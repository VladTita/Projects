#include "Map.h"
#include "Continent.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include "Player.h"
#include "Global.h"

using namespace std;

Map::Map()
{

}

void Map::addContinent(string name, int controlValue)
{
    Continent* continent = new Continent(name, controlValue);
    this->continents.push_back(continent);
}

Continent* Map::getContinentByName(string name) const
{
    for (Continent* continentPtr : continents)
    {
        if (continentPtr->getName() == name)
        {
            return continentPtr;
        }
    }
    return NULL;
}

Territory* Map::getTerritoryByName(string name) const
{
    for (Continent* continentPtr : continents)
    {
        for (Territory* territoryPtr : continentPtr->getTerritories())
        {
            if (territoryPtr->getName() == name)
            {
                return territoryPtr;
            }
        }
    }
    return NULL;
}

Territory* Map::getTerritoryByName(string name, string continentName) const
{
    for (Continent* continentPtr : continents)
    {
        if (continentPtr->getName() == continentName)
        {
            for (Territory* territoryPtr : continentPtr->getTerritories())
            {
                if (territoryPtr->getName() == name)
                {
                    return territoryPtr;
                }
            }
        }

    }
    return NULL;
}

vector<Territory*> Map::getAllTerritories() const
{
    vector<Territory*> territories;
    for (Continent* continent : continents)
    {
        for (Territory* territory : continent->getTerritories())
        {
            territories.push_back(territory);
        }
    }
    return territories;
}

vector<Continent*> Map::getAllContinents() const
{
    return continents;
}

bool Map::validate()
{
    vector<Territory*> territories;
    //Validate Continent Sub-Graphs
    for (Continent* continentPtr : continents)
    {
        if(!validateList(continentPtr->getTerritories()))
        {
            return false;
        }
        for (Territory* territoryPtr : continentPtr->getTerritories())
        {
            territories.push_back(territoryPtr);
        }
    }

    //Validate Graph
    if(!validateList(territories))
    {
        return false;
    }

    if (territories.size() <= 1)
    {
        return false;
    }

    return true;
}

bool Map::validateList(vector<Territory*> territories)
{
    for (Territory* territory : territories)
    {
        if (!DFS(territories, territory))
        {
            return false;
        }
    }
    return true;
}

bool Map::DFS(vector<Territory*> territories, Territory* startTerritory)
{
    for (Territory* territory : territories)
    {
        territory->visited = false;
    }
    DFSRecursive(territories, startTerritory);
    for (Territory* territory : territories)
    {
        if (!territory->visited)
        {
            return false;
        }
    }
    return true;
}

void Map::DFSRecursive(vector<Territory*> territories, Territory* territory)
{
    territory->visited = true;
    for (Territory* adjTerritory : territory->getAdjTerritories())
    {
        if (!adjTerritory->visited)
        {
            for (Territory* ter : territories)
            {
                if (ter == adjTerritory)
                {
                    DFSRecursive(territories, adjTerritory);
                    break;
                }
            }
        }
    }
}

void Map::unload() {
    for(Continent *continent : continents) {
        for(Territory *territory : continent->getTerritories()) {
            delete territory;
        }
        delete continent;
    }
    continents.clear();
}

bool Map::load(string filePath)
{
    if (cmdDisplay)
        cout << "\n" << filePath;
    unload();
    string line;
    //STATES
    //NONE = 0
    //CONTINENTS = 1
    //TERRITORIES = 2
    int curState = 0;
    try {
        for (int runNum = 1; runNum <= 2; runNum++)
        {
            ifstream myfile(filePath);
            if (myfile.is_open())
            {
                while (getline(myfile, line))
                {
                    if (line[line.size()-1] == '\r')
                        line = line.substr(0, line.size()-1);
                    if (curState == 0)
                    {
                        if (line == "[Continents]")
                        {
                            curState = 1;
                        }
                        else if (line == "[Territories]")
                        {
                            curState = 2;
                        }
                    }
                    else
                    {
                        if (line == "")
                        {
                            curState = 0;
                        }
                        else if (runNum == 1)
                        {
                            if (curState == 1)
                            {
                                string delimiter = "=";
                                string continentName = line.substr(0, line.find(delimiter));
                                string controlValStr = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                                addContinent(continentName, stoi(controlValStr));
                            }
                            else if (curState == 2)
                            {
                                string delimiter = ",";
                                string territoryName = line.substr(0, line.find(delimiter));
                                line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                                line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                                line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                                string continentName = line.substr(0, line.find(delimiter));

                                getContinentByName(continentName)->addTerritory(territoryName);
                            }
                        }
                        else if (runNum == 2 && curState == 2)
                        {
                            string delimiter = ",";
                            string territoryName = line.substr(0, line.find(delimiter));
                            line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                            line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                            line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                            string continentName = line.substr(0, line.find(delimiter));

                            Territory* territory = getTerritoryByName(territoryName);
                            while (line.find(delimiter) != -1)
                            {
                                line = line.substr(line.find(delimiter) + 1, line.size() - line.find(delimiter) - 1);
                                string adjTerritoryStr = line.substr(0, line.find(delimiter));
                                Territory* adjTerritory = getTerritoryByName(adjTerritoryStr);
                                territory->addAdjTerritory(adjTerritory);
                            }
                        }
                    }
                }
            }
            else
            {
                if (cmdDisplay)
                    cout << "\nUnable to open file";
                return false;
            }

        }
    }
    catch (...) {
        return false;
    }
    return validate();
}

void Map::print()
{
    for (Continent* continentPtr : continents)
    {
        Continent continent = *continentPtr;
        cout << continent.getName();
        cout << "\n-----\n";
        for (Territory* territoryPtr : continent.getTerritories())
        {
            cout << territoryPtr->getName();

            cout << "\n\tOwner: " << territoryPtr->owner->getName();
            cout << "\n\tArmy Count: " << territoryPtr->getArmyCount();

            cout << "\n\tAdjacent Territories";
            for (Territory* adjTerritoriesPtr : territoryPtr->getAdjTerritories())
            {
                cout << " - ";
                cout << adjTerritoriesPtr->getName();
            }
            cout << "\n";
        }
        cout << "-----\n\n";
    }
}

void Map::reset()
{
    for (Territory* terr : getAllTerritories())
    {
        terr->reset();
    }
}