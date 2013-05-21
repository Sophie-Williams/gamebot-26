/*
 * SpecialObjects.cpp
 *
 *  Created on: 26.04.2013
 *      Author: urandon
 */

#include "SpecialObjects.h"
#include "Task.h"
#include "Errors.h"
#include <cstdlib>

#include <cstdio>

/* "Templates" */

SchSpecialDontCall::SchSpecialDontCall():SchSpecial(0,0){}
void SchSpecialDontCall::call(SchemeMachine & vm, int N, int step){
	throw NotAFunctionCalledError(getLine());
}

SchSpecialDontExec::SchSpecialDontExec():SchSpecial(0,0){}
void SchSpecialDontExec::execute(SchemeMachine & vm, int N, int step){
	throw NotAnExecutableError(getLine());
}

SchSpecialEvalArgs::SchSpecialEvalArgs():SchSpecial(0,0){}
bool SchSpecialEvalArgs::prepareArgs(){ return true; }

SchSpecialDontEvalArgs::SchSpecialDontEvalArgs():SchSpecial(0,0){}
bool SchSpecialDontEvalArgs::prepareArgs(){ return false; }

SchSpecialValencyZero::SchSpecialValencyZero():SchSpecial(0,0){}
int SchSpecialValencyZero::valency(){ return 0; }

SchSpecialValencyOne::SchSpecialValencyOne():SchSpecial(0,0){}
int SchSpecialValencyOne::valency(){ return 1; }

SchSpecialValencyTwo::SchSpecialValencyTwo():SchSpecial(0,0){}
int SchSpecialValencyTwo::valency(){ return 2; }

SchSpecialValencyThree::SchSpecialValencyThree():SchSpecial(0,0){}
int SchSpecialValencyThree::valency(){ return 3; }

SchSpecialValencyVardic::SchSpecialValencyVardic():SchSpecial(0,0){}
int SchSpecialValencyVardic::valency(){ return -1; }


/* Constructors */

SchSpecialLambda::SchSpecialLambda(int _line):SchSpecial(_line, Special::LAMBDA){};
SchSpecialDefine::SchSpecialDefine(int _line):SchSpecial(_line, Special::DEFINE){};
SchSpecialRedefine::SchSpecialRedefine(int _line):SchSpecial(_line, Special::REDEFINE){};
SchSpecialIf::SchSpecialIf(int _line):SchSpecial(_line, Special::IF){};
SchSpecialCond::SchSpecialCond(int _line):SchSpecial(_line, Special::COND){};
SchSpecialDo::SchSpecialDo(int _line):SchSpecial(_line, Special::DO){};
SchSpecialEval::SchSpecialEval(int _line):SchSpecial(_line, Special::EVAL){};
SchSpecialLet::SchSpecialLet(int _line):SchSpecial(_line, Special::LET){};
SchSpecialPrint::SchSpecialPrint(int _line):SchSpecial(_line, Special::PRINT){};

SchSpecialList::SchSpecialList(int _line):SchSpecial(_line, Special::LIST){};
SchSpecialQuote::SchSpecialQuote(int _line):SchSpecial(_line, Special::QUOTE){};
SchSpecialCar::SchSpecialCar(int _line):SchSpecial(_line, Special::CAR){};
SchSpecialCdr::SchSpecialCdr(int _line):SchSpecial(_line, Special::CDR){};
SchSpecialAdd::SchSpecialAdd(int _line):SchSpecial(_line, Special::ADD){};

SchSpecialPlus::SchSpecialPlus(int _line):SchSpecial(_line, Special::PLUS){};
SchSpecialMinus::SchSpecialMinus(int _line):SchSpecial(_line, Special::MINUS){};
SchSpecialMultiply::SchSpecialMultiply(int _line):SchSpecial(_line, Special::MULTIPLY){};
SchSpecialDivide::SchSpecialDivide(int _line):SchSpecial(_line, Special::DIVIDE){};
SchSpecialModulo::SchSpecialModulo(int _line):SchSpecial(_line, Special::MODULO){};

