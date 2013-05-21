/*
 * GameClient.cpp
 *
 *  Created on: 05.05.2013
 *      Author: urandon
 */

#include "GameClient.h"
#include <cstdio>

GameClient::GameClient(const char * _ip, int _port, struct timeval _default_timeval):
	TypedClient(_ip, _port), default_timeval(_default_timeval)
{
	globals.game_started = false;
	globals.can_perform = false;
	globals.month_no = 1;
	globals.myid = -1;
	globals.players = -1;
	aucts = NULL;
	send_buffer = (char *) malloc(sizeof(char) * SENDBUFFER_SIZE);
}

GameClient::~GameClient(){
	delete aucts;
	free(send_buffer);
}

const int GameClient::SENDBUFFER_SIZE = 256;

GameClient::player_auct_t::player_auct_t():
		produced(0),
		bought_quan(0), bought_price(0),
		sold_quan(0), sold_price(0) {}

int GameClient::check(struct timeval timeout){
	int res = 0;
	do{
		res += TypedClient::check(timeout);
		getGlobals();
	} while(!globals.game_started);

	return res;
}

int GameClient::checkForFeedback(struct timeval timeout){
	int length = getLength(S_MACHINE);
	int res = 0;
	do{
		res += GameClient::check(timeout);
	} while(getLength(S_MACHINE) <= length);


	return res;
}


void GameClient::perform(int subtype, int quantity, int price){
	do{
		check(default_timeval);
	} while(!globals.can_perform);

	switch(subtype){
	case NetworkTask::BUY :
		sprintf(send_buffer, "buy %d %d\n", quantity, price);
		break;
	case NetworkTask::SELL :
		sprintf(send_buffer, "sell %d %d\n", quantity, price);
		break;
	case NetworkTask::PROD :
		sprintf(send_buffer, "prod %d\n", quantity);
		break;
	case NetworkTask::BUILD :
		sprintf(send_buffer, "build %d\n", quantity);
		break;
	case NetworkTask::ENDTURN :
		sprintf(send_buffer, "turn\n");
		globals.can_perform = false;
		break;
	case NetworkTask::WAIT :
		wait4turn();
	}
	BaseClient::send(send_buffer);
}

int GameClient::getInfo(int gtype, int subtype, int player_id, int quantity, int price){
	check(default_timeval);
	switch(gtype){
	case NetworkTask::GENERAL :
		return getGeneralInfo(subtype);
		break;
	case NetworkTask::MARKET :
		return getMarketInfo(subtype);
		break;
	case NetworkTask::PLAYER :
		return getPlayerInfo(subtype, player_id);
		break;
	case NetworkTask::AUCTION :
		return getAuctionInfo(subtype, player_id);
		break;
	default :
		//nothing
		break;
	}
	return 0;
}

void GameClient::getGlobals(){
	while(!isEmpty(S_BROADCAST)){
		char * msg = getMessage(S_BROADCAST), * nmsg;
		int word = getSpace(msg);

		msg[word] = '\0';
		if(strcmp(msg, "started") == 0){
			globals.game_started = true;
			globals.can_perform = true;
		} else
		if(strcmp(msg, "new_month") == 0){
			// #
			nmsg = msg+word+1;
			word = getSpace(nmsg);
			nmsg[word] = '\0';
			globals.month_no = atoi(nmsg);
			// state
			nmsg = msg+word+1;
			word = getSpace(nmsg);
			nmsg[word] = '\0';
			globals.market.state = atoi(nmsg);
			globals.can_perform = true;
		} else
		if(strcmp(msg, "mt") == 0){
			int id, value, price;
			char action;
			if(globals.players == -1){
				getGeneralInfo(NetworkTask::PLAYERS);
			}
			if(aucts == NULL){
				aucts = new player_auct_t[globals.players];
			}

			nmsg = msg+word+1;
			action = *nmsg;
			nmsg += 2;

			word = getSpace(nmsg);
			nmsg[word] = '\0';
			id = atoi(nmsg);
			nmsg += word+1;

			word = getSpace(nmsg);
			nmsg[word] = '\0';
			value = atoi(nmsg);
			nmsg += word+1;

			word = getSpace(nmsg);
			nmsg[word] = '\0';
			price = atoi(nmsg);


			switch(action){
			case 'b':
				aucts[id].bought_quan = value;
				aucts[id].bought_price = price;
				break;
			case 's':
				aucts[id].sold_quan = value;
				aucts[id].sold_price = price;
				break;
			}
		} else
		if(strcmp(msg, "info") == 0){
			nmsg = msg+word+1;
			word = getSpace(nmsg);
			nmsg[word] = '\0';
			if(strcmp(nmsg, "turns")){
				if(aucts != NULL){
					delete aucts;
					aucts = NULL;
				}
			}
			// just ignore it
		} else
		if(strcmp(msg, "win") == 0){
			printf("WIN!\n");
			throw GameOver();
		}

		free(msg);
	}
}

