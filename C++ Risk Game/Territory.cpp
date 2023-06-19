#include "Territory.h"
#include <vector>

using namespace std;

Territory::Territory(string name)
{
    this->name = name;
    this->armyCount = 0;
}

string Territory::getName()
{
    return this->name;
}

int Territory::getArmyCount()
{
    return this->armyCount;
}

int Territory::addArmy(int armyCount)
{
    this->armyCount = this->armyCount + armyCount;
    return this->armyCount;
}

int Territory::removeArmy(int armyCount)
{
    this->armyCount = this->armyCount - armyCount > 0 ? this->armyCount - armyCount : 0;
    return this->armyCount;
}

vector<Territory*> Territory::getAdjTerritories()
{
    return territoriesAdj;
}

void Territory::addAdjTerritory(Territory* territory)
{
    this->territoriesAdj.push_back(territory);
}

void Territory::reset()
{
    armyCount = 0;
    owner = nullptr;
}

ostream &operator<<(ostream &out, const Territory &t)
{
    out << "Territory:" << endl;
    out << "\t name: " << t.name << endl;
    out << "\t army count: " << t.armyCount << endl;
    return out;
}
