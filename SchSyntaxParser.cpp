/*
 * SchSyntaxParser.cpp
 *
 *  Created on: 17.04.2013
 *      Author: urandon
 */

#include <cstdlib>
#include <stdio.h>
#include "SchSyntaxParser.h"
#include "SpecialObjects.h"

SchSyntaxParser::SchSyntaxParser():
		lexical(Predefined::atoms, Predefined::length),ptr(0)
{
	//receive(fd);
}


void SchSyntaxParser::receive(int fd) {
	const int BUFFSIZE = 64;
	char buffer[BUFFSIZE];
	int length;
	lexem * lex;

	do{
		length = read(fd, buffer, BUFFSIZE);

		if(length == 0){
			if((lex = lexical.push(int(EOF))) != NULL){
				storage.push(*lex);
				delete lex;
			}
		} else {
			for(int i = 0; i < length; ++i){
				if((lex = lexical.push(int(buffer[i]))) != NULL){
					storage.push(*lex);
					delete lex;
				}
			}
		}
	} while(length != 0);
}

SchSyntaxParser::~SchSyntaxParser() { }

/* SchSyntaxParser::lex_storage_t */

SchSyntaxParser::lex_storage_t::lex_storage_t():size(0),allocated(DEFAULT_SIZE){
	data = (lexem **) malloc(DEFAULT_SIZE * sizeof(lexem *));
}

SchSyntaxParser::lex_storage_t::~lex_storage_t(){
	for(int i = 0; i < size; ++i){
		//delete data[i];
		//free(data[i]);
	}
	//free(data);
}

void SchSyntaxParser::lex_storage_t::push(const lexem & lex){
	int newsize = size + 1;

	if(newsize > allocated){
		allocated *= 2;
		data = (lexem **) realloc(data, allocated * sizeof(* data));
	}

	data[size] = new lexem(lex);
	size = newsize;
}


lexem * SchSyntaxParser::previous()	{
	return (ptr < storage.size || ptr >= 1) ? storage.data[ptr-1] : NULL;
}

lexem * SchSyntaxParser::current()	{
	return (ptr < storage.size || ptr >= 0) ? storage.data[ptr] : NULL;
}

lexem * SchSyntaxParser::next()		{
	return (ptr < storage.size-1 || ptr >= 0) ? storage.data[ptr+1] : NULL;
}


/* The Parser */

void SchSyntaxParser::reset(){ ptr = 0; }

SchObjectRef SchSyntaxParser::trueParse(){
	SchObjectRef ref = rec_obj();
	if(next() != NULL && ptr != 0){
		throw ExpectedEOFLexemFoundError(previous()->line);
	}
	return ref;
}

SchObjectRef SchSyntaxParser::parse(){
	if(current() == NULL){
		if(ptr > 0){
			throw UnballancedLeftBrace(previous()->line);
		} else {
			throw EmptyCodeError();
		}
	}
	switch(current()->type){
	case SchLexicalParser::NAME :
		return SchObjectRef(new SchName( current()->line, current()->id ));
		break;

	case SchLexicalParser::SPECIAL :
		//return SchObjectRef(new SchSpecial( current()->line, current()->id ));
		return rec_special_atom();
		break;

	case SchLexicalParser::INTEGER :
		return SchObjectRef(new SchInteger( current()->line, atoi(lexical.getString(current()->id)) ));
		break;

	case SchLexicalParser::FLOAT :
		return SchObjectRef(new SchFloat( current()->line, atof(lexical.getString(current()->id)) ));
		break;

	case SchLexicalParser::STRING :
		return SchObjectRef(new SchString( current()->line, lexical.getString(current()->id) ));
		break;

	case SchLexicalParser::LBRACE :
		int cline;
		if(next() == NULL){
			throw UnballancedLeftBrace(current()->line);
		}
		if(next()->type == SchLexicalParser::RBRACE){
			return SchObjectRef(new SchList(current()->line, NULL, 0));
		}
		list_t * list, * clist, * nlist;
		int length;

		length = 0;
		cline = current()->line;
		list = (list_t *) malloc(sizeof(list_t));
		clist = list;

		while(next()->type != SchLexicalParser::RBRACE){
			// list.push( copy of * ref );
			ptr++;
			nlist= (list_t *) malloc(sizeof(list_t));
			clist->next = nlist;
			nlist->next = NULL;
			nlist->node = new SchObjectRef(parse());
			clist = nlist;
			++length;
			if(next() == NULL){
				throw UnballancedLeftBrace(cline);
			}
		}
		ptr++;
		clist = list->next;
		free(list);

		return SchObjectRef(new SchList(cline, clist, length));
		break;

	case SchLexicalParser::RBRACE :
		throw UnballancedRightBrace(current()->line);
		break;
	default:
		throw ContactDeveloperError();
	}
}