SchSpecialNotEqual::SchSpecialNotEqual(int _line):SchSpecial(_line, Special::NOT_EQ){};
SchSpecialLess::SchSpecialLess(int _line):SchSpecial(_line, Special::LESS){};
SchSpecialLessEqual::SchSpecialLessEqual(int _line):SchSpecial(_line, Special::LESS_EQ){};
SchSpecialEqual::SchSpecialEqual(int _line):SchSpecial(_line, Special::EQUAL){};
SchSpecialGreaterEqual::SchSpecialGreaterEqual(int _line):SchSpecial(_line, Special::GREATER_EQ){};
SchSpecialGreater::SchSpecialGreater(int _line):SchSpecial(_line, Special::GREATER){};

SchSpecialAnd::SchSpecialAnd(int _line):SchSpecial(_line, Special::AND){};
SchSpecialOr::SchSpecialOr(int _line):SchSpecial(_line, Special::OR){};
SchSpecialNot::SchSpecialNot(int _line):SchSpecial(_line, Special::NOT){};

SchSpecialBuy::SchSpecialBuy(int _line):SchSpecial(_line, Special::BUY){};
SchSpecialSell::SchSpecialSell(int _line):SchSpecial(_line, Special::SELL){};
SchSpecialProd::SchSpecialProd(int _line):SchSpecial(_line, Special::PROD){};
SchSpecialBuild::SchSpecialBuild(int _line):SchSpecial(_line, Special::BUILD){};
SchSpecialEndturn::SchSpecialEndturn(int _line):SchSpecial(_line, Special::ENDTURN){};
SchSpecialWait::SchSpecialWait(int _line):SchSpecial(_line, Special::WAIT){};

SchSpecial_MyId::SchSpecial_MyId(int _line):SchSpecial(_line, Special::_MY_ID){};
SchSpecial_Turn::SchSpecial_Turn(int _line):SchSpecial(_line, Special::_TURN){};
SchSpecial_Players::SchSpecial_Players(int _line):SchSpecial(_line, Special::_PLAYERS){};
SchSpecial_ActivePlayers::SchSpecial_ActivePlayers(int _line):SchSpecial(_line, Special::_ACTIVE_PLAYERS){};
SchSpecial_Supply::SchSpecial_Supply(int _line):SchSpecial(_line, Special::_SUPPLY){};
SchSpecial_RawPrice::SchSpecial_RawPrice(int _line):SchSpecial(_line, Special::_RAW_PRICE){};
SchSpecial_Demand::SchSpecial_Demand(int _line):SchSpecial(_line, Special::_DEMAND){};
SchSpecial_ProductionPrice::SchSpecial_ProductionPrice(int _line):SchSpecial(_line, Special::_PRODUCTION_PRICE){};
SchSpecial_Money::SchSpecial_Money(int _line):SchSpecial(_line, Special::_MONEY){};
SchSpecial_Raw::SchSpecial_Raw(int _line):SchSpecial(_line, Special::_RAW){};
SchSpecial_Production::SchSpecial_Production(int _line):SchSpecial(_line, Special::_PRODUCTION){};
SchSpecial_Factories::SchSpecial_Factories(int _line):SchSpecial(_line, Special::_FACTORIES){};
SchSpecial_ActiveFactories::SchSpecial_ActiveFactories(int _line):SchSpecial(_line, Special::_ACTIVE_FACTORIES){};
SchSpecial_ResultRawBought::SchSpecial_ResultRawBought(int _line):SchSpecial(_line, Special::_RESULT_RAW_BOUGHT){};
SchSpecial_ResultRawPrice::SchSpecial_ResultRawPrice(int _line):SchSpecial(_line, Special::_RESULT_RAW_PRICE){};
SchSpecial_ResultProdSold::SchSpecial_ResultProdSold(int _line):SchSpecial(_line, Special::_RESULT_PROD_SOLD){};
SchSpecial_ResultProdPrice::SchSpecial_ResultProdPrice(int _line):SchSpecial(_line, Special::_RESULT_PROD_PRICE){};

/* Realization */

/* Language-based object */

void SchSpecialLambda::call(SchemeMachine & vm, int N, int step){
	list_t * src;
	int * ids;
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef * defs = refs[N-1];
	SchObjectRef body = *refs[N-2];
	SchList * ldefs;
	int length;

	if((*defs)->getType() != LIST){
		throw Special_LambdaListExpectedError((*defs)->getLine());
	}
	ldefs = static_cast<SchList *>(&**defs);
	length = ldefs->getLength();
	src = ldefs->getList();

	ids = (int *) malloc (length * sizeof(int));
	for(int i = 0; i < length; ++i, src = src->next){
		if((*src->node)->getType() != NAME){
			throw Special_LambdaNameExpectedError((*src->node)->getLine());
		}
		ids[i] = static_cast<SchName *>(&**src->node)->getId();
	}

	vm.pushResult(SchObjectRef(new SchFunction(getLine(), body, ids, length)));
}

