#include "GameEngine.h"
#include "CommandProcessing.h"
#include "PlayerStrategies.h"
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
using namespace std;

GameEngine::GameEngine() {
	subject->Attach(this);
	initialization();
	cp = new CommandProcessor();
}

GameEngine::~GameEngine() {
	subject->Detach(this);
}

void GameEngine::Update() {
	myfile << "GAME STATE: " << this->state << "\n";
}

GameEngine::GameEngine(string file) {
	subject->Attach(this);
	initialization();
	cp = new FileCommandProcessorAdapter(file);
}

void GameEngine::startupPhase() {
	while (state != ASSIGN_REINFORCEMENT && !transition());
}

void GameEngine::mainGameLoop() {
	mainGameLoop(-1);
}

void GameEngine::mainGameLoop(int maxTurns) {
	turnNumber = 0;
	do {
		turnNumber++;
		if (maxTurns != -1 && turnNumber > maxTurns)
			break;
		if (cmdDisplay)
			map->print();
		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();
	} while (!checkWin());
	if (cmdDisplay)
		map->print();
	Player* winner = getWinner();
	if (cmdDisplay) {
		if (winner == NULL)
		{
			cout << "\n\nNo Winner\n\n";
		}
		else
		{
			cout << "\n\nplayer " << winner->getPlayerId() << " (" << winner->getName() << ") has won!\n\n";
		}
		if (!tournamentMode) {
			cout << "\nPRESS ENTER TO CONTINUE";
			string temp;
			getline(cin, temp);
		}
	}
}

bool GameEngine::closingPhase() {
	while (state != START && !transition());
}

void GameEngine::reinforcementPhase() {
	if (cmdDisplay)
		cout << "\n\n\nREINFORCEMENT PHASE STARTING";
	for (Player* player : players)
	{
		int army_units = player->getTerritories().size()/3;

		for (Continent* continent : map->getAllContinents())
		{
			bool bonus = true;
			for (Territory* territory : continent->getTerritories())
			{
				if (player != territory->owner)
				{
					bonus = false;
					break;
				}
			}
			if (bonus == true)
			{
				army_units += continent->getControlValue();
				if (cmdDisplay)
					cout << "\nplayer " << player->getPlayerId() << " (" << player->getName() << ") has full continent with control value " << continent->getControlValue();
			}
		}

		if (army_units < MIN_ARMY_UNITS_PER_TURN)
			army_units = MIN_ARMY_UNITS_PER_TURN;

		player->addReinforcementsToPool(army_units);
		if (cmdDisplay)
			cout << "\nAdded " << army_units << " army units to player " << player->getPlayerId() << " (" << player->getName() << ")";
	}
	if (cmdDisplay)
		cout << "\nREINFORCEMENT PHASE DONE";
}

void GameEngine::issueOrdersPhase() {
	if (cmdDisplay)
		cout << "\n\n\nISSUE ORDERS PHASE STARTING";
	bool newOrderRecieved;
	do {
		newOrderRecieved = false;
		for (Player* player : players)
		{
			if (player->hasTerritories() && player->issueOrder())
			{
				newOrderRecieved = true;
			}
		}
	} while (newOrderRecieved);
	if (cmdDisplay)
		cout << "\nISSUE ORDERS PHASE DONE";
}

void GameEngine::executeOrdersPhase() {
	if (cmdDisplay)
		cout << "\n\n\nEXECUTE ORDERS PHASE STARTING";
	bool newOrderRecieved;
	do {
		newOrderRecieved = false;
		for (Player* player : players)
		{
			if (player->orders->getOrderList().size() > 0)
			{
				newOrderRecieved = true;
				Order* order = player->orders->getOrderList().front();
				if (order->validate(player)) {
					if (cmdDisplay)
						cout << "\n" << player->getName() << " executing order";
					order->execute();
				}
				player->orders->remove(order);
			}
		}
	} while (newOrderRecieved);
	if (cmdDisplay)
		cout << "\nEXECUTE ORDERS PHASE DONE";
}

bool GameEngine::checkWin() {
	for (int i = 0; i < players.size(); i++)
	{
		if (!players[i]->hasTerritories())
		{
			if (cmdDisplay)
				cout << "\n" << players[i]->getName() << " (" << players[i]->getPlayerId() << ") has been removed from the game";
			players.erase(players.begin() + i);
			i--;
		}
	}

	if (cmdDisplay && !tournamentMode) {
		cout << "\nPRESS ENTER TO CONTINUE";
		string temp;
		getline(cin, temp);
	}

	if (players.size() <= 1)
		return true;
	return false;
}

