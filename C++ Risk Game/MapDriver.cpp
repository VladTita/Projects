#include "Map.h"
#include "MapDriver.h"
#include <string>


void testLoadMaps()
{
    Map* map1 = loadMap("maps/valid.map");

    Map* map2 = loadMap("maps/invalid.map");

    Map* map3 = loadMap("maps/invalid_subgraph.map");
}

Map* loadMap(string filePath)
{
    cout << "\nLoading Map at location: " << filePath << "\n";
    Map* mapPtr = new Map();
    if (mapPtr->load(filePath))
    {
        cout << "Map Loaded\n";
        mapPtr->print();
        return mapPtr;
    }
    else
    {
        cout << "Map Loading Failed\n";
        return NULL;
    }
}