SchObjectRef SchSyntaxParser::rec_obj(){
	if(current() == NULL){
		if(ptr > 0){
			throw UnexpectedEOFError(previous()->line);
		} else {
			throw EmptyCodeError();
		}
	}
	switch(current()->type){
	case SchLexicalParser::LBRACE :
	{
		SchObjectRef ref = rec_list();
		return ref;
	}
		break;
	case SchLexicalParser::RBRACE :
		throw ObjectExpectedError(current()->line, current());
		break;
	default :
	{
		SchObjectRef ref = rec_atom();
		return ref;
	}
		break;
	}
}

SchObjectRef SchSyntaxParser::rec_atom(){
	if(current() == NULL){
		if(ptr > 0){
			throw UnexpectedEOFError(previous()->line);
		} else {
			throw EmptyCodeError();
		}
	}

	switch(current()->type){
	case SchLexicalParser::NAME :
		return SchObjectRef(new SchName( current()->line, current()->id ));
		break;

	case SchLexicalParser::SPECIAL :
		return rec_special_atom();
		break;

	case SchLexicalParser::INTEGER :
		return SchObjectRef(new SchInteger( current()->line, atoi(lexical.getString(current()->id)) ));
		break;

	case SchLexicalParser::FLOAT :
		return SchObjectRef(new SchFloat( current()->line, atof(lexical.getString(current()->id)) ));
		break;

	case SchLexicalParser::STRING :
		return SchObjectRef(new SchString( current()->line, lexical.getString(current()->id) ));
		break;

	default :
		throw AtomExpectedError(current()->line, current());
		break;
	}
}

SchObjectRef SchSyntaxParser::rec_list(){
	int cline;
	list_t * list;

	if(current() == NULL){
		if(ptr > 0){
			throw UnexpectedEOFError(previous()->line);
		} else {
			throw EmptyCodeError();
		}
	}

	cline = current()->line;
	if(current()->type != SchLexicalParser::LBRACE){
		throw ListExpectedError(current()->line, current());
	}

	ptr++;
	list = rec_internal();
	ptr++;

	if(current()->type != SchLexicalParser::RBRACE){
		delete list;
		throw ListExpectedError(current()->line, current());
	}

	return SchObjectRef(new SchList(current()->line, list));
}

list_t * SchSyntaxParser::rec_internal(){
	if(current() == NULL){
		if(ptr > 0){
			throw UnexpectedEOFError(previous()->line);
		} else {
			throw EmptyCodeError();
		}
	}

	list_t * list, * clist, * nlist;

	list = (list_t *) malloc(sizeof(list_t));
	list->next = NULL;
	clist = list;

	while(current()->type != SchLexicalParser::RBRACE){
		//nlist= (list_t *) malloc(sizeof(list_t));
		nlist = new list_t;
		clist->next = nlist;
		nlist->next = NULL;
		nlist->node = new SchObjectRef(rec_obj());
		clist = nlist;
		ptr++;
		if(current() == NULL){
			delete list;
			throw UnexpectedEOFError(previous()->line);
		}
	}

	ptr--;

	clist = list->next;
	free(list);

	return clist;
}

const char * SchSyntaxParser::getLexString(int id){
	return lexical.getString(id);
}