void SchSpecialRedefine::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef name = * refs[N-1], alias = * refs[N-2];

	if(step == 0){
		vm.addTask(new ExecTask(SchObjectRef(this), N, 1));
		vm.addTask(new PushResultTask(name));
		vm.addTask(new EvalTask(alias));
	} else {
		if(name->getType() == NAME){
			vm.addTask(new AliasTask( static_cast<SchName *>(&*name)->getId(), alias ));
		} else {
			throw Special_RedefineNameExpectedError(name->getLine());
		}
	}
}


void SchSpecialDefine::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef name = * refs[N-1], alias = * refs[N-2];

	if(name->getType() == NAME){
		vm.addTask(new AliasTask( static_cast<SchName *>(&*name)->getId(), alias ));
	} else
	if(name->getType() == LIST){
		list_t * list = static_cast<SchList *>(&*name)->getList(), * src;
		int length = static_cast<SchList *>(&*name)->getLength()-1;
		int * ids = NULL;
		SchObjectRef alname = *list->node;

		if(length != 0){
			src = list->next;
			ids = (int *) malloc (length * sizeof(int));

			for(int i = 0; i < length; ++i, src = src->next){
				if((*src->node)->getType() != NAME){
					throw Special_DefineNameExpectedError((*src->node)->getLine());
				}
				ids[i] = static_cast<SchName *>(&**src->node)->getId();
			}
		}

		vm.addTask(new AliasTask( static_cast<SchName *>(&*alname)->getId(),
			SchObjectRef(new SchFunction(getLine(), alias, ids, length))));

	} else {
		throw Special_DefineNameExpectedError(name->getLine());
	}
}

void SchSpecialIf::call(SchemeMachine & vm, int N, int step){
	if(step == 0){
		SchObjectRef * cond = *vm.popResult(1);
		vm.addTask(new CallTask(this, N, 1));
		vm.addTask(new EvalTask(*cond));
	} else {
		SchObjectRef ** refs = vm.popResult(N);
		SchObjectRef cond = *refs[N-1], _then = *refs[N-2], _else = *refs[N-3];

		if(cond->getType() == INTEGER && static_cast<SchInteger *>(&*cond)->getN() != 0){
			vm.addTask(new EvalTask(*_then));
		} else {
			vm.addTask(new EvalTask(*_else));
		}
	}
}

void SchSpecialDo::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);

	for(int i = 0; i < N; ++i){
		vm.addTask(new ExecTask(*refs[i], 1));
	}
}

void SchSpecialCond::call(SchemeMachine & vm, int N, int step){
	if(step >= 2*N){
		throw Special_CondNoChoosenError(getLine());
	}
	if(step % 2 == 0){ // evaluate pair->first
		SchObjectRef * pair = * vm.popResult(1);
		if((*pair)->getType() != LIST){
			throw Special_CondListExpectedError((*pair)->getLine());
		}
		list_t * list = static_cast<SchList *>(&**pair)->getList();
		SchObjectRef * cond, * todo;
		if(list == NULL){
			throw Special_CondObjectExpectedError((*pair)->getLine());
		}
		cond = list->node;
		if(list->next == NULL){
			throw Special_CondObjectExpectedError((*pair)->getLine());
		}
		todo = list->next->node;
		vm.pushResult(*todo);
		vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
		vm.addTask(new EvalTask(*cond));
	} else {
		SchObjectRef ** pair = vm.popResult(2);
		SchObjectRef * cond = pair[1], * todo = pair[0];

		if((*cond)->getType() != INTEGER){
			throw Special_CondIntegerExpectedError((*cond)->getType());
		}
		if(static_cast<SchInteger *>(&**cond)->getN()){
			vm.addTask(new EvalTask(*todo));
			vm.popResult(N - step/2 - 1);
		} else {
			vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
		}
	}
}

void SchSpecialEval::call(SchemeMachine & vm, int N, int step){ }

