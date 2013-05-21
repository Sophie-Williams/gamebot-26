/*
 * HumanClient.cpp
 *
 *  Created on: 05.05.2013
 *      Author: urandon
 */

#include "HumanClient.h"
#include <cstdio>

HumanClient::HumanClient(const char * _ip, int _port):TypedClient(_ip, _port) {}
HumanClient::~HumanClient() {}

void HumanClient::launch(struct timeval timeout){
	fd_set dsc;
	int inet = getDescriptor();
	int stdfd = STDIN_FILENO;
	struct timeval tmp;

	const int BUFFSIZE = 64;
	char buffer[BUFFSIZE];
	int length;


	while(true){
		FD_ZERO(&dsc);
		FD_SET(inet, &dsc);
		FD_SET(stdfd, &dsc);

		tmp = timeout;
		select(((inet>stdfd)?inet:stdfd)+1, &dsc, NULL, NULL, &tmp);

		if(FD_ISSET(stdfd, &dsc)){
			length = read(stdfd, buffer, BUFFSIZE);
			if(length != 0){
				send(buffer, length);
			}
		}
		if(FD_ISSET(inet, &dsc)){
			check(timeout);
			for(int i = 0; i <= PREFIX_QUANTITY; ++i){
				TypedClient::message_type type = TypedClient::message_type(i);
				while(!isEmpty(type)){
					char * s = getMessage(type);
					if(type != S_MACHINE && type != S_BROADCAST) {
						if(type == U_BROADCAST || type == U_PRIVATE){
							printf("[user message] ");
						}
						printf("%s", s);
					}
					free(s);
				}
			}
		}
	}
}

