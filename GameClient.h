/*
 * GameClient.h
 *
 *  Created on: 05.05.2013
 *      Author: urandon
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "TypedClient.h"
#include "Task.h"

class GameClient: public TypedClient {
public:
	GameClient(const char * ip, int port, struct timeval default_timeval);
	virtual ~GameClient();

	void perform(int subtype, int quantity, int price);
	int getInfo(int gtype, int subtype, int player_id, int quantity, int price);

private:
	void getGlobals();
	int check(struct timeval timeout);
	int checkForFeedback(struct timeval timeout);

	int getSpace(const char * s);

	int getGeneralInfo(int subtype);
	int getMarketInfo(int subtype);
	int getPlayerInfo(int subtype, int id);
	int getAuctionInfo(int subtype, int id);

	void wait4turn();

	struct timeval default_timeval;
	static const int SENDBUFFER_SIZE;
	char * send_buffer;

	struct globals_t {
		bool can_perform;
		bool game_started;
		int myid;
		int month_no;
		int players; // active_players;
		struct market_t {
			int state;
			int supply, raw_price;
			int demand, production_price;
		} market;
	} globals;

	struct player_auct_t {
		int produced;
		int bought_quan, bought_price;
		int sold_quan, sold_price;
		player_auct_t();
	};
	player_auct_t * aucts;
};

#endif /* GAMECLIENT_H_ */
