/*
 * SchObject.h
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#ifndef SCHOBJECT_H_
#define SCHOBJECT_H_

#include "SchemeMachine.h"
#include <unistd.h>

class SchemeMachine;
class SchObjectRef;

class SchObject {
public:
	SchObject(int line);
	virtual ~SchObject();

	enum type_t {
		INTEGER,
		FLOAT,
		STRING,
		LIST,
		NAME,
		FUNCTION,
		SPECIAL
	};

	friend class SchObjectRef;

	virtual void evaluate(SchemeMachine & vm, int step = 0) = 0;
	virtual void call(SchemeMachine & vm, int N, int step = 0) = 0;
	virtual void execute(SchemeMachine & vm, int N, int step = 0) = 0;

	virtual enum type_t getType() = 0;
	int getLine();
	virtual void print() = 0;

	int getId();
	int getRefcount();
private:
	int refcount;
	int line;

	static int max_id;
	int my_id;
};

class SchObjectRef {
	SchObject * obj;
public:
	SchObjectRef(SchObject & obj);
	SchObjectRef(SchObject * obj);
	SchObjectRef(const SchObjectRef & ref);
	~SchObjectRef();

	SchObject * operator->();
	SchObject & operator* ();
};

/* Constants */

class SchConstant : public SchObject {
public:
	SchConstant(int line);

	virtual void evaluate(SchemeMachine & vm, int step = 0);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchInteger : public SchConstant {
	int n;
public:
	SchInteger(int line, int n);
	enum type_t getType();
	int getN();
	virtual void print();
};

class SchTrue : public SchInteger {
public:
	SchTrue(int line);
};

class SchFalse : public SchInteger {
public:
	SchFalse(int line);
};

class SchFloat : public SchConstant {
	double f;
public:
	SchFloat(int line, double f);
	enum type_t getType();
	double getF();
	virtual void print();
};

class SchString : public SchConstant {
	const char * s;
public:
	SchString(int line, const char *s);
	enum type_t getType();
	const char * getS();
	virtual void print();
};

/* List */

struct list_t{
	SchObjectRef * node;
	list_t * next;
	int refcount;

	list_t();
	~list_t();
};

class SchList : public SchObject {
public:
	SchList(int line, list_t * list, int length);
	SchList(int line, list_t * list);
	/* should be guaranteed that "list_t list" wouldn't be deleted by chineese
	 * this list will be deleted by destructor */
	~SchList();
	enum type_t getType();

	virtual void evaluate(SchemeMachine & vm, int step = 0);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
	virtual void print();

	list_t * getList();
	int getLength();
private:
	list_t * list;
	int length;
	static int tabs;
};

/* Specials, Names and Functions */

class SchName : public SchObject {
	int id;
public:
	SchName(int line, int id);
	enum type_t getType();
	virtual void evaluate(SchemeMachine & vm, int step = 0);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
	virtual void print();

	SchObjectRef getRef(SchemeMachine &vm);

	int getId();
};

class SchFunction : public SchObject {
	static int top_id;
	int _id;
	int * ids;
	int length;
	SchObjectRef body;
public:
	SchFunction(int line, SchObjectRef body, const int * ids, int length);
	SchFunction(int line, SchObjectRef body, int * ids, int length);
	~SchFunction();

	enum type_t getType();
	virtual void evaluate(SchemeMachine & vm, int step = 0);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
	virtual void print();
	int getLength();
};

class SchSpecial : public SchObject {
	int id;
public:
	SchSpecial(int line, int id);

	enum type_t getType();
	virtual void evaluate(SchemeMachine & vm, int step = 0);
	virtual void print();

	virtual bool prepareArgs() = 0;
	virtual int valency() = 0; // -1 is vardic
};


class Predefined {
public:
	static const char * atoms[];
	static const int length;
};

template<typename T, size_t N>
inline size_t LengthOf(T (&x)[N]){
	return N;
}


#endif /* SCHOBJECT_H_ */
