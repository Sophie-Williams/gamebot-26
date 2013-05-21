/*
 * Errors.h
 *
 *  Created on: 15.04.2013
 *      Author: urandon
 */

#ifndef ERRORS_H_
#define ERRORS_H_

/*  This file contains throwable errors  */
#include "LexicalParser.h"

struct lexem;

class Error {
public:
	virtual ~Error();
	virtual void print(const char * filename);
};

class ErrorLine : public Error {
	int line;
public:
	ErrorLine(int line);
	int getLine();
	virtual void print(const char * filename);
};

class ContactDeveloperError : public Error { public: virtual void print(const char * filename); };
class ContactDeveloperErrorLine : public ErrorLine {
public:
	ContactDeveloperErrorLine(int line);
	virtual void print(const char * filename);
};


class NetworkError : public Error { public: virtual void print(const char * filename); } ;
	class NetworkErrorErrno : public NetworkError{
		int errno;
	public:
		NetworkErrorErrno(int errno);
		int getErrno();
		virtual void print(const char * filename);
	};
	class CannotCreateSocketError : public NetworkError { public: virtual void print(const char * filename); };
	class BadIPError : public NetworkError { public: virtual void print(const char * filename); } ;
	class CannotEstablishConnectionError : public NetworkError { public: virtual void print(const char * filename); } ;
	class DisconnectedError : public NetworkError { public: virtual void print(const char * filename); } ;


class BufferError : public Error { public: virtual void print(const char * filename); } ;
	class BufferOverflowError : public BufferError { public: virtual void print(const char * filename); } ;


class ParserError : public ErrorLine {
public:
	ParserError(int line);
	virtual void print(const char * filename);
};

class LexicalError : public ParserError {
public:
	LexicalError(int line);
	virtual void print(const char * filename);
};

	class BadSymbolError : public LexicalError {
		int ch;
	public:
		BadSymbolError(int line, int ch);
		int getSymbol();
		virtual void print(const char * filename);
	};

	class EOFinsideLexemError : public LexicalError {
	public:
		EOFinsideLexemError(int line);
		virtual void print(const char * filename);
	};

class UnregistredLexemError : public Error {
	char * lex;
	int length;
public:
	UnregistredLexemError(const char * lex);
	UnregistredLexemError(const UnregistredLexemError &e);
	~UnregistredLexemError();
	const char * getLex() const;
	virtual void print(const char * filename);
};

class UnknownLexemIdError : public Error { public: virtual void print(const char * filename); };

class SyntaxError : public ParserError {
public:
	SyntaxError(int line);
	virtual void print(const char * filename);
};

	class UnexpectedLexemError : public SyntaxError {
		int id_got;
		int id_expected;
	public:
		UnexpectedLexemError(int line, int got, int expected);
		int getGot() const;
		int getExpected() const;
		virtual void print(const char * filename, const char * sgot, const char * sexpected);
	};

	class UnballancedRightBrace : public SyntaxError {
	public:
		UnballancedRightBrace(int line);
		virtual void print(const char * filename);
	};

	class UnballancedLeftBrace : public SyntaxError {
	public:
		UnballancedLeftBrace(int line);
		virtual void print(const char * filename);
	};

	class EmptyCodeError : public SyntaxError{
	public:
		EmptyCodeError();
		virtual void print(const char * filename);
	};

	class UnexpectedEOFError : public SyntaxError{
	public:
		UnexpectedEOFError(int line);
		virtual void print(const char * filename);
	};

	class ExpectedEOFLexemFoundError : public SyntaxError{
	public:
		ExpectedEOFLexemFoundError(int line);
		virtual void print(const char * filename);
	};

	class SomethingExpectedError : public SyntaxError {
		lexem * found;
	public:
		SomethingExpectedError(int line, lexem * found);
		lexem * getLex();
		virtual void print(const char * filename, const char * sid);
	};

		class ObjectExpectedError : public SomethingExpectedError{
		public:
			ObjectExpectedError(int line, lexem * found);
			virtual void print(const char * filename, const char * sid);
		};

		class AtomExpectedError : public SomethingExpectedError{
		public:
			AtomExpectedError(int line, lexem * found);
			virtual void print(const char * filename, const char * sid);
		};

		class ListExpectedError : public SomethingExpectedError{
		public:
			ListExpectedError(int line, lexem * found);
			virtual void print(const char * filename, const char * sid);
		};

		class InternalExpectedError : public SomethingExpectedError{
		public:
			InternalExpectedError(int line, lexem * found);
			virtual void print(const char * filename, const char * sid);
		};