void SchSpecialLet::call(SchemeMachine & vm, int N, int step){
	if(step == 0){
		list_t * src;
		SchObjectRef ** refs = vm.popResult(N);
		SchObjectRef * defs = refs[N-1];
		SchObjectRef body = *refs[N-2];
		SchList * ldefs;
		int length;

		if((*defs)->getType() != LIST){
			throw Special_LetListExpectedError((*defs)->getLine());
		}
		ldefs = static_cast<SchList *>(&**defs);
		length = ldefs->getLength();
		src = ldefs->getList();

		vm.addTask(new DelNamesTask());
		vm.addTask(new EvalTask(body));
		vm.addTask(new CallTask(this, length, step+1));

		for(int i = 0; i < length; ++i, src = src->next){
			SchList * pair;
			SchObject * name, * obj;
			if((*src->node)->getType() != LIST){
				throw Special_LetListExpectedError((*src->node)->getLine());
			}
			pair = static_cast<SchList *>(&**src->node);
			if(pair->getLength() != 2){
				throw Special_LetPairExpectedError(pair->getLine());
			}
			name = &**(pair->getList()->node);
			obj = &**(pair->getList()->next->node);
			if(name->getType() != NAME){
				throw Special_LetNameExpectedError(name->getLine());
			}
			vm.addTask(new PushResultTask(*name));
			vm.addTask(new EvalTask(*obj));
		}
	} else {
		namemap_t * map = new namemap_t(N);
		SchObjectRef ** refs = vm.popResult(2*N);

		// build namemap
		for(int i = 0; i < N; ++i){
			SchObjectRef * name = refs[2*i+1], * obj = refs[2*i];
			map->add(static_cast<SchName *>(&**name)->getId(), *obj);
		}

		vm.addTask(new AddNamesTask(map));
	}
}


void SchSpecialLet::execute(SchemeMachine & vm, int N, int step){
	if(step == 0){
		list_t * src;
		SchObjectRef ** refs = vm.popResult(N);
		SchObjectRef * defs = refs[N-1];
		SchObjectRef body = *refs[N-2];
		SchList * ldefs;
		int length;

		if((*defs)->getType() != LIST){
			throw Special_LetListExpectedError((*defs)->getLine());
		}
		ldefs = static_cast<SchList *>(&**defs);
		length = ldefs->getLength();
		src = ldefs->getList();

		vm.addTask(new DelNamesTask());
		vm.addTask(new ExecTask(body, 0));
		vm.addTask(new ExecTask(this, length, step+1));

		for(int i = 0; i < length; ++i, src = src->next){
			SchList * pair;
			SchObject * name, * obj;
			if((*src->node)->getType() != LIST){
				throw Special_LetListExpectedError((*src->node)->getLine());
			}
			pair = static_cast<SchList *>(&**src->node);
			if(pair->getLength() != 2){
				throw Special_LetPairExpectedError(pair->getLine());
			}
			name = &**(pair->getList()->node);
			obj = &**(pair->getList()->next->node);
			if(name->getType() != NAME){
				throw Special_LetNameExpectedError(name->getLine());
			}
			vm.addTask(new PushResultTask(*name));
			vm.addTask(new EvalTask(*obj));
		}
	} else {
		namemap_t * map = new namemap_t(N);
		SchObjectRef ** refs = vm.popResult(2*N);

		// build namemap
		for(int i = 0; i < N; ++i){
			SchObjectRef * name = refs[2*i+1], * obj = refs[2*i];
			map->add(static_cast<SchName *>(&**name)->getId(), *obj);
		}

		vm.addTask(new AddNamesTask(map));
	}
}


void SchSpecialPrint::execute(SchemeMachine & vm, int N, int step){
	vm.addTask(new PrintTask(N));
}

/* List-based objects */

void SchSpecialList::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	list_t * list, * curr, * next;

	list = (list_t *) malloc (sizeof(*list));
	list->next = NULL;
	curr = list;

	for(int i = N-1; i >= 0; --i, curr = curr->next){
		next = new list_t;
		next->node = new SchObjectRef(*refs[i]);
		next->next = NULL;
		curr->next = next;
	}

	curr = list->next;
	free(list);
	list = curr;

	vm.pushResult(SchObjectRef(new SchList(getLine(), list, N)));
}

void SchSpecialQuote::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	list_t * list, * curr, * next;

	list = (list_t *) malloc (sizeof(*list));
	list->next = NULL;
	curr = list;

	for(int i = N-1; i >= 0; --i, curr = curr->next){
		next = new list_t;
		next->node = new SchObjectRef(*refs[i]);
		next->next = NULL;
		curr->next = next;
	}

	curr = list->next;
	free(list);
	list = curr;

	vm.pushResult(SchObjectRef(new SchList(getLine(), list, N)));
}

