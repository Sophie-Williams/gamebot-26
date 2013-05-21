/*
 * LexicalParser.h
 *
 *  Created on: 07.04.2013
 *      Author: urandon
 */

#ifndef LEXICALPARSER_H_
#define LEXICALPARSER_H_

#include "Errors.h"

struct lexem {
	int type;
	int id;
	int line;

	lexem(int id, int type, int line);
	lexem(const lexem & lex);
	virtual ~lexem();
};


class LexicalParser {
public:
	LexicalParser();
	virtual ~LexicalParser();

	struct buffer_t {
		static const int DEFAULT_SIZE = 64;
		char * data;
		int size;
		int allocated;

		buffer_t();
		~buffer_t();

		void push(char ch);
		void flush();
	};

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

	class map_t {
		char ** strings;
		int size, allocated;
	public:
		map_t();
		~map_t();
		int push(const char * s, int length);
		int push(const char * s);
		int getId(const char * s);
		const char * getString(int id);
	};

	virtual lexem * push(int ch) = 0;
	virtual bool isEmpty() = 0;
	virtual const char * getString(int id) = 0;
};

#endif /* LEXICALPARSER_H_ */
