#include "Global.h"

GameEngine* engine;
Subject* subject = new Subject();
OrderList* protectedPlayers = new OrderList();
ofstream myfile;
int turnNumber = 0;
bool cmdDisplay = true;
bool tournamentMode = false;
bool displayCmdOptions = true;