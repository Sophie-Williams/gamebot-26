/*
 * SchSyntaxParser.h
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#ifndef SCHSYNTAXPARSER_H_
#define SCHSYNTAXPARSER_H_

#include "SchLexicalParser.h"
#include "SchObject.h"

class SchObjectRef;
class SchObject;

struct list_t;

class SchSyntaxParser {
public:
	SchSyntaxParser(/*int fd*/);
	~SchSyntaxParser();

	struct lex_storage_t {
		static const int DEFAULT_SIZE = 64;
		lexem ** data;
		int size;
		int allocated;

		lex_storage_t();
		~lex_storage_t();

		void push(const lexem & lexem);
	};

	SchObjectRef parse(); // @deprecated
	SchObjectRef trueParse();
	void reset();
	void receive(int fd);

	const char * getLexString(int id);

private:
	SchLexicalParser lexical;
	lex_storage_t storage;

	int ptr;
	lexem * previous();
	lexem * current();
	lexem * next();

	SchObjectRef rec_obj();
	SchObjectRef rec_list();
	list_t * rec_internal();
	SchObjectRef rec_atom();

	SchObjectRef rec_special_atom();
};

#endif /* SCHSYNTAXPARSER_H_ */