void SchSpecialCar::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef * list = refs[N-1];

	if((*list)->getType() == NAME){
		vm.addTask(new CallTask(SchObjectRef(this), N, step));
		vm.addTask(new PushResultTask(( static_cast<SchName *>(&**list)->getRef(vm) )));
	} else {
		if((*list)->getType() != LIST){
			throw Special_CarListExpectedError(getLine());
		}
		vm.pushResult( *static_cast<SchList *>(&**list)->getList()->node );
	}
}

void SchSpecialCdr::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef * list = refs[N-1];
	list_t * cdr;
	int length;

	if((*list)->getType() == NAME){
		vm.addTask(new CallTask(SchObjectRef(this), N, step));
		vm.addTask(new PushResultTask(( static_cast<SchName *>(&**list)->getRef(vm) )));
	} else {
		if((*list)->getType() != LIST){
			throw Special_CdrListExpectedError(getLine());
		}
		cdr = static_cast<SchList *>(&**list)->getList();
		length = static_cast<SchList *>(&**list)->getLength();

		if(cdr == NULL){
			vm.pushResult(SchObjectRef(new SchList(getLine(), NULL, 0)));
		} else {
			++cdr->next->refcount;
			vm.pushResult(SchObjectRef(new SchList(getLine(), cdr->next, length-1)));
		}
	}
}

void SchSpecialAdd::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef first = *refs[N-1], second = *refs[N-2];
	list_t * res, * cont;
	int length;

	if(second->getType() == NAME){
		vm.addTask(new CallTask(SchObjectRef(this), N, step));
		vm.addTask(new PushResultTask(first));
		vm.addTask(new PushResultTask(( static_cast<SchName *>(&*second)->getRef(vm) )));
	} else {
		if(second->getType() != LIST){
			throw Special_AddListExpectedError(getLine());
		}
		cont = static_cast<SchList *>(&*second)->getList();
		length = static_cast<SchList *>(&*second)->getLength()+1;

		++cont->refcount;
		res = new list_t;
		res->next = cont;
		res->node = new SchObjectRef(first);

		vm.pushResult(SchObjectRef(new SchList(getLine(), res, length)));
	}
}


/* Arithmetic objects */

void SchSpecialPlus::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	int sum_i = 0, dx_i;
	double sum_f = 0, dx_f;
	bool is_int = true, curr_int;

	for(int i = N-1; i >= 0; --i){
		switch ((*refs[i])->getType()){
		case INTEGER :
			dx_i = static_cast<SchInteger *>(&**refs[i])->getN();
			curr_int = true;
			break;
		case FLOAT :
			dx_f = static_cast<SchFloat *>(&**refs[i])->getF();
			if(is_int == true){
				sum_f = (double)sum_i;
			}
			is_int = false;
			curr_int = false;
			break;
		default :
			throw Special_PlusNumericExpectedError((*refs[i])->getLine());
			break;
		}

		if(is_int){
			sum_i += dx_i;
		} else {
			if(curr_int){
				sum_f += double(dx_i);
			} else {
				sum_f += dx_f;
			}
		}
	}

	if(is_int){
		vm.pushResult(SchObjectRef(new SchInteger(getLine(), sum_i)));
	} else {
		vm.pushResult(SchObjectRef(new SchFloat(getLine(), sum_f)));
	}
}

void SchSpecialMinus::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	int sum_i = 0, dx_i;
	double sum_f = 0, dx_f;
	bool is_int = true, curr_int;

	for(int i = N-1; i >= 0; --i){
		switch ((*refs[i])->getType()){
		case INTEGER :
			dx_i = static_cast<SchInteger *>(&**refs[i])->getN();
			curr_int = true;
			break;
		case FLOAT :
			dx_f = static_cast<SchFloat *>(&**refs[i])->getF();
			if(is_int == true){
				sum_f = (double)sum_i;
			}
			is_int = false;
			curr_int = false;
			break;
		default :
			throw Special_MinusNumericExpectedError((*refs[i])->getLine());
			break;
		}

		// first element
		if(i == N-1){
			if(is_int){
				sum_i = dx_i;
			} else {
				sum_f = dx_f;
			}
		} else {
			if(is_int){
				sum_i -= dx_i;
			} else {
				if(curr_int){
					sum_f -= double(dx_i);
				} else {
					sum_f -= dx_f;
				}
			}
		}
	}

	if(is_int){
		vm.pushResult(SchObjectRef(new SchInteger(getLine(), (N==1)?-sum_i:sum_i)));
	} else {
		vm.pushResult(SchObjectRef(new SchFloat(getLine(), (N==1)?-sum_f:sum_f)));
	}
}

