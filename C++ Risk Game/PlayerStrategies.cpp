#include "PlayerStrategies.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include "Global.h"
using namespace std;

std::array<string, 5> strategies = {"human", "aggressive", "benevolent", "neutral", "cheater"};

bool PlayerStrategy::verifyPlayerStrategy(string strat)
{
    return std::find(std::begin(strategies), std::end(strategies), strat) != std::end(strategies);
}

PlayerStrategy::PlayerStrategy(Player* player)
{
    this->player = player;
    turnPlayed = 0;
}

PlayerStrategy::~PlayerStrategy()
{

}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {
    done = false;
}
HumanPlayerStrategy::~HumanPlayerStrategy() {}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : AggressivePlayerStrategy(player) {
    isAggressive = false;
}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player) {}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

bool HumanPlayerStrategy::issueOrder()
{
    if (turnPlayed != turnNumber) {
        done = false;
        turnPlayed = turnNumber;
    }

    if (done)
        return false;

    if (cmdDisplay)
        cout << "\nPlayer " << this->player->getName() << " (" << player->getPlayerId() << ") issue order (empty string for none): ";
    //get order from player
    Order* order = nullptr;
    string temp;
    getline(cin, temp);

    if (temp == "") {
        done = true;
        return false;
    }

    std::istringstream is(temp);
    is >> &order;
    //return true if theres an order
    this->player->orders->setOrderList(order);
    return true;
}

bool AggressivePlayerStrategy::issueOrder()
{
    if (turnPlayed != turnNumber)
    {
        turnPlayed = turnNumber;
        armyCount = player->getReinforcementPool();
        numAdvanceOrders = 3;
        numCardsToPlay = 1;
    }

    //deploy <armyUnits> <targetTerritory>
    if (armyCount > 0) {
        int armyUnits = armyCount;
        armyCount = 0;

        Order* order = nullptr;
        std::istringstream is(string("deploy ") + to_string(armyUnits) + string(" ") + toDefend().front()->getName());
        is >> &order;
        this->player->orders->setOrderList(order);
        return true;
    }

    //move units to largest territory from smallest nearby with more than 1 unit
    if (numAdvanceOrders > 0 && rand() > 0.8) {
        numAdvanceOrders--;
        Territory* largestTerritory = toDefend().front();

        Territory* smallestNearbyTerritory = nullptr;
        for (Territory* territory : largestTerritory->getAdjTerritories())
        {
            if (territory->owner != player) {
                if (smallestNearbyTerritory == nullptr) {
                    smallestNearbyTerritory = territory;
                }
                else if (smallestNearbyTerritory->getArmyCount() > territory->getArmyCount() && rand() > 0.4) {
                    smallestNearbyTerritory = territory;
                }
            }
        }

        //advance <armyUnits> <sourceTerritory> <targetTerritory>
        if (smallestNearbyTerritory != nullptr)
        {
            int armyUnits = largestTerritory->getArmyCount() - 1;

            Order* order = nullptr;
            std::istringstream is(string("advance ") + to_string(armyUnits) + string(" ") + largestTerritory->getName() + " " + smallestNearbyTerritory->getName());
            is >> &order;
            this->player->orders->setOrderList(order);
            return true;
        }
    }

    //play card
    if (numCardsToPlay > 0) {
        numCardsToPlay--;
        for (Card* card : player->getHand()->getHand()) {
            //bomb <targetTerritory>
            if (card->getType() == "bomb") {
                Territory* bombedTerritory = nullptr;
                for (Territory* terr : toDefend().front()->getAdjTerritories())
                {
                    if (terr->owner != player) {
                        bombedTerritory = terr;
                        break;
                    }
                }
                if (bombedTerritory == nullptr)
                    return false;

                Order* order = nullptr;
                std::istringstream is(string("bomb ") + bombedTerritory->getName());
                is >> &order;
                this->player->orders->setOrderList(order);
                return true;
            }
            //airlift <armyUnits> <sourceTerritory> <targetTerritory>
            else if(card->getType() == "airlift")
            {
                Territory* airliftTerritory = nullptr;
                for (Territory* terr : player->getTerritories())
                {
                    if (terr->owner == player && terr->getArmyCount() > 1 && terr != toDefend().front()) {
                        airliftTerritory = terr;
                        break;
                    }
                }

                if (airliftTerritory == nullptr)
                    return false;

                Order* order = nullptr;
                std::istringstream is(string("airlift ") + to_string(airliftTerritory->getArmyCount() - 1) + string(" ") + airliftTerritory->getName() + string(" ") + toDefend().front()->getName());
                is >> &order;
                this->player->orders->setOrderList(order);
                return true;
            }
        }
    }
    return false;
}

