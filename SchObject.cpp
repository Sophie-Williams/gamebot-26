/*
 * SchObject.cpp
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#include "SchObject.h"
#include "Errors.h"
#include "Task.h"
#include <cstdio>
#include <cstdlib>

SchObject::SchObject(int _line):refcount(0), line(_line) {
	my_id = ++max_id;
}
SchObject::~SchObject() { }

int SchObject::max_id = 0;
int SchObject::getId(){ return my_id; }
int SchObject::getRefcount(){ return refcount; }
int SchObject::getLine() { return line; }

/* Smart RefCount Pointer */

SchObjectRef::SchObjectRef(SchObject & mobj):obj(&mobj){
	mobj.refcount++;
}

SchObjectRef::SchObjectRef(SchObject * mobj):obj(mobj){
	mobj->refcount++;
}

SchObjectRef::SchObjectRef(const SchObjectRef & ref):obj(ref.obj){
	ref.obj->refcount++;
}

SchObjectRef::~SchObjectRef(){
	if(--obj->refcount == 0){
		delete obj;
	}
}

SchObject * SchObjectRef::operator->() { return obj;  }
SchObject & SchObjectRef::operator* () { return *obj; }


/* Constants */

SchConstant::SchConstant(int _line):SchObject(_line) { };
void SchConstant::evaluate(SchemeMachine & vm, int step){
	vm.pushResult(SchObjectRef(this));
}
void SchConstant::call(SchemeMachine & vm, int N, int step){
	throw NotAFunctionCalledError(getLine());
}
void SchConstant::execute(SchemeMachine & vm, int N, int step){
	throw NotAnExecutableError(getLine());
};

SchInteger::SchInteger(int _line, int _n):SchConstant(_line), n(_n) { };
SchObject::type_t SchInteger::getType(){ return INTEGER; }
int SchInteger::getN(){ return n; }
void SchInteger::print(){ printf("%di", n); }

SchTrue::SchTrue(int _line):SchInteger(_line, 1){}
SchFalse::SchFalse(int _line):SchInteger(_line, 0){}

SchFloat::SchFloat(int _line, double _f):SchConstant(_line), f(_f) { };
SchObject::type_t SchFloat::getType(){ return FLOAT; }
double SchFloat::getF(){ return f; }
void SchFloat::print(){ printf("%ff", f); }

SchString::SchString(int _line, const char * _s):SchConstant(_line), s(_s) { };
SchObject::type_t SchString::getType(){ return STRING; }
const char * SchString::getS(){ return s; }
void SchString::print(){ printf("%s", s); }


/* list_t */

list_t::list_t():refcount(1){}

list_t::~list_t(){
	delete node;
	if(next != 0){
		--next->refcount;
		if(next->refcount <= 0){
			delete next;
		}
	}
}

/* List */


int SchList::tabs = 0;

SchList::SchList(int _line, list_t* _list, int _length):
		SchObject(_line), list(_list), length(_length) {}

SchList::SchList(int _line, list_t* _list):
		SchObject(_line), list(_list)
{
	int cnt = 0;
	for(list_t * tmp = _list; tmp != NULL; tmp = tmp->next){
		cnt++;
	}
	length = cnt;
};


SchList::~SchList(){
	if(list != NULL){
		list->refcount--;
		if(list->refcount <= 0){
			delete list;
		}
	}
}


void SchList::call(SchemeMachine & vm, int N, int step){ throw NotAFunctionCalledError(getLine()); }

