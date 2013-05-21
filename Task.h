/*
 * Task.h
 *
 *  Created on: 22.04.2013
 *      Author: urandon
 */

#ifndef TASK_H_
#define TASK_H_

#include "SchObject.h"

class SchObjectRef;


struct namemap_t {
	const static int DEFAULT;
	int allocated;
	int size;
	int * ids;
	SchObjectRef ** refs;

	namemap_t(int allocated);
	~namemap_t();

	void add(int id, SchObjectRef ref);
	SchObjectRef * searchRef(int id); // return NULL if no such id in the namemap
	void print();
};


struct Task {
	enum type {
		EVALUATE, CALL, EXECUTE,
		PUSH_RESULT,
		ADD_NAMES, DEL_NAMES, ALIAS,
		NETWORK,
		PRINT
	};

	Task();
	virtual ~Task();

	virtual enum type getType() = 0;
	virtual void print() = 0;
};

struct EvalTask : public Task {
	SchObjectRef * ref;
	int step;

	EvalTask(SchObjectRef ref);
	EvalTask(SchObjectRef ref, int step);
	~EvalTask();

	enum type getType();
	void print();
};

struct CallTask : public Task {
	SchObjectRef * ref;
	int n;
	int step;

	CallTask(SchObjectRef ref, int n, int step = 0);
	~CallTask();

	enum type getType();
	void print();
};

struct ExecTask : public Task {
	SchObjectRef * ref;
	int n;
	int step;

	ExecTask(SchObjectRef ref, int n, int step = 0);
	~ExecTask();

	enum type getType();
	void print();
};

struct AddNamesTask : public Task{
	namemap_t * map;

	AddNamesTask(namemap_t * map);
	~AddNamesTask();

	enum type getType();
	void print();
};

struct DelNamesTask : public Task{
	DelNamesTask();
	~DelNamesTask();

	enum type getType();
	void print();
};

struct AliasTask : public Task{
	int id;
	SchObjectRef * ref;

	AliasTask(int id, SchObjectRef ref);
	~AliasTask();
	enum type getType();
	void print();
};

struct PrintTask : public Task{
	int N;

	PrintTask(int N);
	~PrintTask();
	enum type getType();
	void print();
};

struct PushResultTask : public Task{
	SchObjectRef * ref;

	PushResultTask(SchObjectRef ref);
	~PushResultTask();

	enum type getType();
	void print();
};

struct NetworkTask : public Task{
	enum net_type {
		GENERAL, MARKET, PLAYER, AUCTION,
		PERFORM
	};

	enum general_net_type {
		MY_ID, TURN, PLAYERS, ACTIVE_PLAYERS,
	};
	enum market_net_type {
		MARKET_STATE, PRODUCTION_PRICE, RAW_PRICE, SUPPLY, DEMAND,
	};
	enum player_net_type {
		MONEY, ACTIVE_FACTORIES, FACTORIES, PRODUCTION, RAW
	};
	enum auction_net_type {
		RESULT_RAW_BOUGHT, RESULT_RAW_PRICE,
		RESULT_PROD_SOLD, RESULT_PROD_PRICE
	};
	enum perform_net_type {
		BUY, SELL, PROD, BUILD, ENDTURN, WAIT
	};

	enum net_type gtype;
	int subtype;

	int player_id;
	int quantity;
	int price;

	NetworkTask(enum net_type gtype, int subtype, int player_id = 0, int quantity = 0, int price = 0);
	~NetworkTask();

	enum type getType();
	void print();
};

#endif /* TASK_H_ */
