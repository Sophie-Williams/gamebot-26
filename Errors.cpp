/*
 * Errors.cpp
 *
 *  Created on: 15.04.2013
 *      Author: urandon
 */

#include "Errors.h"
#include <string.h>
#include <cstdlib>
#include <cstdio>

Error::~Error() { };

ErrorLine::ErrorLine(int _line):line(_line){};
int ErrorLine::getLine(){ return line; }

ContactDeveloperErrorLine::ContactDeveloperErrorLine(int _line):ErrorLine(_line){ };

NetworkErrorErrno::NetworkErrorErrno(int _errno):errno(_errno){ };
int NetworkErrorErrno::getErrno(){ return errno; }

ParserError::ParserError(int _line):ErrorLine(_line) { };

LexicalError::LexicalError(int _line):ParserError(_line) { };

BadSymbolError::BadSymbolError(int _line, int _ch):LexicalError(_line), ch(_ch) { };
int BadSymbolError::getSymbol(){ return ch; }

EOFinsideLexemError::EOFinsideLexemError(int _line):LexicalError(_line) { };

UnregistredLexemError::UnregistredLexemError(const char * _lex){
	length = strlen(_lex) + 1;
	lex = (char *) malloc(length * sizeof(char));
	strcpy(lex, _lex);
};

UnregistredLexemError::UnregistredLexemError(const UnregistredLexemError &e){
	length = e.length;
	lex = (char *) malloc(length * sizeof(char));
	strcpy(lex, e.lex);
};

UnregistredLexemError::~UnregistredLexemError(){ free(lex); }

const char * UnregistredLexemError::getLex() const { return lex; }

/* Syntax Errors */

SyntaxError::SyntaxError(int _line):ParserError(_line) { };

UnexpectedLexemError::UnexpectedLexemError(int line, int got, int expected):
		SyntaxError(line), id_got(got), id_expected(expected) { };

int UnexpectedLexemError::getGot() const { return id_got; }
int UnexpectedLexemError::getExpected() const { return id_got; }


UnballancedRightBrace::UnballancedRightBrace(int _line):SyntaxError(_line) { };
UnballancedLeftBrace::UnballancedLeftBrace(int _line):SyntaxError(_line) { };

EmptyCodeError::EmptyCodeError():SyntaxError(1) { };

SomethingExpectedError::SomethingExpectedError(int _line, lexem * _found):
		SyntaxError(_line), found(_found) { };
lexem * SomethingExpectedError::getLex(){ return found; }

ExpectedEOFLexemFoundError::ExpectedEOFLexemFoundError(int _line):
		SyntaxError(_line) { };

UnexpectedEOFError::UnexpectedEOFError(int _line):
		SyntaxError(_line) { };

ObjectExpectedError::ObjectExpectedError(int _line, lexem * _found):
		SomethingExpectedError(_line, _found){ };

AtomExpectedError::AtomExpectedError(int _line, lexem * _found):
		SomethingExpectedError(_line, _found){ };

ListExpectedError::ListExpectedError(int _line, lexem * _found):
		SomethingExpectedError(_line, _found){ };

InternalExpectedError::InternalExpectedError(int _line, lexem * _found):
		SomethingExpectedError(_line, _found){ };

//Internal_ExpectedError::Internal_ExpectedError(int _line, lexem * _found):
//		SomethingExpectedError(_line, _found){ };


/* Runtime Errors */

RuntimeError::RuntimeError(int _line):ErrorLine(_line) { };

WrongNumberOfArgumentsError::WrongNumberOfArgumentsError(int _line, int _got, int _expected):
		RuntimeError(_line), got(_got), expected(_expected) { };
int WrongNumberOfArgumentsError::getGot() const { return got; }
int WrongNumberOfArgumentsError::getExpected() const { return expected; }

NotAFunctionCalledError::NotAFunctionCalledError(int _line):RuntimeError(_line) { };

NotAnExecutableError::NotAnExecutableError(int _line):RuntimeError(_line){ };

UndefinedSymbolError::UndefinedSymbolError(int _line, int _id):
		RuntimeError(_line), id(_id) { };
int UndefinedSymbolError::getId(){ return id; }

LocalNamespaceUnderflowError::LocalNamespaceUnderflowError(int _line):
		RuntimeError(_line) { };

StackUnderflowError::StackUnderflowError(int _line):
				ErrorLine(_line) { };
TaskStackUnderflowError::TaskStackUnderflowError(int _line):
		StackUnderflowError(_line){ };
ResultStackUnderflowError::ResultStackUnderflowError(int _line):
		StackUnderflowError(_line){ };

