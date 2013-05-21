#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <cstdio>

struct args_t {
	char * ip;
	int port;
	char * script;
	bool memtest;
	bool verbose;
	bool evaluate;
};

struct args_t * parse_args(int argc, char ** argv);

#endif
