/*
 * SpecialObjects.h
 *
 *  Created on: 26.04.2013
 *      Author: urandon
 */

#ifndef SPECIALOBJECTS_H_
#define SPECIALOBJECTS_H_

#include "SchObject.h"

namespace Special {
	enum special_type {
		// Scheme-specefied
		LAMBDA, DEFINE, IF, COND, DO, EVAL, LET, // 6
		LIST, QUOTE, CAR, CDR, ADD, // 11
		// Arithmetic & Logic
		PLUS, MINUS, MULTIPLY, DIVIDE, MODULO, // 16
		NOT_EQ, LESS, LESS_EQ, EQUAL, GREATER_EQ, GREATER, // 22
		//"#true", "#false",
		//"and", "or", "not",
		TRUE, FALSE, // 24
		AND, OR, NOT, // 27
		// network operators
		BUY, SELL, PROD, BUILD, ENDTURN, // 32
		PRINT, // 33
		// network operations
		_MY_ID, _TURN, _PLAYERS, _ACTIVE_PLAYERS, // 37
		_SUPPLY, _RAW_PRICE, _DEMAND, _PRODUCTION_PRICE, // 41
		_MONEY, _RAW, _PRODUCTION, _FACTORIES, _ACTIVE_FACTORIES, _MANUFACTURED, // 47
		// newtork auction results
		_RESULT_RAW_BOUGHT, _RESULT_RAW_PRICE, // 49
		_RESULT_PROD_SOLD, _RESULT_PROD_PRICE, // 51
		//new
		REDEFINE, WAIT // 53
	};
};

/* "Templates" */

class SchSpecialDontCall : virtual public SchSpecial {
public:
	SchSpecialDontCall();
	void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialDontExec : virtual public SchSpecial {
public:
	SchSpecialDontExec();
	void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialEvalArgs : virtual public SchSpecial {
public:
	SchSpecialEvalArgs();
	bool prepareArgs();
};

class SchSpecialDontEvalArgs : virtual public SchSpecial {
public:
	SchSpecialDontEvalArgs();
	bool prepareArgs();
};

class SchSpecialValencyZero : virtual public SchSpecial {
public:
	SchSpecialValencyZero();
	int valency();
};

class SchSpecialValencyOne : virtual public SchSpecial {
public:
	SchSpecialValencyOne();
	int valency();
};

class SchSpecialValencyTwo : virtual public SchSpecial {
public:
	SchSpecialValencyTwo();
	int valency();
};

class SchSpecialValencyThree : virtual public SchSpecial {
public:
	SchSpecialValencyThree();
	int valency();
};

class SchSpecialValencyVardic : virtual public SchSpecial {
public:
	SchSpecialValencyVardic();
	int valency();
};


/* Language-based object */

class SchSpecialLambda : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialLambda(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialDefine : public SchSpecialDontEvalArgs, public SchSpecialDontCall, public SchSpecialValencyTwo {
public:
	SchSpecialDefine(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialRedefine : public SchSpecialDontEvalArgs, public SchSpecialDontCall, public SchSpecialValencyTwo {
public:
	SchSpecialRedefine(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};


class SchSpecialIf : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyThree {
public:
	SchSpecialIf(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialCond : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialCond(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};


class SchSpecialDo : public SchSpecialDontEvalArgs, public SchSpecialDontCall, public SchSpecialValencyVardic {
public:
	SchSpecialDo(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialEval : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecialEval(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialLet : public SchSpecialDontEvalArgs, public SchSpecialValencyTwo {
public:
	SchSpecialLet(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialPrint : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyVardic {
public:
	SchSpecialPrint(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};


/* List-based objects */

class SchSpecialList : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialList(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialQuote : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialQuote(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialCar : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecialCar(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialCdr : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecialCdr(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialAdd : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialAdd(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};


/* Arithmetic-based objects */

class SchSpecialPlus : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialPlus(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialMinus : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic{
public:
	SchSpecialMinus(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialMultiply : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialMultiply(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialDivide : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialDivide(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialModulo : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialModulo(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

/* Comparation-based objects */

class SchSpecialNotEqual : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialNotEqual(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};


class SchSpecialLess : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialLess(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialLessEqual : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialLessEqual(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialEqual : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialEqual(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialGreaterEqual : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialGreaterEqual(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialGreater : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyTwo {
public:
	SchSpecialGreater(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

/* Logic-based objects */

class SchSpecialAnd : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialAnd(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialOr : public SchSpecialDontEvalArgs, public SchSpecialDontExec, public SchSpecialValencyVardic {
public:
	SchSpecialOr(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialNot : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecialNot(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};


/* Game-based objects-operations */

class SchSpecialBuy : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyTwo {
public:
	SchSpecialBuy(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialSell : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyTwo {
public:
	SchSpecialSell(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialProd : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyOne {
public:
	SchSpecialProd(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialBuild : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyOne {
public:
	SchSpecialBuild(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialEndturn : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyZero {
public:
	SchSpecialEndturn(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecialWait : public SchSpecialEvalArgs, public SchSpecialDontCall, public SchSpecialValencyZero {
public:
	SchSpecialWait(int line);
	virtual void execute(SchemeMachine & vm, int N, int step = 0);
};


/* Game-based objects-functions*/

class SchSpecial_MyId : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_MyId(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Turn : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_Turn(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Players : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_Players(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ActivePlayers : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_ActivePlayers(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Supply : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_Supply(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_RawPrice : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_RawPrice(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Demand : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_Demand(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ProductionPrice : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyZero {
public:
	SchSpecial_ProductionPrice(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Money : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_Money(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Raw : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_Raw(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Production : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_Production(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_Factories : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_Factories(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ActiveFactories : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_ActiveFactories(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ResultRawBought : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_ResultRawBought(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ResultRawPrice : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_ResultRawPrice(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ResultProdSold : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_ResultProdSold(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

class SchSpecial_ResultProdPrice : public SchSpecialEvalArgs, public SchSpecialDontExec, public SchSpecialValencyOne {
public:
	SchSpecial_ResultProdPrice(int line);
	virtual void call(SchemeMachine & vm, int N, int step = 0);
};

#endif /* SPECIALOBJECTS_H_ */
