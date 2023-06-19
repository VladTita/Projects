#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include "MapDriver.h"
#include "Map.h"
#include "Continent.h"
#include "Orders.h"
#include "Player.h"
#include "PlayerDriver.h"
#include "Territory.h"
#include "LoggingObserver.h"

class CommandProcessor;

using namespace std;

class GameEngine : Observer{
	public:
		GameEngine();
		~GameEngine();
		void Update();
		GameEngine(string file);
		enum State {START, MAP_LOADED, MAP_VALIDATED, PLAYERS_ADDED, ASSIGN_REINFORCEMENT, ISSUE_ORDERS, EXECUTE_ORDERS, WIN};
		State state;
		Map* map;
		CommandProcessor* cp;
		vector<Player*> players;
		Deck* deck;
		void startupPhase();
		void mainGameLoop();
		void mainGameLoop(int maxTurns);
		bool transition();
		bool closingPhase(); //return true to end
		bool checkWin();
		Player* getWinner();
		void runTournament(string params);

	private:
		const int MIN_PLAYERS = 2;
		const int MAX_PLAYERS = 6;
		const int STARTING_REINFORCEMENTS_PER_PLAYER = 50;
		const int STARTING_CARDS_PER_PLAYER = 2;
		const int DECK_SIZE = 50;
		const int MIN_ARMY_UNITS_PER_TURN = 3;
		void reinforcementPhase();
		void issueOrdersPhase();
		void executeOrdersPhase();
		void printActions();
		void initialization();

};


#endif