void SchSpecialMultiply::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	int sum_i = 1, dx_i;
	double sum_f = 1, dx_f;
	bool is_int = true, curr_int;

	for(int i = N-1; i >= 0; --i){
		switch ((*refs[i])->getType()){
		case INTEGER :
			dx_i = static_cast<SchInteger *>(&**refs[i])->getN();
			curr_int = true;
			break;
		case FLOAT :
			dx_f = static_cast<SchFloat *>(&**refs[i])->getF();
			if(is_int == true){
				sum_f = (double)sum_i;
			}
			is_int = false;
			curr_int = false;
			break;
		default :
			throw Special_MultiplyNumericExpectedError((*refs[i])->getLine());
			break;
		}

		if(is_int){
			sum_i *= dx_i;
		} else {
			if(curr_int){
				sum_f *= double(dx_i);
			} else {
				sum_f *= dx_f;
			}
		}
	}

	if(is_int){
		vm.pushResult(SchObjectRef(new SchInteger(getLine(), sum_i)));
	} else {
		vm.pushResult(SchObjectRef(new SchFloat(getLine(), sum_f)));
	}
}

void SchSpecialDivide::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	int sum_i = 0, dx_i;
	double sum_f = 0, dx_f;
	bool is_int = true, curr_int;

	if(N < 1){
		throw Special_DivideExpectedAtLeastOneArgumentError(getLine());
	}
	// first elem
	switch ((*refs[N-1])->getType()){
	case INTEGER :
		dx_i = static_cast<SchInteger *>(&**refs[N-1])->getN();
		curr_int = true;
		break;
	case FLOAT :
		dx_f = static_cast<SchFloat *>(&**refs[N-1])->getF();
		if(is_int == true){
			sum_f = (double)sum_i;
		}
		is_int = false;
		curr_int = false;
		break;
	default :
		throw Special_DivideNumericExpectedError((*refs[N-1])->getLine());
		break;
	}
	if(is_int){
		sum_i = dx_i;
	} else {
		sum_f = dx_f;
	}


	for(int i = N-2; i >= 0; --i){
		switch ((*refs[i])->getType()){
		case INTEGER :
			dx_i = static_cast<SchInteger *>(&**refs[i])->getN();
			curr_int = true;
			break;
		case FLOAT :
			dx_f = static_cast<SchFloat *>(&**refs[i])->getF();
			if(is_int == true){
				sum_f = (double)sum_i;
			}
			is_int = false;
			curr_int = false;
			break;
		default :
			throw Special_DivideNumericExpectedError((*refs[i])->getLine());
			break;
		}

		if(is_int){
			if(dx_i == 0){
				throw Special_DivideByZeroError((*refs[i])->getLine());
			}
			sum_i /= dx_i;
		} else {
			if(curr_int){
				sum_f /= double(dx_i);
			} else {
				sum_f /= dx_f;
			}
		}
	}

	if(N == 1){
		if(is_int){
			if(sum_i == 0){
				throw Special_DivideByZeroError((*refs[N-1])->getLine());
			}
			sum_i = 1 / sum_i;
		} else {
			if(sum_f == 0){
				throw Special_DivideByZeroError((*refs[N-1])->getLine());
			}
			sum_f = 1 / sum_f;
		}
	}

	if(is_int){
		vm.pushResult(SchObjectRef(new SchInteger(getLine(), sum_i)));
	} else {
		vm.pushResult(SchObjectRef(new SchFloat(getLine(), sum_f)));
	}
}

void SchSpecialModulo::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	int a, b;

	if((*refs[N-1])->getType() != INTEGER){
		throw  Special_ModuloIntegerExpectedError((*refs[N-1])->getLine());
	}
	if((*refs[N-2])->getType() != INTEGER){
		throw  Special_ModuloIntegerExpectedError((*refs[N-2])->getLine());
	}

	a = static_cast<SchInteger *>(&**refs[N-1])->getN();
	b = static_cast<SchInteger *>(&**refs[N-2])->getN();

	if(b == 0){
		throw Special_ModuloByZeroError((*refs[N-2])->getLine());
	}

	vm.pushResult(SchObjectRef(new SchInteger(getLine(), a % b)));
}

