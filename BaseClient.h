#ifndef BASE_CLIENT_HPP_
#define BASE_CLIENT_HPP_

// CLient API v.0.0.02 alpha
// buffer, networking

#include "Errors.h"
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>


class BaseClient {
	/* static variables */
	
  public:
  
	/* internal structures */
	struct server_t {
		int ip;
		int port;
	};
	
	struct buffer_t {
		static const int DEFAULT_BUFFER = 64;
		static const int MAXIMUM_BUFFER = 1024*1024*8;

		char * data;
		int allocated, size;
		
		void push(const char * data, int length);
	};
	
	struct message_queue_t{
		struct message_list{
			char * message;
			int length;
			struct message_list *next, *prev;
		} *lo, *hi;
		int count;
		
		bool isEmpty() const;
		int getLength() const;
		void push(const char * data, int length);
		char * pop(); /* YOU HAVE TO FREE MEMORY MANUALLY */
		
		message_queue_t();
		~message_queue_t();
	};
	
	struct netinfo_t {
		int descriptor;
	};
	
	
  private:
	/* non-static data */	
	char message_separator;
	server_t server;
	buffer_t buffer;
	netinfo_t netinfo;

  protected:
	message_queue_t message_queue;

  private:
	/* private methods */	
	int split_messages(char separator);

  public:	
	/* public methods */	
	BaseClient (const char * ip, int port, char msp = '\0');
	virtual ~BaseClient();
	
	void send(const char * data, int length);
	void send(const char * data);

	int getDescriptor();

	virtual int check(struct timeval timeout); /* check for incomming messages */
};

#endif
