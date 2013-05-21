/*
 * LexicalParser.cpp
 *
 *  Created on: 07.04.2013
 *      Author: urandon
 */

#include "LexicalParser.h"
#include <cstdlib>
#include <ctype.h>
#include <cstdio>
#include <string.h>

LexicalParser::LexicalParser() { }
LexicalParser::~LexicalParser() { }

/* LexicalParere::buffer_t */

void LexicalParser::buffer_t::push(char ch) {
	int newsize = size + 1;

	if(newsize > allocated){
		allocated *= 2;
		data = (char *) realloc(data, allocated * sizeof(* data));
	}

	data[size] = ch;
	size = newsize;
}

void LexicalParser::buffer_t::flush() {
	size = 0;
	if(allocated != DEFAULT_SIZE){
		allocated = DEFAULT_SIZE;
		free(data);
		data = (char *) malloc(allocated * sizeof(char));
	}
}

LexicalParser::buffer_t::buffer_t():size(0),allocated(DEFAULT_SIZE) {
	data = (char *) malloc(DEFAULT_SIZE * sizeof(char));
}

LexicalParser::buffer_t::~buffer_t() {
	free(data);
}


/* LexicalParser::lexem */

lexem::lexem(int mid, int mtype, int mline):
			type(mtype),id(mid),line(mline) {} ;

lexem::lexem(const lexem & lex) {
	type = lex.type;
	id = lex.id;
	line = lex.line;
}

lexem::~lexem() {}


/* LexicalParser::map */
LexicalParser::map_t::map_t():size(0) {
	const int DEFAULT = 64;

	allocated = DEFAULT;
	strings = (char **) malloc(allocated * sizeof(*strings));
}

LexicalParser::map_t::~map_t(){
	for(int i = 0; i < size; ++i){
		free(strings[i]);
	}
	free(strings);
}

const char * LexicalParser::map_t::getString(int id){
	if(id < 0 || id >= size){
		throw UnknownLexemIdError();
	} else {
		return strings[id];
	}
}

int LexicalParser::map_t::getId(const char *s){
	for(int i = 0; i < size; ++i){
		if(strcmp(strings[i],s)){
			return i;
		}
	}

	throw UnregistredLexemError(s);
}

int LexicalParser::map_t::push(const char *s, int length){
	for(int i = 0; i < size; ++i){
		if(strcmp(strings[i],s) == 0){
			return i;
		}
	}

	if(size >= allocated){ //resize it
		allocated *= 2;
		strings = (char **) realloc(strings, allocated * sizeof(* strings));
	}

	strings[size] = (char *) malloc( (length) * sizeof(char) );
	strcpy(strings[size], s);

	++size;
	return size-1;
}

int LexicalParser::map_t::push(const char *s){
	return push(s, strlen(s)+1);
}