SpecialRuntimeError::SpecialRuntimeError(int _line):RuntimeError(_line){ };
/*language*/
Special_LambdaListExpectedError::Special_LambdaListExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_LambdaNameExpectedError::Special_LambdaNameExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_DefineNameExpectedError::Special_DefineNameExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_RedefineNameExpectedError::Special_RedefineNameExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_CondListExpectedError::Special_CondListExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_CondNoChoosenError::Special_CondNoChoosenError(int _line):SpecialRuntimeError(_line){ };
Special_CondObjectExpectedError::Special_CondObjectExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_CondIntegerExpectedError::Special_CondIntegerExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_LetListExpectedError::Special_LetListExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_LetPairExpectedError::Special_LetPairExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_LetNameExpectedError::Special_LetNameExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_CarListExpectedError::Special_CarListExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_CdrListExpectedError::Special_CdrListExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_AddListExpectedError::Special_AddListExpectedError(int _line):SpecialRuntimeError(_line){ };
/*arithmetic*/
Special_PlusNumericExpectedError::Special_PlusNumericExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_MinusNumericExpectedError::Special_MinusNumericExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_MultiplyNumericExpectedError::Special_MultiplyNumericExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_DivideNumericExpectedError::Special_DivideNumericExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_DivideByZeroError::Special_DivideByZeroError(int _line):SpecialRuntimeError(_line){ };
Special_DivideExpectedAtLeastOneArgumentError::Special_DivideExpectedAtLeastOneArgumentError(int _line):SpecialRuntimeError(_line){ };
Special_ModuloIntegerExpectedError::Special_ModuloIntegerExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_ModuloByZeroError::Special_ModuloByZeroError(int _line):SpecialRuntimeError(_line){ };
/*cmp*/
Special_CompareNumericExpectedError::Special_CompareNumericExpectedError(int _line):SpecialRuntimeError(_line){ };
/*logic*/
Special_LogicIntExpectedError::Special_LogicIntExpectedError(int _line):SpecialRuntimeError(_line){ };
/*network*/
Special_NetworkIntQuantityExpectedError::Special_NetworkIntQuantityExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_NetworkIntPriceExpectedError::Special_NetworkIntPriceExpectedError(int _line):SpecialRuntimeError(_line){ };
Special_NetworkIntPlayerExpectedError::Special_NetworkIntPlayerExpectedError(int _line):SpecialRuntimeError(_line){ };

/* virtual print() methods
 *
 * */

void Error::print(const char * filename){ fprintf(stderr, "[%s]", filename); }
void ErrorLine::print(const char * filename){ fprintf(stderr, "[%s::%d]", filename, line); }
void ContactDeveloperError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Contact Developer and take him your source code\n");
}
void ContactDeveloperErrorLine::print(const char * filename){
	ErrorLine::print(filename);
	fprintf(stderr, "Contact Developer and take him your source code. He would be more happy if you say him the line also\n");
}
void NetworkError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Network error: ");
}
void NetworkErrorErrno::print(const char * filename){
	NetworkError::print(filename);
	fprintf(stderr, "errno %d got: \"%s\"", errno, 	strerror(errno));
}
void CannotCreateSocketError::print(const char * filename){
	NetworkError::print(filename);
	fprintf(stderr, "cannot create socket");
}
void BadIPError::print(const char * filename){
	NetworkError::print(filename);
	fprintf(stderr, "bad IP adress");
}
void CannotEstablishConnectionError::print(const char * filename){
	NetworkError::print(filename);
	fprintf(stderr, "cannot establish connection");
}
void DisconnectedError::print(const char * filename){
	NetworkError::print(filename);
	fprintf(stderr, "disconnected");
}
void BufferError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Some problem was caused with buffer");
}
void BufferOverflowError::print(const char * filename){
	BufferError::print(filename);
	fprintf(stderr, ": buffer overflow");
}
/*Parser ::print(const char * filename)*/

void ParserError::print(const char * filename){
	ErrorLine::print(filename);
	fprintf(stderr, "Code Analys error: ");
}
void LexicalError::print(const char * filename){
	ParserError::print(filename);
	fprintf(stderr, "(lexical) ");
}
void SyntaxError::print(const char * filename){
	ParserError::print(filename);
	fprintf(stderr, "(syntax) ");
}
void BadSymbolError::print(const char * filename){
	LexicalError::print(filename);
	fprintf(stderr, "an unexpected symbol '%c'", getSymbol());
}
void EOFinsideLexemError::print(const char * filename){
	LexicalError::print(filename);
	fprintf(stderr, "an unexpexted EOF in the file");
}

void UnregistredLexemError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Unregistred lexem <%s>. Contact developer please", getLex());
}
void UnknownLexemIdError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Unregistred lexem ID. Contact developer please");
}

void UnexpectedLexemError::print(const char * filename, const char * sgot, const char * sexpected){
	SyntaxError::print(filename);
	fprintf(stderr, "unexpected lexem found: got \"%s\" with id=%d, expected \"%s\" with id=%d",
			sgot, getGot(), sexpected, getExpected());
}

void UnballancedRightBrace::print(const char * filename){
	SyntaxError::print(filename);
	fprintf(stderr, "unballanced right brace");
}
void UnballancedLeftBrace::print(const char * filename){
	SyntaxError::print(filename);
	fprintf(stderr, "unballanced left brace");
}
///
void EmptyCodeError::print(const char * filename){
	SyntaxError::print(filename);
	fprintf(stderr, "code is empty");
}
void UnexpectedEOFError::print(const char * filename){
	SyntaxError::print(filename);
	fprintf(stderr, "unexpected EOF found");
}
void ExpectedEOFLexemFoundError::print(const char * filename){
	SyntaxError::print(filename);
	fprintf(stderr, "expected EOF, but lexem found");
}

