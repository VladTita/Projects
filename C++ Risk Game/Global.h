#ifndef GLOBAL_CPP
#define GLOBAL_CPP
#include "GameEngine.h"
#include "LoggingObserver.h"
#include <iostream>
#include <fstream>

extern GameEngine* engine;
extern OrderList* protectedPlayers;
extern Subject* subject;
extern ofstream myfile;
extern int turnNumber;
extern bool cmdDisplay;
extern bool tournamentMode;
extern bool displayCmdOptions;

#endif