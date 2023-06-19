#ifndef TERRITORY_H
#define TERRITORY_H

#include <iostream>
#include <vector>
class Player;

using namespace std;

class Territory
{
    public:
        Territory(string name);
        string getName();
        int getArmyCount();
        int addArmy(int armyCount);
        int removeArmy(int armyCount);
        vector<Territory*> getAdjTerritories();
        void addAdjTerritory(Territory*);
        void reset();
        bool visited;
        Player *owner;

        friend ostream& operator<<(ostream& out, const Territory& t);

    private:
        string name;
        int armyCount;
        vector<Territory*> territoriesAdj;

};

#endif