void SomethingExpectedError::print(const char * filename, const char * sid){
	SyntaxError::print(filename);
	fprintf(stderr, "found \"%s\" with id=%d, but ", sid, getLex()->id);
}
void ObjectExpectedError::print(const char * filename, const char * sid){
	SomethingExpectedError::print(filename, sid);
	fprintf(stderr, "<object> expected");
}
void AtomExpectedError::print(const char * filename, const char * sid){
	SomethingExpectedError::print(filename, sid);
	fprintf(stderr, "<atom> expected");
}
void ListExpectedError::print(const char * filename, const char * sid){
	SomethingExpectedError::print(filename, sid);
	fprintf(stderr, "<list> expected");
}
void InternalExpectedError::print(const char * filename, const char * sid){
	SomethingExpectedError::print(filename, sid);
	fprintf(stderr, "<internal> expected");
}

/* Runtime :: print(filename) */

void RuntimeError::print(const char * filename){
	ErrorLine::print(filename);
	fprintf(stderr, "Runtime Error: ");
}

void WrongNumberOfArgumentsError::print(const char * filename){
	RuntimeError::print(filename);
	fprintf(stderr, "wrong number of arguments: got %d, expected ", getGot());
	if(getExpected() != -1){
		fprintf(stderr, "%d\n", getExpected());
	} else {
		fprintf(stderr, "nonzero arguments");
	}
}

void NotAFunctionCalledError::print(const char * filename){
	RuntimeError::print(filename);
	fprintf(stderr, "not a function called");
}
void NotAnExecutableError::print(const char * filename){
	RuntimeError::print(filename);
	fprintf(stderr, "not an executable was executed\n");
}
void UndefinedSymbolError::print(const char * filename, const char * sid){
	RuntimeError::print(filename);
	fprintf(stderr, "symbol \"%s\" with id=%d hasn't any defenition in this scope",
			sid, getId());
}

void StackUnderflowError::print(const char * filename){
	ErrorLine::print(filename);
	fprintf(stderr, "Virtual Machine's ");
}
void TaskStackUnderflowError::print(const char * filename){
	StackUnderflowError::print(filename);
	fprintf(stderr, "task stack underflow");
}
void ResultStackUnderflowError::print(const char * filename){
	StackUnderflowError::print(filename);
	fprintf(stderr, "result stack underflow");
}

void NamemapOverflorError::print(const char * filename){
	Error::print(filename);
	fprintf(stderr, "Namemap was created wrong (overflow)");
}
void LocalNamespaceUnderflowError::print(const char * filename){
	RuntimeError::print(filename);
	fprintf(stderr, "local namespace underflow");
}

/* SpecialRuntime ::print(filename) */
void SpecialRuntimeError::print(const char * filename){
	RuntimeError::print(filename);
	fprintf(stderr, "<special> ");
}

void Special_LambdaListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "lambda: parametric list expected");
}
void Special_LambdaNameExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "lambda: name expected");
}
void Special_DefineNameExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "define: name expected");
}
void Special_RedefineNameExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "redefine: name expected");
}
void Special_CondListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "cond: condition list expected");
}
void Special_CondNoChoosenError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "cond: no a condition choosen");
}
void Special_CondObjectExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "cond: object expected");
}
void Special_CondIntegerExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "cond: integer expected");
}
void Special_LetListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "let: defenition list expected");
}
void Special_LetPairExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "let: \"name ref\" pair expected");
}
void Special_LetNameExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "let: name expected");
}
void Special_CarListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "car: list expected");
}
void Special_CdrListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "cdr: list expected");
}
void Special_AddListExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "add: list expected");
}

/*special arithmetic print()*/

void Special_PlusNumericExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "<+>: numeric expected");
}
void Special_MinusNumericExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "<->: numeric expected");
}
void Special_MultiplyNumericExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "<*>: numeric expected");
}
void Special_DivideNumericExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "</>: numeric expected");
}
void Special_ModuloIntegerExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "<%%>: integer expected");
}
void Special_DivideByZeroError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "</>: division by zero");
}
void Special_DivideExpectedAtLeastOneArgumentError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "</>: at least one argument expected");
}
void Special_ModuloByZeroError::print(const char * filename){
	SpecialRuntimeError::print(filename);
		fprintf(stderr, "<%%>: division by zero");
}

void Special_CompareNumericExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "comparation: numeric expected");
}
void Special_LogicIntExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "logic: integer expected");
}

/*spec network ::print()*/

void Special_NetworkIntQuantityExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "network operation: integer quantity parameter expected");
}
void Special_NetworkIntPriceExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "network operation: integer price parameter expected");
}
void Special_NetworkIntPlayerExpectedError::print(const char * filename){
	SpecialRuntimeError::print(filename);
	fprintf(stderr, "network operation: integer player parameter expected");
}



void GameOver::print(const char * filename){
	fprintf(stderr, "The Game is over");
}
