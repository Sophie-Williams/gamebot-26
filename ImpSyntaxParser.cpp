/*
 * SyntaxParser.cpp
 *
 *  Created on: 15.04.2013
 *      Author: urandon
 */

#include "ImpSyntaxParser.h"
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

template<typename T, size_t N>
inline size_t LengthOf(T (&x)[N]){
	return N;
}

const char * ImpSyntaxParser::atom_essence[] = {
	"[", "]", "(", ")", "{", "}",
	":=", ":", ";", ",",
	"def",
	"if", "then", "else", "goto",
	"buy", "sell", "prod", "build", "endturn",
	"print",
	"&", "|", "!",
	"<", ">", "=",
	"+", "-",
	"/", "*", "%"
};

const int ImpSyntaxParser::PREDEFINED_ATOMS = LengthOf(ImpSyntaxParser::atom_essence);

/* ImpSyntaxParser::atom */
ImpSyntaxParser::atom::atom(enum atom_type mtype, int mid, int mline):
		type(mtype), id(mid), line(mline) { } ;

ImpSyntaxParser::atom::atom(const lexem & lex):
		id(lex.id), line(lex.line)
{
	switch(lex.type){
	case LexicalParser::NUMERIC :
		type = NUMERIC;
		break;
	case LexicalParser::STRING :
		type = STRING;
		break;
	case LexicalParser::VARIABLE :
		type = VARIABLE;
		break;
	case LexicalParser::FUNCTION :
		type = FUNCTION;
		break;
	case LexicalParser::LABEL :
		type = LABEL;
		break;
	default:
		type = (enum atom_type) id;
	}
}

ImpSyntaxParser::atom::atom(const ImpSyntaxParser::atom & mAtom):
		type(mAtom.type), id(mAtom.id), line(mAtom.line) { }

/* SyntaxParser::code_t */

ImpSyntaxParser::code_t::code_t():size(0),allocated(DEFAULT_SIZE){
	data = (atom **) malloc(DEFAULT_SIZE * sizeof(char));
}

ImpSyntaxParser::code_t::~code_t(){
	for(int i = 0; i < size; ++i){
		delete data[i];
	}
	free(data);
}

void ImpSyntaxParser::code_t::push(atom * mAtom){
	int newsize = size + 1;

	if(newsize > allocated){
		allocated *= 2;
		data = (atom **) realloc(data, allocated);
	}

	data[size] = mAtom;
	size = newsize;
}


/* Costructor & Destructor */

ImpSyntaxParser::ImpSyntaxParser(int fd):lo(0),hi(0) {
	const int buffsize = 8;
	char buffer[buffsize];
	int length;

	lexem * lex;

	atom * mAtom;

	do{
		length = read(fd, buffer, buffsize);

		if(length == 0){
			if((lex = lexical.push(int(EOF))) != NULL){
				mAtom = new atom(*lex);
				delete lex;
				code.push(mAtom);
			}
		} else {
			for(int i = 0; i < length; ++i){
				if((lex = lexical.push(int(buffer[i]))) != NULL){
					mAtom = new atom(*lex);
					delete lex;
					code.push(mAtom);
				}
			}
		}
	} while(length != 0);
}

ImpSyntaxParser::~ImpSyntaxParser() { }

ImpSyntaxParser::atom * ImpSyntaxParser::current()	{ return code.data[lo]; 	}
ImpSyntaxParser::atom * ImpSyntaxParser::next()		{ return code.data[++lo]; 	}
ImpSyntaxParser::atom * ImpSyntaxParser::prev()		{ return code.data[--lo]; 	}

/* language-sensitive recursive descent methods */

/*
void SyntaxParser::Program() {
	if(current()->type == DEFINITION){
		Definition();
		if(next()->type == DOT_N_COMMA){
			Code();
		} else {
			throw UnexpectedLexemError(current()->line, int(current()->type), int(DOT_N_COMMA));
		}
	} else {
		Code();
	}
}

void SyntaxParser::Definition() {

} */