bool BenevolentPlayerStrategy::issueOrder()
{
    if (turnPlayed != turnNumber)
    {
        turnPlayed = turnNumber;
        armyCount = player->getReinforcementPool();
        numAdvanceOrders = 1;
        numDeployOrders = 3;
        numCardsToPlay = 1;
    }

    //deploy <armyUnits> <targetTerritory>
    if (numDeployOrders > 0) {
        numDeployOrders--;
        int armyUnits = 0;
        if (numDeployOrders > 0)
            armyUnits = player->getReinforcementPool() / 3;
        else
            armyUnits = armyCount;

        armyCount -= armyUnits;
        Order* order = nullptr;
        std::istringstream is(string("deploy ") + to_string(armyUnits) + string(" ") + toDefend()[numDeployOrders]->getName());
        is >> &order;
        this->player->orders->setOrderList(order);
        return true;
    }

    //move units from largest to smallest nearby territory
    if (numAdvanceOrders > 0 && rand() > 0.8) {
        numAdvanceOrders--;

        Territory* largestTerritory = player->getTerritories().front();
        for (Territory* territory : player->getTerritories())
        {
            if (largestTerritory->getArmyCount() < territory->getArmyCount()) {
                largestTerritory = territory;
            }
        }

        Territory* smallestNearbyTerritory = nullptr;
        for (Territory* territory : largestTerritory->getAdjTerritories())
        {
            if (territory->owner == player) {
                if (smallestNearbyTerritory == nullptr) {
                    smallestNearbyTerritory = territory;
                }
                else if (smallestNearbyTerritory->getArmyCount() > territory->getArmyCount()) {
                    smallestNearbyTerritory = territory;
                }
            }
        }

        //advance <armyUnits> <sourceTerritory> <targetTerritory>
        if (smallestNearbyTerritory != nullptr)
        {
            int armyUnits = (largestTerritory->getArmyCount() - smallestNearbyTerritory->getArmyCount()) / 2;

            Order* order = nullptr;
            std::istringstream is(string("advance ") + to_string(armyUnits) + string(" ") + largestTerritory->getName() + " " + smallestNearbyTerritory->getName());
            is >> &order;
            this->player->orders->setOrderList(order);
            return true;
        }
    }

    //play card
    if (numCardsToPlay > 0) {
        numCardsToPlay--;
        for (Card* card : player->getHand()->getHand()) {
            //airlift <armyUnits> <sourceTerritory> <targetTerritory>
            if(card->getType() == "airlift")
            {
                Territory* airliftTerritory = player->getTerritories().front();
                for (Territory* terr : player->getTerritories())
                {
                    if (airliftTerritory->getArmyCount() < terr->getArmyCount()) {
                        airliftTerritory = terr;
                    }
                }

                if (airliftTerritory == nullptr)
                    return false;

                int armyUnits = 0;

                if (airliftTerritory->getArmyCount() < 10)
                    armyUnits = airliftTerritory->getArmyCount()/2;
                else if (airliftTerritory->getArmyCount() > 3 * toDefend().front()->getArmyCount())
                    armyUnits = (airliftTerritory->getArmyCount() - toDefend().front()->getArmyCount()) / 4;
                else
                    armyUnits = (airliftTerritory->getArmyCount() - toDefend().front()->getArmyCount()) / 8;

                Order* order = nullptr;

                std::istringstream is(string("airlift ") + to_string(armyUnits) + string(" ") + airliftTerritory->getName() + string(" ") + toDefend().front()->getName());
                is >> &order;
                this->player->orders->setOrderList(order);
                return true;
            }
            //negotiate <targetPlayer>
            else if(card->getType() == "diplomacy")
            {
                for (Player* player : engine->players)
                {
                    if (player != this->player)
                    {
                        Order* order = nullptr;

                        std::istringstream is(string("negotiate ") + player->getName());
                        is >> &order;
                        this->player->orders->setOrderList(order);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool NeutralPlayerStrategy::issueOrder()
{
    if (isAggressive)
        return AggressivePlayerStrategy::issueOrder();
    return false;
}

bool CheaterPlayerStrategy::issueOrder()
{
    if (turnPlayed != turnNumber) {
        for (Territory* territory : this->toAttack())
        {
            territory->owner->removeTerritory(territory);
            player->addTerritory(territory);
        }
        turnPlayed = turnNumber;
    }
    return false;
}

//returns a list of territories that can be attacked
vector<Territory*> HumanPlayerStrategy::toAttack()
{
    vector<Territory*> adjTerritories;
    for (Territory* territory : player->getTerritories())
    {
        for (Territory* adjTerr : territory->getAdjTerritories())
        {
            if (std::find(std::begin(adjTerritories), std::end(adjTerritories), adjTerr) == std::end(adjTerritories))
                adjTerritories.push_back(adjTerr);
        }
    }
    return adjTerritories;
}

//returns a list of territories that can be reinforced
vector<Territory*> HumanPlayerStrategy::toDefend()
{
    return this->player->getTerritories();
}

/*returns the enemy territory with the least army camp
that lies next to the player's territory with largest army count*/
vector<Territory*> AggressivePlayerStrategy::toAttack()
{
    vector<Territory*> territories;
    for (Territory* territory : toDefend())
    {
        for(Territory* adjTerritory : territory->getAdjTerritories())
        {
            if (adjTerritory->owner != player)
            {
                territories.push_back(adjTerritory);
            }
        }
    }
    return territories;
}

//returns the territory with the largest army count
vector<Territory*> AggressivePlayerStrategy::toDefend()
{
    vector<Territory*> territories;
    territories.push_back(player->getTerritories().front());
    for (Territory* territory : player->getTerritories())
    {
        if (territories.front()->getArmyCount() < territory->getArmyCount()) {
            territories.pop_back();
            territories.push_back(territory);
        }
    }
    return territories;
}

//returns empty list
vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
    vector<Territory*> territories;
    return territories;
}

bool compareTerritoryByArmyCount(Territory* t1, Territory* t2)
{
    return (t1->getArmyCount() < t2->getArmyCount());
}

//returns 3 territories with least army count
vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory*> territories;
    vector<Territory*> allTerritories = player->getTerritories();


    std::sort(std::begin(allTerritories), std::end(allTerritories), compareTerritoryByArmyCount);

    int i = 3;
    while (i >= 0) {
        for (Territory* territory : allTerritories)
        {
            i--;
            if (i < 0)
                break;

            territories.push_back(territory);
        }
    }

    return territories;
}

//returns empty list if hasn't been attacked; otherwise acts like aggressive player.
vector<Territory*> NeutralPlayerStrategy::toAttack()
{
    if (isAggressive)
        return AggressivePlayerStrategy::toAttack();

    vector<Territory*> territories;
    return territories;
}

//returns empty list if hasn't been attacked; otherwise acts like aggressive player.
vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    if (isAggressive)
        return AggressivePlayerStrategy::toDefend();

    vector<Territory*> territories;
    return territories;
}

//returns list of all adjacent territories
vector<Territory*> CheaterPlayerStrategy::toAttack()
{
    vector<Territory*> adjTerritories;
    for (Territory* territory : player->getTerritories())
    {
        for (Territory* adjTerr : territory->getAdjTerritories())
        {
            if (std::find(std::begin(adjTerritories), std::end(adjTerritories), adjTerr) == std::end(adjTerritories))
                adjTerritories.push_back(adjTerr);
        }
    }
    return adjTerritories;
}

//returns empty list
vector<Territory*> CheaterPlayerStrategy::toDefend()
{
    vector<Territory*> territories;
    return territories;
}