void SchList::evaluate(SchemeMachine & vm, int step){
	if(length == 0){
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	} else
	if(step == 0){
		vm.addTask(new EvalTask(SchObjectRef(this), 1));
		vm.addTask(new EvalTask(SchObjectRef(*list->node))); // evaluate arg0
	} else {
		//arg0 is on the top of result stack
		SchObjectRef arg0 = SchObjectRef(**vm.popResult(1));

		vm.addTask(new CallTask(arg0, length-1));
		if(arg0->getType() == SPECIAL){
			SchSpecial * spec = static_cast<SchSpecial *>(&*arg0);
			int valency = spec->valency();

			if(valency != -1 && valency != length-1){
				throw WrongNumberOfArgumentsError(getLine(), length-1, valency);
			}

			if(spec->prepareArgs()){
				for(list_t * curr = list->next; curr != NULL; curr = curr->next){
					vm.addTask(new EvalTask(*curr->node));
				}
			} else {
				for(list_t * curr = list->next; curr != NULL; curr = curr->next){
					vm.addTask(new PushResultTask(*curr->node));
				}
			}
		} else {
			for(list_t * curr = list->next; curr != NULL; curr = curr->next){
				vm.addTask(new EvalTask(*curr->node));
			}
		}
	}
}


void SchList::execute(SchemeMachine & vm, int N, int step){
	if(length == 0){
		throw NotAnExecutableError(getLine());
	} else
	if(step == 0){
		vm.addTask(new ExecTask(SchObjectRef(this), 1, 1));
		vm.addTask(new EvalTask(SchObjectRef(*list->node))); // evaluate arg0
	} else {
		//arg0 is on the top of result stack
		SchObjectRef arg0 = SchObjectRef(**vm.popResult(1));

		vm.addTask(new ExecTask(arg0, length-1));
		if(arg0->getType() == SPECIAL){
			SchSpecial * spec = static_cast<SchSpecial *>(&*arg0);
			int valency = spec->valency();

			if(valency != -1 && valency != length-1){
				throw WrongNumberOfArgumentsError(getLine(), length-1, valency);
			}

			if(spec->prepareArgs()){
				for(list_t * curr = list->next; curr != NULL; curr = curr->next){
					vm.addTask(new EvalTask(*curr->node));

				}
			} else {
				for(list_t * curr = list->next; curr != NULL; curr = curr->next){
					vm.addTask(new PushResultTask(*curr->node));
				}
			}
		} else {
			for(list_t * curr = list->next; curr != NULL; curr = curr->next){
				vm.addTask(new EvalTask(*curr->node)); //TODO check
			}
		}
	}
}

list_t * SchList::getList(){ return list; }
int SchList::getLength(){ return length; }


void SchList::print(){
	bool islist = false, prev_islist = false, was_list = false;
	const char * space = "    ";

	for(int i = 0; i < tabs; ++i){
		printf("%s", space);
	}
	printf("( ");
	++tabs;
	for(list_t * ptr = list; ptr != NULL; ptr = ptr->next){
		islist = (*ptr->node)->getType() == LIST;
		if(islist){
			was_list = true;
			printf("\n");
		} else
		if(prev_islist){
			printf("\n");
			for(int i = 0; i < tabs; ++i){
				printf("%s", space);
			}
		}
		if((*ptr->node)->getType() == STRING){
			printf("\"");
			(*ptr->node)->print();
			printf("\"");
		} else {
			(*ptr->node)->print();
		}
		printf(" ");
		prev_islist = islist;
	}
	--tabs;
	if(tabs != 0){
		if(islist){
			printf("\n");
			for(int i = 0; i < tabs; ++i){
				printf("%s", space);
			}
		}
	} else {
		if(was_list){
			printf("\n");
		}
	}
	printf(")");
}

SchObject::type_t SchList::getType(){ return LIST; }

/* Functions */

int SchFunction::top_id = 0;

SchFunction::SchFunction(int _line, SchObjectRef _body, const int * _ids, int _length):
		SchObject(_line), length(_length), body(_body)
{
	ids = (typeof(ids)) malloc (_length * sizeof(*ids));
	for(int i = 0; i < _length; ++i){
		ids[i] = _ids[i];
	}
	_id = ++top_id;
}

SchFunction::SchFunction(int _line, SchObjectRef _body, int * _ids, int _length):
		SchObject(_line), ids(_ids), length(_length), body(_body) { _id = ++top_id; }


