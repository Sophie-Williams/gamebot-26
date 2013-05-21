/*
 * HumanClient.h
 *
 *  Created on: 05.05.2013
 *      Author: urandon
 */

#ifndef HUMANCLIENT_H_
#define HUMANCLIENT_H_

#include "TypedClient.h"

class HumanClient: private TypedClient {
public:
	HumanClient(const char * ip, int port);
	virtual ~HumanClient();

	void launch(struct timeval timeout);
};

#endif /* HUMANCLIENT_H_ */