int GameClient::getSpace(const char * s){
	int i;
	for(i = 0; s[i] != '\0'; ++i){
		if(s[i] == '\n' || s[i] == ' '){
			return i;
		}
	}
	return i;
}

int GameClient::getMarketInfo(int subtype){
	char * msg, * nmsg;
	int res;
	int word = -1;

	send("market\n");
	checkForFeedback(default_timeval);
	msg = getMessage(S_MACHINE);
	nmsg = msg;

	for(int i = 0; i < subtype+1; ++i){
		nmsg += word+1;
		word = getSpace(nmsg);
	}

	nmsg[word] = '\0';
	res = atoi(nmsg);
	free(msg);

	return res;
}

int GameClient::getGeneralInfo(int subtype){
	int word;
	char * msg, * nmsg;
	int res;

	switch(subtype){
	case NetworkTask::MY_ID :
		if(globals.myid == -1){
			send("stat\n");
			checkForFeedback(default_timeval);
			msg = getMessage(S_MACHINE);
			nmsg = msg + 2;
			word = getSpace(nmsg);
			nmsg[word] = '\0';
			globals.myid = atoi(nmsg);
		}
		return globals.myid;
		break;
	case NetworkTask::TURN :
		return globals.month_no;
		break;
	case NetworkTask::PLAYERS :
		if(globals.players == -1){
			send("market\n");
			checkForFeedback(default_timeval);
			msg = getMessage(S_MACHINE);
			nmsg = msg;

			for(int i = 0; i < 6; ++i, nmsg = word+nmsg+1){
				word = getSpace(nmsg);
			}

			nmsg[word] = '\0';
			globals.players = atoi(nmsg);
			free(msg);
		}
//		check(default_timeval);
		return globals.players;

		break;
	case NetworkTask::ACTIVE_PLAYERS :
		send("market\n");
		checkForFeedback(default_timeval);
		msg = getMessage(S_MACHINE);
		nmsg = msg;

		for(int i = 0; i < 7; ++i, nmsg = word+nmsg+1){
			word = getSpace(nmsg);
		}

		nmsg[word] = '\0';
		res = atoi(nmsg);
		free(msg);
		return res;

		break;
	}

	return 0;
}

int GameClient::getPlayerInfo(int subtype, int id){
	char * msg, * nmsg;
	int res;
	int word = -1;

	sprintf(send_buffer, "player %d\n", id);
	send(send_buffer);
	checkForFeedback(default_timeval);
	msg = getMessage(S_MACHINE);
	nmsg = msg+2;

	for(int i = 0; i < subtype+2; ++i){
		nmsg = word+nmsg+1;
		word = getSpace(nmsg);
	}

	nmsg[word] = '\0';
	res = atoi(nmsg);
	free(msg);

	return res;
}

int GameClient::getAuctionInfo(int subtype, int id){
	if(aucts == NULL){
		return 0;
	}

	switch(subtype){
	case NetworkTask::RESULT_RAW_BOUGHT :
		return aucts[id].bought_quan;
		break;
	case NetworkTask::RESULT_RAW_PRICE :
		return aucts[id].bought_price;
		break;
	case NetworkTask::RESULT_PROD_SOLD :
		return aucts[id].sold_quan;
		break;
	case NetworkTask::RESULT_PROD_PRICE :
		return aucts[id].sold_price;
		break;
	}

	return 0;
}

void GameClient::wait4turn(){
	do{
		check(default_timeval);
	} while(!globals.can_perform);
}
