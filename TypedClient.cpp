/*
 * TypedClient.cpp
 *
 *  Created on: 08.04.2013
 *      Author: urandon
 */

#include "TypedClient.h"

const char TypedClient::service_prefix[PREFIX_QUANTITY+1][PATTERN_LENGTH+1] = {
			"[UB]", // U_BROADCAST
			"[UP]", // U_PRIVATE
			"[SB]", // S_BROADCAST
			"[SH]", // S_HUMAN
			"[SM]", // S_MACHINE
			"[00]" // NO_TYPE
};

TypedClient::TypedClient(const char * ip, int port):BaseClient(ip,port) {};

enum TypedClient::message_type TypedClient::recognize(char * message){
	char pattern[PATTERN_LENGTH+1];

	for(int i = 0; i < PATTERN_LENGTH && message[i] != '\0'; ++i){
		pattern[i] = message[i];
	}
	pattern[PATTERN_LENGTH] = '\0';

	if(pattern[0] != '[' || pattern[PATTERN_LENGTH-1] != ']'){
		return NO_TYPE;
	}

	switch(pattern[1]){
	case 'U':
		switch(pattern[2]){
		case 'B':	return U_BROADCAST; break;
		case 'P':	return U_PRIVATE; break;
		default:	return NO_TYPE;
		};
	case 'S':
		switch(pattern[2]){
		case 'B':	return S_BROADCAST; break;
		case 'H':	return S_HUMAN; break;
		case 'M':	return S_MACHINE; break;
		default:	return NO_TYPE;
		};
	default:
		return NO_TYPE;
	};
}


int TypedClient::check(struct timeval timeout) {
	int res = 0;
	enum message_type type;

	for(int tmp = 0; tmp != -1; tmp = BaseClient::check(timeout)){
		res += tmp;
	}

	if(res == 0){
		return 0;
	}

	while(!message_queue.isEmpty()) {
		char * tmp;
		int length;

		length = message_queue.lo->length;
		tmp = message_queue.pop();
		type = recognize(tmp);
		queue[type].push(tmp + PATTERN_LENGTH, length - PATTERN_LENGTH);
	}

	return res;
}

int TypedClient::act() {
	for(int i = 0; i <= PREFIX_QUANTITY; ++i){
		while(!queue[i].isEmpty()){
			char * s = queue[i].pop();
			if(/* || i != S_MACHINE && i != S_BROADCAST */ 1) {
				printf("{%s} %s", service_prefix[i], s);
			}
			free(s);
		}
	}
	return 0;
}

TypedClient::message_t::message_t(char * _msg, enum TypedClient::message_type _type):type(_type), msg(_msg){
	int cnt;
	for(cnt = 0; _msg[cnt] != '\0'; ++cnt);;
	length = cnt;
}
TypedClient::message_t::message_t(const TypedClient::message_t & message):type(message.type), length(message.length){
	msg = (char *) malloc ((message.length + 1) * sizeof(char));
	strcpy(msg, message.msg);
}
TypedClient::message_t::~message_t(){ free(msg); }


char * TypedClient::getMessage(TypedClient::message_type queue_no){
	return queue[queue_no].pop();
}

bool TypedClient::isEmpty(TypedClient::message_type queue_no){
	return queue[queue_no].isEmpty();
}

int TypedClient::getLength(TypedClient::message_type queue_no){
	return queue[queue_no].getLength();
}
