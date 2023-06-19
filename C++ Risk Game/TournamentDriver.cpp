#include "TournamentDriver.h"
#include "GameEngine.h"
#include "Global.h"

void testTournament()
{
    tournamentMode = true;
    cmdDisplay = false;

    engine = new GameEngine();
    engine->startupPhase();

    displayCmdOptions = false;
    engine = new GameEngine("tournament.txt");
    engine->startupPhase();
}