#ifndef CONTINENT_H
#define CONTINENT_H

#include <iostream>
#include <vector>
#include "Territory.h"
using namespace std;

class Continent
{
    public:
        Continent(string name, int controlValue);
        string getName();
        int getControlValue();
        void addTerritory(string name);
        vector<Territory*> getTerritories();

    private:
        string name;
        int controlValue;
        vector<Territory*> territories;



};

#endif