SchFunction::~SchFunction(){
	free(ids);
}

void SchFunction::evaluate(SchemeMachine & vm, int step){ vm.pushResult(SchObjectRef(this)); }
//void SchFunction::execute(SchemeMachine & vm, int N, int step){
//	throw NotAnExecutableError(getLine());
//}

void SchFunction::execute(SchemeMachine & vm, int N, int step){
	if(N != length){
		throw WrongNumberOfArgumentsError(getLine(), N, length);
	}
	namemap_t * map = new namemap_t(N);
	SchObjectRef ** refs = vm.popResult(N);

	for(int i = 0; i < N; ++i){
		if(refs[i] == NULL){
			throw RuntimeError(getLine());
		}
		map->add(ids[i], *(refs[N-1 - i]));
	}

	vm.addTask(new DelNamesTask());
	vm.addTask(new ExecTask(body, N));
	vm.addTask(new AddNamesTask(map));
}

void SchFunction::call(SchemeMachine & vm, int N, int step){
	if(N != length){
		throw WrongNumberOfArgumentsError(getLine(), N, length);
	}
	namemap_t * map = new namemap_t(N);
	SchObjectRef ** refs = vm.popResult(N);

	for(int i = 0; i < N; ++i){
		if(refs[i] == NULL){
			throw RuntimeError(getLine());
		}
		map->add(ids[i], *(refs[N-1 - i]));
	}

	vm.addTask(new DelNamesTask());
	vm.addTask(new EvalTask(body));
	vm.addTask(new AddNamesTask(map));
}

void SchFunction::print(){
	printf("<func id=%d>", _id);
}

SchObject::type_t SchFunction::getType(){ return FUNCTION; }


/* Specials and Names */
SchName::SchName(int _line, int _id): SchObject(_line), id(_id) { } ;
void SchName::call(SchemeMachine & vm, int N, int step){
	throw NotAFunctionCalledError(getLine());
}
void SchName::evaluate(SchemeMachine & vm, int step){
	vm.addTask(new EvalTask(vm.getRef(id)));
}
void SchName::execute(SchemeMachine & vm, int N, int step){
//	throw NotAnExecutableError(getLine());
	vm.addTask(new ExecTask(vm.getRef(id), N));
}

SchObject::type_t SchName::getType(){ return SchObject::NAME; }
void SchName::print(){ printf("<name_id=%d>", id); }
int SchName::getId(){ return id; }

SchObjectRef SchName::getRef(SchemeMachine &vm){ return vm.getRef(id); }


SchSpecial::SchSpecial(int _line, int _id): SchObject(_line), id(_id) { } ;
SchObject::type_t SchSpecial::getType(){ return SchObject::SPECIAL; }
void SchSpecial::evaluate(SchemeMachine & vm, int step){ vm.pushResult(SchObjectRef(this)); };
void SchSpecial::print(){ printf("%s id=%d", Predefined::atoms[id], id); }

const char * Predefined::atoms[] = {
		// Scheme-specefied
		"lambda", "define",	"if", "cond", "do", "eval", "let", //6
		"list", "quote", "car", "cdr", "add", //11
		// Arithmetic & Logic
		"+", "-", "*", "/", "%", // 16
		"!=", "<", "<=", "=", ">=", ">", // 22
		"#true", "#false", // 24
		"and", "or", "not", // 27
		// network operators
		"buy", "sell", "prod", "build", "endturn", // 32
		"print", // 33
		// network operations
		"?my_id", "?turn", "?players", "?active_players", // 37
		"?supply", "?raw_price", "?demand",	"?production_price", // 41
		"?money", "?raw", "?production", "?factories", "?active_factories", "?manufactured", // 47
		// newtork auction results
		"?result_raw_bought", "?result_raw_price", // 49
		"?result_prod_sold", "?result_prod_price", // 51
		//new
		":=", "wait" // 53
};

const int Predefined::length = LengthOf(Predefined::atoms);

