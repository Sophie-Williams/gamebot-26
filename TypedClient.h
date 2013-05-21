/*
 * TypedClient.h
 *
 *  Created on: 08.04.2013
 *      Author: urandon
 */

#ifndef TYPEDCLIENT_H_
#define TYPEDCLIENT_H_

#include "BaseClient.h"

class TypedClient: public BaseClient {
public:
	TypedClient(const char * ip, int port);

	static const int PATTERN_LENGTH = 4;
	static const int PREFIX_QUANTITY = 5;
	static const char service_prefix[PREFIX_QUANTITY+1][PATTERN_LENGTH+1];

	enum message_type {
		U_BROADCAST, U_PRIVATE, // user's messages
		S_BROADCAST, S_HUMAN, S_MACHINE, // server's messages
		NO_TYPE // when type is not defined
	};

	struct message_t {
		enum message_type type;
		int length;
		char * msg;

		message_t(char * msg, enum message_type type);
		message_t(const message_t & message);
		~message_t();
	};

	virtual int check(struct timeval timeout);
	virtual int act();
private:
	message_queue_t queue[PREFIX_QUANTITY+1];
	enum message_type recognize(char * message);

protected:
	char * getMessage(message_type queue_no);
	bool isEmpty(message_type queue_no);
	int getLength(message_type queue_no);
};

#endif /* TYPEDCLIENT_H_ */
