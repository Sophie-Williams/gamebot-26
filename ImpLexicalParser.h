/*
 * ImpLexicalParser.h
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#ifndef IMPLEXICALPARSER_H_
#define IMPLEXICALPARSER_H_

#include "LexicalParser.h"

class ImpLexicalParser : public LexicalParser {
public:
	ImpLexicalParser();
	virtual ~ImpLexicalParser();

	enum state_t {
		H, N, I, K, A, S, SEP
	};

	enum lexem_type {
		SEPARATOR,
		EQUALITY,
		NUMERIC,
		STRING,
		VARIABLE,
		LABEL,
		LABELREF,
		FUNCTION,
		KEYWORD
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
	bool str_slash;

	lexem * ret(enum state_t state);

	static bool isseparator(char ch);
};

#endif /* IMPLEXICALPARSER_H_ */