/* Comparation-based objects */

void SchSpecialLess::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f < b_f;
	} else {
		res = a_i < b_i;
	}

	if(res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}

void SchSpecialLessEqual::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f <= b_f;
	} else {
		res = a_i <= b_i;
	}

	if(res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}

void SchSpecialEqual::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f == b_f;
	} else {
		res = a_i == b_i;
	}

	if(res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}

void SchSpecialNotEqual::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f == b_f;
	} else {
		res = a_i == b_i;
	}

	if(!res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}


void SchSpecialGreaterEqual::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f >= b_f;
	} else {
		res = a_i >= b_i;
	}

	if(res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}

void SchSpecialGreater::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef a = *refs[N-1], b = *refs[N-2];
	int a_i, b_i;
	double a_f, b_f;
	bool res, float_cmp = false;

	switch(a->getType()){
	case INTEGER :
		a_f = a_i = static_cast<SchInteger *>(&*a)->getN();
		break;
	case FLOAT :
		a_f = static_cast<SchFloat *>(&*a)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(a->getLine());
		break;
	}

	switch(b->getType()){
	case INTEGER :
		b_f = b_i = static_cast<SchInteger *>(&*b)->getN();
		break;
	case FLOAT :
		b_f = static_cast<SchFloat *>(&*b)->getF();
		float_cmp = true;
		break;
	default :
		throw Special_CompareNumericExpectedError(b->getLine());
		break;
	}

	if(float_cmp){
		res = a_f > b_f;
	} else {
		res = a_i > b_i;
	}

	if(res){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}

/* Logic-based objects */

void SchSpecialAnd::call(SchemeMachine & vm, int N, int step){
	// SchObjectRef ** refs = vm.popResult(N); // because of lazyness
	if(step > N){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else
	if(step == 0){
		if(N == 0){
			vm.pushResult(SchObjectRef(new SchTrue(getLine())));
		} else {
			vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
			vm.addTask(new EvalTask( **vm.popResult(1) ));
		}
	} else {
		SchObjectRef * arg = *vm.popResult(1);
		int res;
		if((*arg)->getType() != INTEGER){
			throw Special_LogicIntExpectedError(getLine());
		}
		res = static_cast<SchInteger *>(&**arg)->getN();
		if(res == 0){
			// return False and flush stack
			vm.popResult(N-step);
			vm.pushResult(SchObjectRef(new SchFalse(getLine())));
		} else {
				vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
				if(step < N){
					vm.addTask(new EvalTask( **vm.popResult(1) ));
				}
		}
	}
}

void SchSpecialOr::call(SchemeMachine & vm, int N, int step){
	if(step > N){
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	} else
	if(step == 0){
		if(N == 0){
			vm.pushResult(SchObjectRef(new SchFalse(getLine())));
		} else {
			vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
			vm.addTask(new EvalTask( **vm.popResult(1) ));
		}
	} else {
		SchObjectRef * arg = *vm.popResult(1);
		int res;
		if((*arg)->getType() != INTEGER){
			throw Special_LogicIntExpectedError(getLine());
		}
		res = static_cast<SchInteger *>(&**arg)->getN();
		if(res != 0){
			// return True and flush stack
			vm.pushResult(SchObjectRef(new SchTrue(getLine())));
			vm.popResult(N-step);
		} else {
			vm.addTask(new CallTask(SchObjectRef(this), N, step+1));
			if(N < step){
				vm.addTask(new EvalTask( **vm.popResult(1) ));
			}
		}
	}
}

void SchSpecialNot::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef * a = refs[N-1];

	if((*a)->getType() != INTEGER){
		throw Special_LogicIntExpectedError(getLine());
	}
	if(static_cast<SchInteger *>(&**a)->getN() == 0){
		vm.pushResult(SchObjectRef(new SchTrue(getLine())));
	} else {
		vm.pushResult(SchObjectRef(new SchFalse(getLine())));
	}
}


/* Game-based objects-operations */
// ==========================================================================
// =                                                                        =
// =                   Network based operation are bellow                   =
// =                                                                        =
// ==========================================================================

