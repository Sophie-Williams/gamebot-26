#include "BaseClient.h"
#include <errno.h>


BaseClient::BaseClient(const char * ip, int port, char msp):message_separator(msp) {
	struct sockaddr_in addr;
	
	
	if((netinfo.descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		throw CannotCreateSocketError();
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = server.port = htons(port);
	if((server.ip = inet_aton(ip, &(addr.sin_addr))) == 0) {
		throw BadIPError();
	}
	if (connect(netinfo.descriptor, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		throw CannotEstablishConnectionError();
	}
	
	buffer.size = 0;
	buffer.allocated = buffer_t::DEFAULT_BUFFER;
	buffer.data = (char *) malloc(buffer.allocated * sizeof(char));
	
	message_queue.count = 0;
	message_queue.lo = message_queue.hi = 0;
	
}


BaseClient::~BaseClient() {
	shutdown(netinfo.descriptor, SHUT_RDWR);
	close(netinfo.descriptor);
	if(buffer.data){
		free(buffer.data);
	}
}


void BaseClient::send(const char * data, int length) {
	int cnt = 0;
	int res;

	while(cnt < length){
		res = write(netinfo.descriptor, data+cnt, length-cnt);
		if(res == -1){
			throw NetworkErrorErrno(errno);
		}
		cnt += res;
	}
}

void BaseClient::send(const char * data){
	int length = strlen(data);
	send(data, length);
}

/* BaseClient:buffer_t methods */

void BaseClient::buffer_t::push(const char * given_data, int length) {
	int new_size = size + length;
	
	if(new_size > MAXIMUM_BUFFER) {
		throw BufferOverflowError();
	}
	
	if(new_size > allocated) {
		allocated = new_size;
		data = (char *) realloc(data, new_size * sizeof(char));
	}
	
	memcpy(data + size, given_data, length * sizeof(char));
	size = new_size;
}

/* BaseClient::message_queue_t methods */

BaseClient::message_queue_t::message_queue_t():lo(0),hi(0),count(0) {};

BaseClient::message_queue_t::~message_queue_t() {
	message_list * tmp = lo;
	
	while(tmp != hi) {
		tmp = lo->next;
		free(lo);
		lo = tmp;
	}
	
	if(hi != 0){
		free(hi);
	}
}


bool BaseClient::message_queue_t::isEmpty() const { return count == 0; }
int BaseClient::message_queue_t::getLength() const { return count; }

void BaseClient::message_queue_t::push (const char * data, int length) {
	message_list * tmp;
	
	tmp = (message_list *) malloc (sizeof(*tmp));

	tmp->prev = hi;
	tmp->next = 0;
	tmp->message = (char *) malloc( (length+1) * sizeof(char) );
	memcpy(tmp->message, data, length * sizeof(char));
	tmp->message[length] = '\0';
	tmp->length = length + 1;
	
	if(hi != 0){
		hi->next = tmp;
		hi = tmp;
	} else {
		lo = hi = tmp;
	}

	count++;	
}


char * BaseClient::message_queue_t::pop() {
	struct message_list *tmp;
	char * res;

	if(lo == NULL){
		return NULL;
	}
	
	tmp = lo->next;
	res = lo->message;
	free(lo);
	lo = tmp;
	
	if(!tmp){
		hi = 0;
	}
	count--;

	return res;
}

/* BaseClient methods */

int BaseClient::split_messages(char separator) {
	buffer_t tmp_b;
	char * pos;
	int cnt = 0;
	
	if(buffer.size == 0){
		return 0;
	}
	
	tmp_b = buffer;
		
	while( tmp_b.size > 0 && ((pos = (char *) memchr(tmp_b.data, separator, tmp_b.size)) != NULL) ){
		int delta = pos - tmp_b.data + 1;
		
		// extract message from the buffer;
		message_queue.push(tmp_b.data, delta);
		tmp_b.data += delta;
		tmp_b.size -= delta;
		tmp_b.allocated -= delta;
		++cnt;
	}
	
	// reallocate memory
	if(tmp_b.allocated < buffer_t::DEFAULT_BUFFER ){
		tmp_b.allocated = buffer_t::DEFAULT_BUFFER;
	}
	
	char * rest = (char *) malloc(tmp_b.allocated * sizeof(char));
	memcpy(rest, tmp_b.data, tmp_b.size);
	tmp_b.data = rest;
	free(buffer.data);
	buffer = tmp_b;
	
	return cnt;
}


int BaseClient::check(struct timeval timeout) {
	fd_set dsc;
	char * buff;
	const int BUFF_LEN = 64;
	int length;
	
	FD_ZERO(&dsc);
	FD_SET(netinfo.descriptor, &dsc);
	
	select(netinfo.descriptor+1, &dsc, NULL, NULL, &timeout);
	
	if(!FD_ISSET(netinfo.descriptor, &dsc)){ // incomming from the server
		return -1;
	}
	
	buff = (char *) malloc(BUFF_LEN * sizeof(char));
	length = read(netinfo.descriptor, buff, BUFF_LEN);
	if(length == 0){
		throw DisconnectedError();
	} else
	if(length == -1){
		throw NetworkErrorErrno(errno);
	}
	
	buffer.push(buff, length);
	
	return split_messages(message_separator);
}


int BaseClient::getDescriptor(){
	return netinfo.descriptor;
}
