#include "Continent.h"
#include "Territory.h"
#include <iostream>

Continent::Continent(string name, int controlValue)
{
    this->name = name;
    this->controlValue = controlValue;
}

string Continent::getName()
{
    return this->name;
}

int Continent::getControlValue()
{
    return this->controlValue;
}

void Continent::addTerritory(string name)
{
    Territory* territory = new Territory(name);
    this->territories.push_back(territory);
}

vector<Territory*> Continent::getTerritories()
{
    return territories;
}