/*
 * SchLexicalParser.h
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#ifndef SCHLEXICALPARSER_H_
#define SCHLEXICALPARSER_H_

#include "LexicalParser.h"

class SchLexicalParser : public LexicalParser {
public:
	SchLexicalParser();
	SchLexicalParser(const char * const * worldlist, int length);
	virtual ~SchLexicalParser();

	enum state_t {
		H, I, F, S, N, SEP
	};

	enum lexem_type {
		INTEGER,
		FLOAT,
		STRING,
		SPECIAL,
		NAME,
		LBRACE,
		RBRACE
	};

	lexem * push(int ch);
	bool isEmpty();
	const char * getString(int id);

private:
	buffer_t buffer;
	enum state_t state;
	enum lexem_type current_type;
	map_t map;

	int line;
	int last_line;
	int predefined_length;
	bool str_slash;

	lexem * ret(enum state_t state);
};

#endif /* SCHLEXICALPARSER_H_ */