SchObjectRef SchSyntaxParser::rec_special_atom(){
	using namespace Special;
	int line = current()->line;
	SchObject * obj;
	enum special_type type = static_cast<special_type>(current()->id);

	switch(type){
	case LAMBDA		: obj = new SchSpecialLambda(line); break;
	case DEFINE		: obj = new SchSpecialDefine(line); break;
	case REDEFINE	: obj = new SchSpecialRedefine(line); break;
	case IF		: obj = new SchSpecialIf(line); break;
	case COND	: obj = new SchSpecialCond(line); break;
	case DO		: obj = new SchSpecialDo(line); break;
	case EVAL	: obj = new SchSpecialEval(line); break;
	case LET	: obj = new SchSpecialLet(line); break;

	case LIST	: obj = new SchSpecialList(line); break;
	case QUOTE	: obj = new SchSpecialQuote(line); break;
	case CAR	: obj = new SchSpecialCar(line); break;
	case CDR	: obj = new SchSpecialCdr(line); break;
	case ADD	: obj = new SchSpecialAdd(line); break;

	case PRINT	: obj = new SchSpecialPrint(line); break;

	case PLUS		: obj = new SchSpecialPlus(line); break;
	case MINUS		: obj = new SchSpecialMinus(line); break;
	case MULTIPLY	: obj = new SchSpecialMultiply(line); break;
	case DIVIDE		: obj = new SchSpecialDivide(line); break;
	case MODULO		: obj = new SchSpecialModulo(line); break;

	case NOT_EQ		: obj = new SchSpecialNotEqual(line); break;
	case LESS		: obj = new SchSpecialLess(line); break;
	case LESS_EQ	: obj = new SchSpecialLessEqual(line); break;
	case EQUAL		: obj = new SchSpecialEqual(line); break;
	case GREATER_EQ	: obj = new SchSpecialGreaterEqual(line); break;
	case GREATER	: obj = new SchSpecialGreater(line); break;

	case TRUE	: obj = new SchTrue(line); break;
	case FALSE	: obj = new SchFalse(line); break;

	case AND	: obj = new SchSpecialAnd(line); break;
	case OR		: obj = new SchSpecialOr(line); break;
	case NOT	: obj = new SchSpecialNot(line); break;

	case BUY		: obj = new SchSpecialBuy(line); break;
	case SELL		: obj = new SchSpecialSell(line); break;
	case PROD		: obj = new SchSpecialProd(line); break;
	case BUILD		: obj = new SchSpecialBuild(line); break;
	case ENDTURN	: obj = new SchSpecialEndturn(line); break;
	case WAIT		: obj = new SchSpecialWait(line); break;

	case _MY_ID				: obj = new SchSpecial_MyId(line); break;
	case _TURN				: obj = new SchSpecial_Turn(line); break;
	case _PLAYERS			: obj = new SchSpecial_Players(line); break;
	case _ACTIVE_PLAYERS	: obj = new SchSpecial_ActivePlayers(line); break;

	case _SUPPLY			: obj = new SchSpecial_Supply(line); break;
	case _RAW_PRICE			: obj = new SchSpecial_RawPrice(line); break;
	case _DEMAND			: obj = new SchSpecial_Demand(line); break;
	case _PRODUCTION_PRICE	: obj = new SchSpecial_ProductionPrice(line); break;
	case _MONEY				: obj = new SchSpecial_Money(line); break;
	case _RAW				: obj = new SchSpecial_Raw(line); break;
	case _PRODUCTION		: obj = new SchSpecial_Production(line); break;
	case _FACTORIES			: obj = new SchSpecial_Factories(line); break;
	case _ACTIVE_FACTORIES	: obj = new SchSpecial_ActiveFactories(line); break;

	case _RESULT_RAW_BOUGHT		: obj = new SchSpecial_ResultRawBought(line); break;
	case _RESULT_RAW_PRICE		: obj = new SchSpecial_ResultRawPrice(line); break;
	case _RESULT_PROD_SOLD		: obj = new SchSpecial_ResultProdSold(line); break;
	case _RESULT_PROD_PRICE		: obj = new SchSpecial_ResultProdPrice(line); break;

	default : throw ContactDeveloperErrorLine(line);
	}

	return SchObjectRef(obj);
}