Player* GameEngine::getWinner() {
	if (players.size() == 1)
		return players[0];
	return NULL;
}


void GameEngine::initialization() {
	state = START;
	map = new Map();
	deck = new Deck(DECK_SIZE);
}

//Returns true on end
bool GameEngine::transition()
{
	if (displayCmdOptions)
		printActions();
	Command* c = cp->getCommand();
	int errCount = 0;
	while (!cp->validate(c, state)) {
		if (displayCmdOptions)
			cout << "Error: Invalid command\n\n";
		if (errCount++ == 10) {
			if (cmdDisplay)
				throw std::invalid_argument("Error: Game Exiting; too many failed attempts");
			else
				exit(0);
		}
		if (displayCmdOptions)
			printActions();
		c = cp->getCommand();
	}
	switch (state)
    {
        case START:
			if (c->getComm() == "loadmap")
			{
				map->load(c->getEff());
				cout << "\nMap Loaded";
				state = MAP_LOADED;
			}
			else if (c->getComm() == "tournament")
			{
				runTournament(c->getEff());
				state = WIN;
			}
            break;

        case MAP_LOADED:
			if (c->getComm() == "loadmap") {
				map->load(c->getEff());
				cout << "\nMap Loaded";
			}
			else if (c->getComm() == "validatemap")
			{
				if (map->validate()) {
					cout << "\nMap Validated";
					state = MAP_VALIDATED;
				}
				else {
					cout << "\nInvalid Map";
				}
			}
            break;
        case MAP_VALIDATED:
			if (c->getComm() == "addplayer")
			{
				if (c->getEff().find(" ") == -1) {
					cout << "\nError: please enter player type and name";
					break;
				}

				string type = c->getEff().substr(0, c->getEff().find(" "));
				string name = c->getEff().substr(c->getEff().find(" ") + 1);

				if (!PlayerStrategy::verifyPlayerStrategy(type)) {
					cout << "\nError: invalid player strategy";
					break;
				}

				Player* player = new Player(type, name);
				players.push_back(player);
				cout << "\nPlayer Added";

				state = PLAYERS_ADDED;
			}
            break;
        case PLAYERS_ADDED:
			if (c->getComm() == "addplayer") {
				if (players.size() >= MAX_PLAYERS) {
					cout << "\nError: maximum player count: " << MAX_PLAYERS;
				}
				else {
					if (c->getEff().find(" ") == -1) {
						cout << "\nError: please enter player type and name";
						break;
					}

					string type = c->getEff().substr(0, c->getEff().find(" "));
					string name = c->getEff().substr(c->getEff().find(" ") + 1);

					if (!PlayerStrategy::verifyPlayerStrategy(type)) {
						cout << "\nError: invalid player strategy";
						break;
					}

					Player* player = new Player(type, name);
					players.push_back(player);
					cout << "\nPlayer Added";
				}
			}
			else if (c->getComm() == "gamestart")
			{
				if (players.size() < MIN_PLAYERS) {
					cout << "\nError: minimum player count: " << MIN_PLAYERS;
				}
				else {
					//randomize player order
					std::random_shuffle(std::begin(players), std::end(players));

					//distribute territories
					vector<Territory*> territories = map->getAllTerritories();
					std::random_shuffle(std::begin(territories), std::end(territories));

					for (int i = 0; i < territories.size(); i++) {
						int curPlayerIndex = players.size() - 1 - (i%players.size()); //last player(s) will have most territories if uneven territories
						Territory* territory = territories[i];
						Player* player = players[curPlayerIndex];
						player->addTerritory(territory);
					}

					//50 army units to each player
					//draw 2 each player
					for (Player* player : players)
					{
						player->addReinforcementsToPool(STARTING_REINFORCEMENTS_PER_PLAYER);
						for (int i = 0; i < STARTING_CARDS_PER_PLAYER; i++)
							deck->draw(player->getHand());

					}

					state = ASSIGN_REINFORCEMENT;
					cout << "\nStartup Phase Done";
				}
			}
            break;
		case WIN:
			if (c->getComm() == "end")
			{
				cout << "\nEnding Game";
				subject->Notify();
				return true;
			}
			else if (c->getComm() == "play")
			{
				cout << "\nRestarting Game";
				initialization();
			}
            break;
	}
	subject->Notify();
	return false;
}

