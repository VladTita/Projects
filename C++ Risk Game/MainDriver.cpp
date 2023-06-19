#include "CardsDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "Global.h"
#include "LoggingObserverDriver.h"
#include "PlayerStrategiesDriver.h"
#include "TournamentDriver.h"

#include <random>

struct ScopePrintGenerator {
    string s;
    ScopePrintGenerator(string s) : s(s)
    {
        cout << " ---- " << s << " ----\n";
    }
    ~ScopePrintGenerator()
    {
        cout << " DONE " << s << " ----\n";
        cout << "PRESS ENTER TO CONTINUE";
        string temp;
        getline(cin, temp);
    }
};

int main() {
    myfile.open ("gamelog.txt");
    //seed for random gen numbers
    srand(time(NULL));

    {
        ScopePrintGenerator x{"Player Strategies Driver"};
        testPlayerStrategies();
    }
    {
        ScopePrintGenerator x{"Tournament Driver"};
        testTournament();
    }
    myfile.close();
}