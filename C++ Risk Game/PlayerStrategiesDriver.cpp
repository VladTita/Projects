#include "PlayerStrategiesDriver.h"
#include "Map.h"
#include <sstream>
#include "Player.h"
#include "PlayerStrategies.h"
#include "Global.h"

void testPlayerStrategies()
{
    //neutral & aggressive player
    Player* p1 = new Player("neutral", "Player 1");
    Player* p2 = new Player("aggressive", "Aggressive Player");

    engine = new GameEngine();
    engine->map->load("maps/small.map");
    engine->map->validate();

    engine->players.push_back(p1);
    engine->players.push_back(p2);

    p1->addTerritory(engine->map->getTerritoryByName("Terr1"));
    p1->addTerritory(engine->map->getTerritoryByName("Terr2"));
    p2->addTerritory(engine->map->getTerritoryByName("Terr3"));

    p1->addReinforcementsToPool(200);
    p2->addReinforcementsToPool(2);

    engine->mainGameLoop();

    engine->map->unload();
    p1->reset();
    p2->reset();

    //benevolent & aggressive player
    p1->ps = new BenevolentPlayerStrategy(p1);
    engine->map->load("maps/small.map");
    engine->map->validate();
    engine->players.push_back(p2);

    p1->addTerritory(engine->map->getTerritoryByName("Terr1"));
    p1->addTerritory(engine->map->getTerritoryByName("Terr2"));
    p2->addTerritory(engine->map->getTerritoryByName("Terr3"));

    p1->addReinforcementsToPool(200);
    p2->addReinforcementsToPool(200);
    engine->mainGameLoop();

    engine->map->unload();
    engine->players.clear();

    //cheater & aggressive player
    p1 = new Player("cheater", "Cheater Player");
    p2 = new Player("aggressive", "Aggressive Player");

    engine->map->load("maps/small.map");
    engine->map->validate();

    engine->players.push_back(p1);
    engine->players.push_back(p2);

    p1->addTerritory(engine->map->getTerritoryByName("Terr1"));
    p2->addTerritory(engine->map->getTerritoryByName("Terr2"));
    p2->addTerritory(engine->map->getTerritoryByName("Terr3"));

    p1->addReinforcementsToPool(10);
    p2->addReinforcementsToPool(200);
    engine->mainGameLoop();

    engine->map->unload();
    engine->players.clear();

    //human, aggressive & benevolent player with cards
    Player* p3 = new Player("human", "Human Player");
    Player* p4 = new Player("aggressive", "Aggressive Player");
    Player* p5 = new Player("benevolent", "Benevolent Player");

    engine->map->load("maps/line.map");
    engine->map->validate();

    engine->players.push_back(p3);
    engine->players.push_back(p4);
    engine->players.push_back(p5);

    p3->addTerritory(engine->map->getTerritoryByName("TerrC"));
    p4->addTerritory(engine->map->getTerritoryByName("TerrA1"));
    p4->addTerritory(engine->map->getTerritoryByName("TerrA2"));
    p4->addTerritory(engine->map->getTerritoryByName("TerrA3"));
    p5->addTerritory(engine->map->getTerritoryByName("TerrB1"));
    p5->addTerritory(engine->map->getTerritoryByName("TerrB2"));
    p5->addTerritory(engine->map->getTerritoryByName("TerrB3"));

    p3->addReinforcementsToPool(200);
    p4->addReinforcementsToPool(10);
    p5->addReinforcementsToPool(10);

    Card* bomb1 = new Card("bomb");
    Card* bomb2 = new Card("bomb");
    Card* airlift1 = new Card("airlift");
    Card* airlift2 = new Card("airlift");
    Card* negotiate1 = new Card("diplomacy");
    Card* negotiate2 = new Card("diplomacy");

    p4->getHand()->addToHand(bomb1);
    p4->getHand()->addToHand(airlift1);
    p4->getHand()->addToHand(negotiate1);
    p5->getHand()->addToHand(bomb2);
    p5->getHand()->addToHand(airlift2);
    p5->getHand()->addToHand(negotiate2);

    engine->mainGameLoop(5);
}