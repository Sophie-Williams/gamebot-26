/*
 * ImpLexicalParser.cpp
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#include "ImpLexicalParser.h"
#include "ImpSyntaxParser.h"
//#include <cstdlib>
#include <ctype.h>
#include <cstdio>
//#include <string.h>

ImpLexicalParser::ImpLexicalParser():state(H),line(1) {
	for(int i = 0; i < ImpSyntaxParser::PREDEFINED_ATOMS; ++i){
		map.push(ImpSyntaxParser::atom_essence[i]);
	}
}


ImpLexicalParser::~ImpLexicalParser() {
}

bool ImpLexicalParser::isseparator(char ch){
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'||
			ch == '&' || ch == '|' || ch == '!' ||
			ch == '>' || ch == '<' || ch == '=' ||
			ch == '[' || ch == ']' || ch == '(' || ch == ')' ||
			ch == '{' || ch == '}' ||
			ch == ',' || ch == ';' || ch == ':';
}

lexem * ImpLexicalParser::ret(enum state_t mstate){
	lexem * lex;
	buffer.push('\0');
	//lex = new lexem(buffer.data, buffer.size, current_type, line);
	lex = new lexem(map.push(buffer.data, buffer.size), current_type, line);
	state = mstate;
	buffer.flush();

	return lex;
}

lexem * ImpLexicalParser::push(int ch){
	lexem * lex;

	if(ch == '\n'){
		++line;
	}

	if(ch == EOF){
		if(state != H){
			throw EOFinsideLexemError(line);
		} else {
			return NULL;
		}
	}

	switch(state){
	case H :
		if(isdigit(ch)){
			state = N;
			current_type = NUMERIC;
			buffer.push(ch);
		} else
		if(isalpha(ch)){
			state = K;
			current_type = KEYWORD;
			buffer.push(ch);
		} else
		if(isseparator(ch) && ch != ':'){
			state = SEP;
			current_type = SEPARATOR;
			buffer.push(ch);
		} else
		if(isspace(ch)){
			// do nothing
		} else
		switch(ch){
		case '?' : case '@' : case '$' :
			state = I;
			if(ch == '?'){
				current_type = FUNCTION;
			} else
			if(ch == '@'){
				current_type = LABEL;
			} else {
				current_type = VARIABLE;
			}
			buffer.push(ch);
			break;
		case ':' :
			state = A;
			current_type = EQUALITY;
			buffer.push(ch);
			break;
		case '"' :
			state = S;
			current_type = STRING;
			str_slash = false;
			buffer.push(ch);
			break;
		default:
			throw BadSymbolError(line, ch);
		};
		break;

	case N :
		if(isdigit(ch)){
			buffer.push(ch);
		} else
		if(isspace(ch)){
			return ret(H);
		} else
		if(isseparator(ch)){
			lex = ret(SEP);
			buffer.push(ch);
			return lex;
		} else {
			throw BadSymbolError(line, ch);
		};
		break;

	case I :
		if(isdigit(ch) || isalpha(ch) || ch == '_'){
			buffer.push(ch);
		} else
		if(isspace(ch)){
			return ret(H);
		} else
		if(isseparator(ch)){
			lex = ret(SEP);
			buffer.push(ch);
			return lex;
		} /* else
		if(ch == ':' && current_type == LABEL){
			buffer.push(ch);
			current_type = LABELREF;
		} */
		else{
			throw BadSymbolError(line, ch);
		};
		break;

	case K :
		if(isalpha(ch)){
			buffer.push(ch);
		} else
		if(isspace(ch)){
			return ret(H);
		} else
		if(isseparator(ch)){
			lex = ret(SEP);
			buffer.push(ch);
			return lex;
		} else {
			throw BadSymbolError(line, ch);
		};
		break;

	case A :
		if(ch == '='){
			buffer.push(ch);
			return ret(H);
		} else {
			throw BadSymbolError(line, ch);
		}
		break;

	case S :
		buffer.push(ch);
		if(str_slash){
			str_slash = false;
		} else
		if(ch == '"'){
			return ret(H);
		} else
		if(ch == '\\'){
			str_slash = true;
		}
		break;

	case SEP :
		current_type = SEPARATOR;
		if(isseparator(ch)){
			lex = ret(SEP);
			buffer.push(ch);
		} else {
			lex = ret(H);
			push(ch);
		}
		return lex;
		break;
	};

	return NULL;
}


bool ImpLexicalParser::isEmpty() {
	return buffer.size == 0;
}

const char * ImpLexicalParser::getString(int id) {
	return map.getString(id);
}

