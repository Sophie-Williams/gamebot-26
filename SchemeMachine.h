/*
 * SchemeMachine.h
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#ifndef SCHEMEMACHINE_H_
#define SCHEMEMACHINE_H_

#include "SchObject.h"
#include "SchSyntaxParser.h"
#include "Task.h"
#include "GameClient.h"

class SchObject;
class SchObjectRef;
struct Task;
class namemap_t;
class GameClient;

class SchemeMachine {
	friend class SchName;
public:
	SchemeMachine(const char * ip, int port, struct timeval default_timeval);

	struct result_stack_t {
		const static int DEFAULT;
		int size, allocated;
		int actual_top;
		SchObjectRef ** data;

		result_stack_t();
		~result_stack_t();
		void push(SchObjectRef ref);
		SchObjectRef ** pop(int N, int last_line);
		void print();
	};

	struct task_stack_t{
		const static int DEFAULT;
		int size, allocated;
		Task ** data;

		task_stack_t();
		~task_stack_t();
		void push(Task * task);
		bool isEmpty();
		Task * pop(int last_line);
		void print();
	};

	/* names */

	struct global_names_t {
		static const int DEFAULT;
		int size, allocated;
		int * ids;
		SchObjectRef ** refs;

		global_names_t();
		~global_names_t();
		void push(int id, const SchObjectRef & ref);
		SchObjectRef * searchRef(int id);
	};

	struct local_names_t {
		namemap_t * current;
		local_names_t * prev;
	};


	virtual ~SchemeMachine();

	void addTask(Task * task);
	void launch(bool verbose = false);

	void pushResult(SchObjectRef ref);
	SchObjectRef ** popResult(int N);
private:
	task_stack_t tasks;
	result_stack_t results;
	global_names_t global_names;
	local_names_t * local_names;
	int current_line;
	int cycle;

	SchObjectRef getRef(int id); // from local and global namespaces;
	int last_line;

	void performTask();

	GameClient * client;
};

#endif /* SCHEMEMACHINE_H_ */
