/*
 * SyntaxParser.h
 *
 *  Created on: 15.04.2013
 *      Author: urandon
 */

#ifndef IMPSYNTAXPARSER_H_
#define IMPSYNTAXPARSER_H_

#include "ImpLexicalParser.h"


class ImpSyntaxParser {
public:
	ImpSyntaxParser(int fd);
	virtual ~ImpSyntaxParser();

	enum atom_type {
		SQBRACE_LEFT, SQBRACE_RIGHT, RDBRACE_LEFT, RDBRACE_RIGHT,
		FIGBRACE_LEFT, FIGBRACE_RIGHT,
		ASSIGN, DOUBLEDOT, DOT_N_COMMA, COMMA,
		DEFINITION,
		IF, THEN, ELSE, GOTO,
		BUY, SELL, PROD, BUILD, ENDTURN,
		PRINT,
		AND, OR, NOT,
		LESS, GREATER, EQUAL,
		PLUS, MINUS,
		DIVISION, MUTLIPLY, MODULO,
		NUMERIC, STRING, VARIABLE, FUNCTION, LABEL
	};

	static const char * atom_essence[];
	static const int PREDEFINED_ATOMS;

	struct atom {
		enum atom_type type;
		int id;
		int line;

		atom(enum atom_type type, int id, int line);
		atom(const lexem & lex);
		atom(const atom & mAtom);
	};

	struct code_t {
		static const int DEFAULT_SIZE = 64;
		atom ** data;
		int size;
		int allocated;

		code_t();
		~code_t();

		void push(atom * mAtom);
	};

private:
	ImpLexicalParser lexical;
	code_t code;
	int lo,hi;

	atom * current();
	atom * next();
	atom * prev();

	/* language-sensitive recursive descent methods */
	void Program();
	void Definition();
	void Code();
	void Variable();
	void Array();
	void Variable_();

	void Operator();
	void Complex_operator();
	void Assign_operator();
	void If_opetator();
	void Goto_operator();
	void Game_operator();
	void Print_operator();
	void Labeled_operator();

	void Game0();
	void Game1();
	void Game2();

	void P_list();
	void P_node();

	void Expression();
	void Comparator();
	void Summand();
	void Multiplier();
	void Term();

	void Func_call();
	void Func_args();
};
#endif /* IMPSYNTAXPARSER_H_ */
