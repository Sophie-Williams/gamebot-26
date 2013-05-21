/*
 * Task.cpp
 *
 *  Created on: 22.04.2013
 *      Author: urandon
 */

#include "Task.h"
#include <cstdlib>
#include <cstdio>

/* namemap */

const int namemap_t::DEFAULT = 1;

namemap_t::namemap_t(int _allocated = DEFAULT){
	allocated = _allocated;
	size = 0;
	refs = (typeof(refs)) malloc (allocated * sizeof(*refs));
	ids = (typeof(ids)) malloc (allocated * sizeof(*ids));
}

namemap_t::~namemap_t(){
	for(int i = 0; i < size; ++i){
		delete refs[i];
	}
	free(refs);
	free(ids);
}

void namemap_t::add(int id, SchObjectRef ref){
	if(size == allocated){
		throw NamemapOverflorError();
	}
	ids[size] = id;
	refs[size] = new SchObjectRef(ref);
	++size;
}

SchObjectRef * namemap_t::searchRef(int id){
	for(int i = 0; i < size; ++i){
		if(ids[i] == id){
			return refs[i];
		}
	}
	return NULL;
}

void namemap_t::print(){
	for(int i = 0; i < size; ++i){
		printf("[id=%d ref=", ids[i]);
		(*refs[i])->print();
		printf("]");
	}
}

/* Tasks */

Task::Task() {}
Task::~Task() {}


EvalTask::EvalTask(SchObjectRef _ref):step(0){ ref = new SchObjectRef(_ref); }
EvalTask::EvalTask(SchObjectRef _ref, int _step):step(_step){ ref = new SchObjectRef(_ref); }
EvalTask::~EvalTask(){ delete ref; }
enum Task::type EvalTask::getType(){ return EVALUATE; }
void EvalTask::print(){ printf("EvalTask step=%d ref=", step); (*ref)->print(); }

CallTask::CallTask(SchObjectRef _ref, int _n, int _step):n(_n),step(_step){ ref = new SchObjectRef(_ref); }
CallTask::~CallTask(){ delete ref; }
enum Task::type CallTask::getType(){ return CALL; }
void CallTask::print(){ printf("CallTask step=%d n=%d ref=", step, n); (*ref)->print(); }

ExecTask::ExecTask(SchObjectRef _ref, int _n, int _step):n(_n),step(_step){ ref = new SchObjectRef(_ref); }
ExecTask::~ExecTask(){ delete ref; }
enum Task::type ExecTask::getType(){ return EXECUTE; }
void ExecTask::print(){ printf("ExecTask step=%d n=%d ref=", step, n); (*ref)->print(); }

AddNamesTask::AddNamesTask(namemap_t * _map):map(_map){ }
AddNamesTask::~AddNamesTask(){ }
enum Task::type AddNamesTask::getType(){ return ADD_NAMES; }
void AddNamesTask::print(){ printf("AddNamesTask map="); map->print(); }

DelNamesTask::DelNamesTask(){ }
DelNamesTask::~DelNamesTask(){ }
enum Task::type DelNamesTask::getType(){ return DEL_NAMES; }
void DelNamesTask::print(){ printf("DelNamesTask");}

AliasTask::AliasTask(int _id, SchObjectRef _ref):id(_id){ ref = new SchObjectRef(_ref); }
AliasTask::~AliasTask(){ delete ref; }
enum Task::type AliasTask::getType(){ return ALIAS; }
void AliasTask::print(){ printf("AliasTask id=%d ref=", id); (*ref)->print();}

PrintTask::PrintTask(int _N):N(_N){}
PrintTask::~PrintTask(){}
enum Task::type PrintTask::getType(){ return PRINT; }
void PrintTask::print(){ printf("PrintTask N=%d", N);}

PushResultTask::PushResultTask(SchObjectRef _ref){ ref = new SchObjectRef(_ref); }
PushResultTask::~PushResultTask(){ delete ref; };
enum Task::type PushResultTask::getType(){ return PUSH_RESULT; }
void PushResultTask::print(){ printf("PushResultTask ref="); (*ref)->print(); }

NetworkTask::NetworkTask(enum net_type _gtype, int _subtype, int _player_id, int _quantity, int _price):
		gtype(_gtype), subtype(_subtype), player_id(_player_id), quantity(_quantity), price(_price) {}
NetworkTask::~NetworkTask(){};
enum Task::type NetworkTask::getType(){ return NETWORK; }
void NetworkTask::print(){
	const char * stype[]={
			"general",
			"market",
			"player",
			"auction",
			"perform",
			"wait"
	};
	printf("NetworkTask type=%s subtype=%d", stype[gtype], subtype);

	switch(gtype){
	case GENERAL : case MARKET : break;
	case PLAYER : case AUCTION: printf(" pid=%d", player_id); break;
	case PERFORM :
		switch(subtype){
		case BUY : case SELL : printf(" #=%d", quantity);
		case PROD : case BUILD : printf(" $=%d", price);
		break;
		}
		break;
	}
}