class RuntimeError : public ErrorLine {
public:
	RuntimeError(int line);
	virtual void print(const char * filename);
};

	class WrongNumberOfArgumentsError : public RuntimeError {
		int got;
		int expected;
	public:
		WrongNumberOfArgumentsError(int line, int got, int expected);
		int getGot() const;
		int getExpected() const;
		virtual void print(const char * filename);
	};

	class NotAFunctionCalledError : public RuntimeError {
	public:
		NotAFunctionCalledError(int line);
		virtual void print(const char * filename);
	};

	class UndefinedSymbolError : public RuntimeError {
		int id;
	public:
		UndefinedSymbolError(int line, int id);
		int getId();
		virtual void print(const char * filename, const char * sid);
	};

	class NotAnExecutableError : public RuntimeError {
	public:
		NotAnExecutableError(int line);
		virtual void print(const char * filename);
	};

	class StackUnderflowError : public ErrorLine {
	public:
		StackUnderflowError(int line);
		virtual void print(const char * filename);
	};
	class TaskStackUnderflowError : public StackUnderflowError {
	public:
		TaskStackUnderflowError(int line);
		virtual void print(const char * filename);
	};
	class ResultStackUnderflowError : public StackUnderflowError {
	public:
		ResultStackUnderflowError(int line);
		virtual void print(const char * filename);
	};

	class NamemapOverflorError : public Error { public: virtual void print(const char * filename);};

	class LocalNamespaceUnderflowError : public RuntimeError {
	public:
		LocalNamespaceUnderflowError(int line);
		virtual void print(const char * filename);
	};

class SpecialRuntimeError : public RuntimeError {
public:
	SpecialRuntimeError(int line);
	virtual void print(const char * filename);
};

	/* Laguage */

	class Special_LambdaListExpectedError : public SpecialRuntimeError {
	public:
		Special_LambdaListExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_LambdaNameExpectedError : public SpecialRuntimeError {
	public:
		Special_LambdaNameExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_DefineNameExpectedError : public SpecialRuntimeError {
	public:
		Special_DefineNameExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_RedefineNameExpectedError : public SpecialRuntimeError {
	public:
		Special_RedefineNameExpectedError(int line);
		virtual void print(const char * filename);
	};


	class Special_CondListExpectedError : public SpecialRuntimeError {
	public:
		Special_CondListExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_CondNoChoosenError : public SpecialRuntimeError {
	public:
		Special_CondNoChoosenError(int line);
		virtual void print(const char * filename);
	};

	class Special_CondObjectExpectedError : public SpecialRuntimeError {
	public:
		Special_CondObjectExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_CondIntegerExpectedError : public SpecialRuntimeError {
	public:
		Special_CondIntegerExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_LetListExpectedError : public SpecialRuntimeError {
	public:
		Special_LetListExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_LetPairExpectedError : public SpecialRuntimeError {
	public:
		Special_LetPairExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_LetNameExpectedError : public SpecialRuntimeError {
	public:
		Special_LetNameExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_CarListExpectedError : public SpecialRuntimeError {
	public:
		Special_CarListExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_CdrListExpectedError : public SpecialRuntimeError {
	public:
		Special_CdrListExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_AddListExpectedError : public SpecialRuntimeError {
	public:
		Special_AddListExpectedError(int line);
		virtual void print(const char * filename);
	};


	/* Arithmetic */

	class Special_PlusNumericExpectedError : public SpecialRuntimeError {
	public:
		Special_PlusNumericExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_MinusNumericExpectedError : public SpecialRuntimeError {
	public:
		Special_MinusNumericExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_MultiplyNumericExpectedError : public SpecialRuntimeError {
	public:
		Special_MultiplyNumericExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_DivideNumericExpectedError : public SpecialRuntimeError {
	public:
		Special_DivideNumericExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_DivideByZeroError : public SpecialRuntimeError {
	public:
		Special_DivideByZeroError(int line);
		virtual void print(const char * filename);
	};

	class Special_DivideExpectedAtLeastOneArgumentError : public SpecialRuntimeError {
	public:
		Special_DivideExpectedAtLeastOneArgumentError(int line);
		virtual void print(const char * filename);
	};

	class Special_ModuloIntegerExpectedError : public SpecialRuntimeError {
	public:
		Special_ModuloIntegerExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_ModuloByZeroError : public SpecialRuntimeError {
	public:
		Special_ModuloByZeroError(int line);
		virtual void print(const char * filename);
	};

	/* Comparation */

	class Special_CompareNumericExpectedError : public SpecialRuntimeError {
	public:
		Special_CompareNumericExpectedError(int line);
		virtual void print(const char * filename);
	};

	/* Logic */

	class Special_LogicIntExpectedError : public SpecialRuntimeError {
	public:
		Special_LogicIntExpectedError(int line);
		virtual void print(const char * filename);
	};

	/* Network */

	class Special_NetworkIntQuantityExpectedError : public SpecialRuntimeError {
	public:
		Special_NetworkIntQuantityExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_NetworkIntPriceExpectedError : public SpecialRuntimeError {
	public:
		Special_NetworkIntPriceExpectedError(int line);
		virtual void print(const char * filename);
	};

	class Special_NetworkIntPlayerExpectedError : public SpecialRuntimeError {
	public:
		Special_NetworkIntPlayerExpectedError(int line);
		virtual void print(const char * filename);
	};

class GameOver : public Error {
public:
	virtual void print(const char * filename);
};

#endif /* ERRORS_H_ */