void GameEngine::printActions()
{
	cout << "\nPossible Commands: ";
	switch (state)
    {
        case START:
			cout << "\nloadmap <map>";
			cout << "\ntournament -M <listOfMapFiles> -P <listOfPlayerStrategies> -G <numberOfGames> -D <maxNumberOfTurns>";
            break;
        case MAP_LOADED:
			cout << "\nloadmap <map>";
			cout << "\nvalidatemap";
            break;
        case MAP_VALIDATED:
			cout << "\naddplayer <type> <name>";
            break;
        case PLAYERS_ADDED:
			cout << "\naddplayer <type> <name>";
			cout << "\ngamestart";
            break;
		case WIN:
			cout << "\nend";
			cout << "\nplay";
            break;

    }
	cout << "\n\n";
}

bool isdigit (string s) {
	for (char c : s)
	{
		if ((c < '0') || (c > '9'))
			return false;
	}
    return true;
}

void GameEngine::runTournament(string params)
{
	vector<string> maps;
	vector<Player*> players;
	int numGames = 0;
	int maxTurns = 0;

	vector<string> paramsArr;
	stringstream data(params);
	string line;
	while (getline(data, line, ' '))
	{
		if (line.length() > 0)
			paramsArr.push_back(line);
	}

	int mode = -1; //0 = maps; 1 = playerStrats; 2 = numGames; 3 = maxTurns;
	for (string param : paramsArr)
	{
		if (param == "-M") {
			mode = 0;
		}
		else if (param == "-P") {
			mode = 1;
		}
		else if (param == "-G") {
			mode = 2;
		}
		else if (param == "-D") {
			mode = 3;
		}
		else if (mode == 0) {
			maps.push_back(param);
		}
		else if (mode == 1 && PlayerStrategy::verifyPlayerStrategy(param) && param != "human") {
			Player* player = new Player(param, param);
			players.push_back(player);
		}
		else if (mode == 2 && isdigit(param)) {
			numGames = stoi(param);
			mode = -1;
		}
		else if (mode == 3 && isdigit(param)) {
			maxTurns = stoi(param);
			mode = -1;
		}
	}

	if (numGames < 0)
		numGames = 0;
	if (maxTurns < 0)
		maxTurns = 0;

	string winner[maps.size()][numGames];

	for (int i = 0; i < maps.size(); i++)
	{
		this->map->load(maps[i]);
		if (!this->map->validate()) {
			for (int j = 0; j < numGames; j++) {
				winner[i][j] = "MAP LOAD FAILED";
			}
			continue;
		}

		for (int j = 0; j < numGames; j++)
		{
			for (Player* player : players)
			{
				player->reset();
				this->players.push_back(player);
			}

			//randomize player order
			std::random_shuffle(std::begin(this->players), std::end(this->players));

			//distribute territories
			vector<Territory*> territories = this->map->getAllTerritories();
			std::random_shuffle(std::begin(territories), std::end(territories));

			for (int i = 0; i < territories.size(); i++) {
				int curPlayerIndex = this->players.size() - 1 - (i%this->players.size()); //last player(s) will have most territories if uneven territories
				Territory* territory = territories[i];
				Player* player = this->players[curPlayerIndex];
				player->addTerritory(territory);
			}

			//50 army units to each player
			//draw 2 each player
			for (Player* player : this->players)
			{
				player->addReinforcementsToPool(STARTING_REINFORCEMENTS_PER_PLAYER);
				for (int i = 0; i < STARTING_CARDS_PER_PLAYER; i++)
					deck->draw(player->getHand());
			}

			mainGameLoop(maxTurns);

			Player* p = getWinner();
			if (p == nullptr)
				winner[i][j] = "draw";
			else
				winner[i][j] = p->getName();

			//unload game
			this->players.clear();
			this->map->reset();
		}
		this->map->unload();
	}

	cout << "\n\nTournament mode:";
	cout << "\nM: ";
	for (int i = 0; i < maps.size(); i++)
	{
		cout << maps[i];
		if (i != maps.size()-1)
			cout << ", ";
	}

	cout << "\nP: ";
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i]->getName();
		if (i != players.size()-1)
			cout << ", ";
	}

	cout << "\nG: " << to_string(numGames);
	cout << "\nD: " << to_string(maxTurns);

	int width = 30;

	cout << "\n\nResults:\n";
	cout << left << setw(width) << setfill(' ') << "MAPS";
	for (int j = 0; j < numGames; j++)
	{
		cout << left << setw(width) << setfill(' ') << ("Game " + to_string(j+1));
	}
	for (int i = 0; i < maps.size(); i++)
	{
		cout << "\n";
		cout << left << setw(width) << setfill(' ') << maps[i];
		for (int j = 0; j < numGames; j++)
		{
			cout << left << setw(width) << setfill(' ') << winner[i][j];
		}
	}

	cout << "\nPRESS ENTER TO CONTINUE";
    string temp;
    getline(cin, temp);
}