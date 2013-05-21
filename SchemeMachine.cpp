/*
 * SchemeMachine.cpp
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#include "SchemeMachine.h"
#include "Task.h"
#include "Errors.h"
#include <cstdlib>
#include <cstdio>

SchemeMachine::SchemeMachine(const char * ip, int port, struct timeval default_timeval):
	local_names(NULL), cycle(1), last_line(0)
{
	client = new GameClient(ip, port, default_timeval);
}

SchemeMachine::~SchemeMachine() {
	delete client;
}

/* SchemeMachine::task_stack_t */

const int SchemeMachine::task_stack_t::DEFAULT = 256;

SchemeMachine::task_stack_t::task_stack_t(){
	size = 0;
	allocated = DEFAULT;
	data = (typeof(data)) malloc(allocated * sizeof(* data));
}

SchemeMachine::task_stack_t::~task_stack_t(){
	delete [] data;
}

void SchemeMachine::task_stack_t::push(Task * task){
	const int DISCOUNT_FACTOR = 16;
	int newsize = size + 1;

	if(newsize >= allocated){
		allocated *= 2;
		data = (typeof(data)) realloc(data, allocated * sizeof(* data));
	}
	if(allocated > DEFAULT && newsize > 0 && newsize * DISCOUNT_FACTOR < allocated){
		allocated /= DISCOUNT_FACTOR / 4;
		data = (typeof(data)) realloc(data, allocated * sizeof(* data));
	}

	data[size] = task;
	size = newsize;
}

Task * SchemeMachine::task_stack_t::pop(int last_line){
	if(size <= 0){
		throw TaskStackUnderflowError(last_line);
	}
	return data[--size];
}

bool SchemeMachine::task_stack_t::isEmpty(){
	return size == 0;
}

void SchemeMachine::task_stack_t::print(){
	for(int i = size-1; i >= 0; --i){
		printf("task#%d ", i);
		data[i]->print();
		printf("\n");
	}
}

/* SchemeMachine::result_stack_t */

const int SchemeMachine::result_stack_t::DEFAULT = 64;

SchemeMachine::result_stack_t::result_stack_t():size(0),actual_top(0){
	allocated = DEFAULT;
	data = (typeof(data)) malloc(allocated * sizeof(* data));
}

SchemeMachine::result_stack_t::~result_stack_t(){
	delete [] data;
}

void SchemeMachine::result_stack_t::push(SchObjectRef ref){
	int newsize = size + 1;
	const int DISCOUNT_FACTOR = 16;

	if(newsize >= allocated){
		allocated *= 2;
		data = (typeof(data)) realloc(data, allocated * sizeof(* data));
	}
	if(actual_top > size){ // collect garbage
		for(int i = size; i < actual_top; ++i){
			delete data[i];
		}
		actual_top = size;
	}
	if(allocated > DEFAULT && newsize > 0 && actual_top * DISCOUNT_FACTOR < allocated){
		allocated /= DISCOUNT_FACTOR / 4;
		data = (typeof(data)) realloc(data, allocated * sizeof(* data));
	}

	data[size] = new SchObjectRef(ref);
	actual_top = size = newsize;
}

SchObjectRef ** SchemeMachine::result_stack_t::pop(int N, int last_line){
	if(size < N){
		throw ResultStackUnderflowError(last_line);
	}
	if(actual_top > size){ // collect garbage
		for(int i = size; i < actual_top; ++i){
			delete data[i];
		}
		actual_top = size;
	}

	size -= N;
	return data + size;
}

void SchemeMachine::result_stack_t::print(){
	for(int i = size-1; i >= 0; --i){
		printf("res#%d ", i);
		(*data[i])->print();
		printf("\n");
	}
}

/* global names */

const int SchemeMachine::global_names_t::DEFAULT = 64;

SchemeMachine::global_names_t::global_names_t(){
	allocated = DEFAULT;
	size = 0;
	ids = (int *) malloc(allocated * sizeof(int));
	refs = (typeof(refs)) malloc(allocated * sizeof(*refs));
}

SchemeMachine::global_names_t::~global_names_t(){
	for(int i = 0; i < size; ++i){
		delete refs[i];
	}
	delete ids;
	delete refs;
}

SchObjectRef * SchemeMachine::global_names_t::searchRef(int id){
	for(int i = 0; i < size; ++i){
		if(ids[i] == id){
			return refs[i];
		}
	}
	return NULL;
}

void SchemeMachine::global_names_t::push(int id, const SchObjectRef & ref){
	bool found = false;
	for(int i = 0; i < size && !found; ++i){
		if(ids[i] == id){
			delete refs[i];
			refs[i] = new SchObjectRef(ref);
			found = true;
		}
	}
	if(!found){
		int newsize = size+1;
		if(newsize >= allocated){
			allocated *= 2;
			ids = (int *) realloc(ids, allocated * sizeof(* ids));
			refs = (typeof(refs)) realloc(refs, allocated * sizeof(* refs));
		}
		ids[size] = id;
		refs[size] = new SchObjectRef(ref);
		size = newsize;
	}
}

/* SchemeMachine public methods */

SchObjectRef ** SchemeMachine::popResult(int N){ return (N > 0) ? results.pop(N, last_line) : NULL; }

void SchemeMachine::pushResult(SchObjectRef ref){ results.push(ref); }

void SchemeMachine::addTask(Task * task){
	tasks.push(task);
}

