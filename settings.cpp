#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

static const char * optString = "i:p:s:hmvl";

static const struct option longOpts[] = {
	{ "ip", required_argument, NULL, 'i' },
	{ "port", required_argument, NULL, 'p' },
	{ "source", required_argument, NULL, 's' },
	{ "help", no_argument, NULL, 'h' },
	{ "memtest", no_argument, NULL, 'm' },
	{ "verbose", no_argument, NULL, 'v' },
	{ "evaluate", no_argument, NULL, 'l' },
	{NULL, no_argument, NULL, 0}
};

void display_usage(char * argv0)
{
	const char * descript[] = {
		"Choose gameserver's ip adress (localhost by default)",
		"Choose gameserver's port",
		"Choose script source (/dev/stdin by default)",
		"Display this message",
		"Test this build for memory leaks",
		"Show SchemeMachine's stacks",
		"Evaluate the expression"
	};
	const char * params[] = {
		"IP_ADRESS",
		"PORT",
		"SOURCE",
		NULL,
		NULL,
		NULL,
	};
	struct option *opt;
	int i, n = sizeof(longOpts) / sizeof(struct option) - 1;

	printf("Usage: %s [options]\n", argv0);
	printf("Options:\n");
	for(i = 0; i < n; i++){
		opt = (struct option *)longOpts + i;
		switch(opt->has_arg){
			case required_argument :
				printf("  -%c, --%s=%s\t%s\n", \
					opt->val, opt->name, params[i], descript[i]);
				break;
			case optional_argument :
				printf("  -%c, --%s[=%s]\t%s\n", \
					opt->val, opt->name, params[i], descript[i]);
				break;
			case no_argument :
				printf("  -%c, --%s\t%s\n", \
					opt->val, opt->name, descript[i]);
				break;
			default:
				break;
		}
	}
}

struct args_t * parse_args(int argc, char ** argv)
{
	int longIndex, opt;
	int length;

	struct args_t * args = new struct args_t;

	args->ip = NULL;
	args->port = 0;
	args->script = NULL;
	args->memtest = false;
	args->verbose = false;
	args->evaluate = false;

	while( (opt = getopt_long( argc, argv, optString, longOpts, &longIndex )) != -1){
		switch(opt){
		case 'p' :
			args->port = atoi(optarg);
			break;
		case 'i' :
			length = strlen(optarg);
			args->ip = (char *) malloc ((length+1) * sizeof(char));
			strcpy(args->ip, optarg);
			break;
		case 's' :
			length = strlen(optarg);
			args->script = (char *) malloc ((length+1) * sizeof(char));
			strcpy(args->script, optarg);
			break;
		case 'h' : case '?':
			display_usage(argv[0]);
			exit(EXIT_SUCCESS);
			break;
		case 'm' :
			args->memtest = true;
			break;
		case 'v' :
			args->verbose = true;
			break;
		case 'l' :
			args->evaluate = true;
			break;
		default:
			break;
		};
	}

	return args;
}

