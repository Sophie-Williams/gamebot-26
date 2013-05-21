#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "TypedClient.h"
//#include "ImpLexicalParser.h"
//#include "ImpSyntaxParser.h"
#include "SchLexicalParser.h"
#include "SchSyntaxParser.h"
#include "SpecialObjects.h"
#include "settings.h"

struct args_t * args;


void network_test() {
	timeval timeout;

	timeout.tv_sec	= 0;
	timeout.tv_usec	= 0.2;

	TypedClient client(args->ip, args->port);
	while(true){
		sleep(1);
		client.send("help\n");

		client.check(timeout);
		client.act();
	}
}

int main(int argc, char ** argv) {
	SchSyntaxParser sparser;
	timeval timeout;
	int fd;


	timeout.tv_sec	= 0;
	timeout.tv_usec	= 0.1;

	args = parse_args(argc, argv);

	if(args->script != NULL){
		fd = open(args->script, O_RDONLY);
	} else {
		fd = STDIN_FILENO;
		char tmp[] = "stdin";
		args->script = (char *) malloc(sizeof(tmp));
		strcpy(args->script, tmp);
	}

	try{
		SchemeMachine vm(args->ip, args->port, timeout);

		sparser.receive(fd);
		sparser.reset();
		SchObjectRef ref(SchObjectRef(sparser.trueParse()));
//		network_test();
		if(args->memtest){
			int cnt = 0;
			const int infinity = true;
			while(infinity || cnt < 10000){
				++cnt;
				fprintf(stderr, "%d%c", cnt, (cnt%8)?'\t':'\n');
				if(args->evaluate){
					vm.addTask(new PrintTask(1));
					vm.addTask(new EvalTask(ref));
				} else {
					vm.addTask(new ExecTask(ref, 1));
				}
				vm.launch();
			} // memory leaks test
		} else {
			if(args->verbose){
				printf("The following object will be %s:\n", (args->evaluate) ? "evaluated" : "executed");
				ref->print();
				printf("\n");
			}

			if(args->evaluate){
				vm.addTask(new PrintTask(1));
				vm.addTask(new EvalTask(ref));
			} else {
				vm.addTask(new ExecTask(ref, 1));
			}
			printf("SchemeMachine launch:\n");
			vm.launch(args->verbose);
			printf("\n");
		}
	}
	catch(UnexpectedLexemError &e){
		e.print(args->script, sparser.getLexString(e.getExpected()), sparser.getLexString(e.getGot()));
		fprintf(stderr, "\n");
	}
	catch(UndefinedSymbolError &e){
		e.print(args->script, sparser.getLexString(e.getId()));
		fprintf(stderr, "\n");
	}
	catch(SomethingExpectedError &e){
		e.print(args->script, sparser.getLexString(e.getLex()->id));
		fprintf(stderr, "\n");
	}
	catch(Error &e){
		e.print(args->script);
		fprintf(stderr, "\n");
	}
	catch(...){
		throw;
		fprintf(stderr, "\nSomething was unexpected in the project. Contact depeloper\n");
	}

	/* Destructors */
	delete args->ip;
	delete args->script;
	delete args;

	return 0;
}