// TODO: network integration
// just printf's while language testing
// so.

/* PERFORM */

void SchSpecialBuy::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef quantity = *refs[N-1], price = *refs[N-2];
	int q, p;

	if(quantity->getType() != INTEGER){
		throw Special_NetworkIntQuantityExpectedError(quantity->getLine());
	}
	if(price->getType() != INTEGER){
		throw Special_NetworkIntPriceExpectedError(price->getLine());
	}

	q = static_cast<SchInteger *>(&*quantity)->getN();
	p = static_cast<SchInteger *>(&*price)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::BUY, 0, q, p));
}

void SchSpecialSell::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef quantity = *refs[N-1], price = *refs[N-2];
	int q, p;

	if(quantity->getType() != INTEGER){
		throw Special_NetworkIntQuantityExpectedError(quantity->getLine());
	}
	if(price->getType() != INTEGER){
		throw Special_NetworkIntPriceExpectedError(price->getLine());
	}

	q = static_cast<SchInteger *>(&*quantity)->getN();
	p = static_cast<SchInteger *>(&*price)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::SELL, 0, q, p));
}

void SchSpecialProd::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef quantity = *refs[N-1];
	int q;

	if(quantity->getType() != INTEGER){
		throw Special_NetworkIntQuantityExpectedError(quantity->getLine());
	}

	q = static_cast<SchInteger *>(&*quantity)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::PROD, 0, q));
}

void SchSpecialBuild::execute(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef quantity = *refs[N-1];
	int q;

	if(quantity->getType() != INTEGER){
		throw Special_NetworkIntQuantityExpectedError(quantity->getLine());
	}

	q = static_cast<SchInteger *>(&*quantity)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::BUILD, 0, q));
}

void SchSpecialEndturn::execute(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::ENDTURN));
}

void SchSpecialWait::execute(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::PERFORM, NetworkTask::WAIT));
}

/* GENERAL */

void SchSpecial_MyId::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::GENERAL, NetworkTask::MY_ID));
}

void SchSpecial_Turn::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::GENERAL, NetworkTask::TURN));
}

void SchSpecial_Players::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::GENERAL, NetworkTask::PLAYERS));
}

void SchSpecial_ActivePlayers::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::GENERAL, NetworkTask::ACTIVE_PLAYERS));
}

/* MARKET */

void SchSpecial_Supply::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::MARKET, NetworkTask::SUPPLY));
}

void SchSpecial_RawPrice::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::MARKET, NetworkTask::RAW_PRICE));
}

void SchSpecial_Demand::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::MARKET, NetworkTask::DEMAND));
}

void SchSpecial_ProductionPrice::call(SchemeMachine & vm, int N, int step){
	if(N != 0){	vm.popResult(N); }
	vm.addTask(new NetworkTask(NetworkTask::MARKET, NetworkTask::PRODUCTION_PRICE));
}

/* PLAYER */

void SchSpecial_Money::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PLAYER, NetworkTask::MONEY, pid));
}

void SchSpecial_Raw::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PLAYER, NetworkTask::RAW, pid));
}

void SchSpecial_Production::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PLAYER, NetworkTask::PRODUCTION, pid));
}

void SchSpecial_Factories::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PLAYER, NetworkTask::FACTORIES, pid));
}

void SchSpecial_ActiveFactories::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::PLAYER, NetworkTask::ACTIVE_FACTORIES, pid));
}

/* AUCTION */

void SchSpecial_ResultRawBought::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::AUCTION, NetworkTask::RESULT_RAW_BOUGHT, pid));
}

void SchSpecial_ResultRawPrice::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::AUCTION, NetworkTask::RESULT_RAW_PRICE, pid));
}

void SchSpecial_ResultProdSold::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::AUCTION, NetworkTask::RESULT_PROD_SOLD, pid));
}

void SchSpecial_ResultProdPrice::call(SchemeMachine & vm, int N, int step){
	SchObjectRef ** refs = vm.popResult(N);
	SchObjectRef player_id = *refs[N-1];
	int pid;

	if(player_id->getType() != INTEGER){
		throw Special_NetworkIntPlayerExpectedError(player_id->getLine());
	}

	pid = static_cast<SchInteger *>(&*player_id)->getN();

	vm.addTask(new NetworkTask(NetworkTask::AUCTION, NetworkTask::RESULT_PROD_PRICE, pid));
}
