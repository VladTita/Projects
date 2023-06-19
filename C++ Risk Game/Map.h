#ifndef MAP_H
#define MAP_H

#include <list>
#include "Continent.h"
#include <iostream>

class Map 
{
    public:
        Map();
        void unload();
        bool validate();
        bool validateList(vector<Territory*> territories);
        void addContinent(string name, int controlValue);
        Continent* getContinentByName(string name) const;
        Territory* getTerritoryByName(string name) const;
        Territory* getTerritoryByName(string name, string continentName) const;
        vector<Territory*> getAllTerritories() const;
        vector<Continent*> getAllContinents() const;
        void print();
        bool load(string filePath);
        bool DFS(vector<Territory*> territories, Territory* startTerritory);
        void DFSRecursive(vector<Territory*> territories, Territory* territory);
        void reset();

    private:
        vector<Continent*> continents;


};

#endif