void SchemeMachine::launch(bool verbose){
	while(!tasks.isEmpty()){
		performTask();
		if(verbose){
			printf("\n\n\t\tCycle ## %d\n", cycle++);
			printf("\tTask stack::\n");
			tasks.print();
			printf("\tResult stack::\n");
			results.print();
			if(local_names != NULL){
				int level = 0;
				printf("\tLocal names::");
				for(local_names_t * curr = local_names; curr != NULL; curr = curr->prev){
					printf("\nlevel#%d ", level++);
					curr->current->print();
				}
				printf("\n");
			}
			if(global_names.size != 0){
				printf("\tGlobal names::");
				for(int i = 0; i < global_names.size; ++i){
					printf(" [%d ", global_names.ids[i]);
					(*global_names.refs[i])->print();
					printf("]\n");
//					printf(" [%d]", global_names.ids[i]);
				}
				printf("\n");
			}
		}
	}
}

SchObjectRef SchemeMachine::getRef(int id){
	SchObjectRef * res;
	for(local_names_t * local = local_names; local != NULL; local = local->prev){
		if( (res = local->current->searchRef(id)) != NULL ) {
			return *res;
		}
	}
	if( (res = global_names.searchRef(id)) != NULL ){
		return *res;
	}

	throw UndefinedSymbolError(last_line, id);
}

void SchemeMachine::performTask(){
	Task * task = tasks.pop(last_line);
	int n;

	switch(task->getType()){
	case Task::EVALUATE :
	{
		EvalTask * evtask;
		SchObjectRef * ref;
		int step;
		evtask = static_cast<EvalTask *>(task);
		ref = new SchObjectRef(*evtask->ref);
		last_line = (*ref)->getLine();
		step = evtask->step;
		delete task;
		(*ref)->evaluate(*this, step);
		delete ref;
	}
		break;
	case Task::CALL :
	{
		// tail recursion optimisation. if CALL and argument haz been evaluated --> del
		CallTask * ctask;
		ctask = static_cast<CallTask *>(task);
		int step = ctask->step;

		if(!tasks.isEmpty() && tasks.data[tasks.size-1]->getType() == Task::DEL_NAMES &&
				((*ctask->ref)->getType() != SchObject::SPECIAL || static_cast<SchSpecial *>(&**ctask->ref)->prepareArgs()))
		{
			// swap tasks
			Task * tmp = tasks.data[tasks.size-1]; // DEL_NAMES
			tasks.push(task);
			tasks.data[tasks.size-2] = tasks.data[tasks.size-1]; // DEL <- CALL
			tasks.data[tasks.size-1] = tmp; // CALL <- tmp
		} else {
			SchObjectRef * ref;
			ref = new SchObjectRef(*ctask->ref);
			last_line = (*ref)->getLine();
			n = ctask->n;
			delete task;
			(*ref)->call(*this, n, step);
			delete ref;
		}
	}
		break;
	case Task::EXECUTE :
	{
		ExecTask * extask;
		int step;
		bool must_swap = false;
		extask = static_cast<ExecTask *>(task);

		if(!tasks.isEmpty() && tasks.data[tasks.size-1]->getType() == Task::DEL_NAMES){
			if((*extask->ref)->getType() == SchObject::LIST){ // TODO
				must_swap = false;
			} else
			if((*extask->ref)->getType() != SchObject::SPECIAL){
				must_swap = true;
			} else
			if(static_cast<SchSpecial *>(&**extask->ref)->prepareArgs()){
				must_swap = true;
			}
		}

		if(must_swap) {
			// swap tasks
			Task * tmp = tasks.data[tasks.size-1]; // DEL_NAMES
			tasks.push(task);
			tasks.data[tasks.size-2] = tasks.data[tasks.size-1]; // DEL <- CALL
			tasks.data[tasks.size-1] = tmp; // CALL <- tmp
		} else {
			SchObjectRef * ref;
			ref = new SchObjectRef(*extask->ref);
			last_line = (*ref)->getLine();
			step = extask->step;
			n = extask->n;
			delete task;
			(*ref)->execute(*this, n, step);
			delete ref;
		}
	}
		break;
	case Task::ALIAS :
	{
		AliasTask * altask;
		altask = static_cast<AliasTask *>(task);
		global_names.push(altask->id, *(altask->ref));
		delete task;
	}
		break;
	case Task::ADD_NAMES :
	{
		AddNamesTask * atask;
		local_names_t * tmp;
		atask = static_cast<AddNamesTask *>(task);
		tmp = (typeof(tmp)) malloc (sizeof(*tmp));
		tmp->current = atask->map;
		tmp->prev = local_names;
		local_names = tmp;
		delete task;
	}
		break;
	case Task::DEL_NAMES :
	{
		delete task;
		if(local_names == NULL){
			throw LocalNamespaceUnderflowError(last_line);
		} else {
			local_names_t * tmp = local_names->prev;
			delete local_names->current;
			delete local_names;
			local_names = tmp;
		}
	}
		break;
	case Task::PRINT :
	{
		int N;
		SchObjectRef ** refs;
		N = static_cast<PrintTask *>(task)->N;
		refs = results.pop(N, last_line);
		for(int i = N-1; i >= 0; --i){
			(*refs[i])->print();
		}
		printf("\n");
		delete task;
	}
		break;
	case Task::PUSH_RESULT :
	{
		SchObjectRef * ref;
		ref = new SchObjectRef( * static_cast<PushResultTask *>(task)->ref );
		delete task;
		pushResult(*ref);
		delete ref;
	}
		break;
	case Task::NETWORK :
	{
		NetworkTask * ntask = static_cast<NetworkTask *>(task);
		int quantity = ntask->quantity, price = ntask->price, pid=ntask->player_id;

		if(ntask->gtype == NetworkTask::PERFORM){
			client->perform(ntask->subtype, quantity, price);
		} else {
			int res = client->getInfo(ntask->gtype, ntask->subtype, pid, quantity, price);
			pushResult(SchObjectRef(new SchInteger(last_line, res)));
		}

		delete task;
		break;
	}
	default:
		throw RuntimeError(last_line);
		break;
	}
}
