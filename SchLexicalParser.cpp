/*
 * SchLexicalParser.cpp
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#include "SchLexicalParser.h"
#include <ctype.h>
#include <stdio.h>

SchLexicalParser::SchLexicalParser():state(H), line(1), last_line(1), predefined_length(0) { }

SchLexicalParser::SchLexicalParser(const char * const * wordlist, int length):
		state(H), line(1), predefined_length(length)
{
	for(int i = 0; i < length; ++i){
		map.push(wordlist[i]);
	}
}

SchLexicalParser::~SchLexicalParser() { }


lexem * SchLexicalParser::ret(enum state_t _state){
	lexem * lex;
	buffer.push('\0');
	//lex = new lexem(buffer.data, buffer.size, current_type, line);
	lex = new lexem(map.push(buffer.data, buffer.size), current_type, last_line);
	if(lex->type == NAME && lex->id < predefined_length){
		lex->type = SPECIAL;
	}
	state = _state;
	buffer.flush();

	return lex;
}

bool SchLexicalParser::isEmpty() {
	return buffer.size == 0;
}

const char * SchLexicalParser::getString(int id) {
	return map.getString(id);
}


lexem * SchLexicalParser::push(int ch){
	lexem * lex;
	last_line = line;

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
			state = I;
			buffer.push(ch);
		} else
		if(isspace(ch)){
			// do nothing
		} else
		switch(ch){
		case '"' :
			state = S;
//			buffer.push(ch);
			break;
		case '.' :
			state = F;
			buffer.push(ch);
			break;
		case '(' : case ')' :
			current_type = (ch == '(') ? LBRACE : RBRACE;
			state = SEP;
			buffer.push(ch);
			break;
		default :
			state = N;
			buffer.push(ch);
			break;
		}
		break;

	case I :
		current_type = INTEGER;
		if(!isdigit(ch)){
			if(ch == '.'){
				buffer.push(ch);
				state = F;
			} else
			if(isspace(ch)){
				return ret(H);
			} else
			if(ch == ')' || ch == '('){
				lex = ret(SEP);
				buffer.push(ch);
				current_type = (ch == '(') ? LBRACE : RBRACE;
				return lex;
			} else {
				buffer.push(ch);
				state = N;
			}
		} else {
			buffer.push(ch);
		}
		break;

	case F :
		current_type = FLOAT;
		if(!isdigit(ch)){
			if(isspace(ch)){
				return ret(H);
			} else
			if(ch == ')' || ch == '('){
				lex = ret(SEP);
				buffer.push(ch);
				current_type = (ch == '(') ? LBRACE : RBRACE;
				return lex;
			} else {
				buffer.push(ch);
				state = N;
			}
		} else {
			buffer.push(ch);
		}
		break;

	case N :
		current_type = NAME;
		if(isspace(ch)){
			return ret(H);
		} else
		if(ch == ')' || ch == '('){
			lex = ret(SEP);
			buffer.push(ch);
			current_type = (ch == '(') ? LBRACE : RBRACE;
			return lex;
		} else {
			buffer.push(ch);
		}
		break;

	case S :
		current_type = STRING;
		if(str_slash){
			buffer.push(ch);
			str_slash = false;
		} else
		if(ch == '"'){
			return ret(H);
		} else
		if(ch == '\\'){
			str_slash = true;
		} else {
			buffer.push(ch);
		}
		break;

	case SEP :
		if(ch == ')' || ch == '('){
			lex = ret(SEP);
			current_type = (ch == '(') ? LBRACE : RBRACE;
			buffer.push(ch);
		} else {
			lex = ret(H);
			if(ch == '\n'){
				--line;
			}
			push(ch);
		}
		return lex;
		break;
	};

	return NULL;
}
