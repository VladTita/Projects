#include "Orders.h"
#include "OrdersDriver.h"
#include "Map.h"
#include <sstream>
#include "Player.h"
#include "Global.h"

void testOrdersExecution() {
    /*Player* p1 = new Player("P1");
    Player* p2 = new Player("P2");

    engine = new GameEngine();
    engine->map->load("maps/small.map");
    engine->map->validate();

    engine->players.push_back(p1);
    engine->players.push_back(p2);

    p1->addTerritory(engine->map->getTerritoryByName("Terr1"));
    p1->addTerritory(engine->map->getTerritoryByName("Terr3"));
    p2->addTerritory(engine->map->getTerritoryByName("Terr2"));

    p1->addReinforcementsToPool(20);
    p2->addReinforcementsToPool(20);

    //current army count
    cout << "\nBefore Deploy: " << engine->map->getTerritoryByName("Terr1")->getArmyCount();

    //deploy 5
    Deploy* deploy = new Deploy("5 Terr1");
    if(deploy->validate(p1))
        deploy->execute();
    cout << "\nAfter Deploy: " << engine->map->getTerritoryByName("Terr1")->getArmyCount();

    //deploy more than player pool
    deploy = new Deploy("50 Terr1");
    if(deploy->validate(p1))
        deploy->execute();
    cout << "\nAfter Deploy 2: " << engine->map->getTerritoryByName("Terr1")->getArmyCount();

    //order before player pool is empty
    Advance* advance = new Advance("10 Terr1 Terr2");
    if(advance->validate(p1))
    {
        cout << "\nAdvance Order is Valid";
        advance->execute();
    }
    else
        cout << "\nInvalid Advance Order";

    //finish deploy
    deploy = new Deploy("20 Terr2");
    if(deploy->validate(p2))
        deploy->execute();

    deploy = new Deploy("15 Terr3");
    if(deploy->validate(p1))
        deploy->execute();

    //bomb without card
    Bomb* bomb = new Bomb("Terr2");
    if(bomb->validate(p1))
    {
        cout << "\nBomb Order is Valid";
        bomb->execute();
    }
    else
        cout << "\nInvalid Bomb Order";

    //bomb with card
    Card* card = new Card("bomb");
    p1->getHand()->addToHand(card);
    cout << "\nBefore Bomb: " << engine->map->getTerritoryByName("Terr2")->getArmyCount();
    if(bomb->validate(p1))
        bomb->execute();

    cout << "\nAfter Bomb: " << engine->map->getTerritoryByName("Terr2")->getArmyCount();

    //airlift
    card = new Card("airlift");
    p1->getHand()->addToHand(card);
    Airlift* airlift = new Airlift("1 Terr1 Terr3");
    cout << "\nBefore Airlift: " << engine->map->getTerritoryByName("Terr3")->getArmyCount();
    if(airlift->validate(p1))
        airlift->execute();
    cout << "\nAfter Airlift: " << engine->map->getTerritoryByName("Terr3")->getArmyCount();

    //blockade
    card = new Card("blockade");
    p1->getHand()->addToHand(card);
    Blockade* blockade = new Blockade("Terr3");
    cout << "\nBefore Blockade: " << engine->map->getTerritoryByName("Terr3")->getArmyCount();
    if(blockade->validate(p1))
        blockade->execute();
    cout << "\nAfter Blockade: " << engine->map->getTerritoryByName("Terr3")->getArmyCount();
    cout << "\nOwner: " << engine->map->getTerritoryByName("Terr3")->owner;

    //negotiate
    card = new Card("diplomacy");
    Card* card2 = new Card("bomb");
    p1->getHand()->addToHand(card);
    p1->getHand()->addToHand(card2);
    Negotiate* negotiate = new Negotiate("P2");
    if(negotiate->validate(p1))
        negotiate->execute();
    if(bomb->validate(p1))
    {
        cout << "\nBomb Order is Valid";
        bomb->execute();
    }
    else
        cout << "\nInvalid Bomb Order";

    //del negotiate order (turn passed)
    protectedPlayers->remove(negotiate);


    //advance / winner
    engine->checkWin();
    cout << "\nCurrner Winner: " << engine->getWinner();
    cout << "\nTerr1: " << engine->map->getTerritoryByName("Terr1")->getArmyCount();
    cout << "\nTerr2: " << engine->map->getTerritoryByName("Terr2")->getArmyCount();
    advance = new Advance("8 Terr2 Terr1");
    if(advance->validate(p2))
        advance->execute();
    engine->checkWin();
    cout << "\nCurrner Winner: " << engine->getWinner()->getName();
    cout << "\nTerr1: " << engine->map->getTerritoryByName("Terr1")->getArmyCount();
    cout << "\nTerr1 owner: " << engine->map->getTerritoryByName("Terr1")->owner->getName();
    cout << "\nTerr2: " << engine->map->getTerritoryByName("Terr2")->getArmyCount();

    cout << "\n";*/
}


void testOrdersLists() { //Free function that tests all the features
    Order* o = nullptr;
    std::istringstream is("Deploy");
    is >> &o;

    OrderList OrderList;

    Order* deploy = nullptr;
    is = istringstream("Deploy");
    is >> &deploy;

    deploy->execute();

    Order* advance = nullptr;
    is = istringstream("Advance");
    is >> &advance;

    Order* bomb = nullptr;
    is = istringstream("Bomb");
    is >> &bomb;

    Order* blockade = nullptr;
    is = istringstream("Blockade");
    is >> &blockade;

    Order* airlift = nullptr;
    is = istringstream("Airlift");
    is >> &airlift;

    Order* negotiate = nullptr;
    is = istringstream("Negotiate");
    is >> &negotiate;

    Order* badOrder = nullptr;
    is = istringstream("random");
    is >> &badOrder;

    //cout << "validating bomb order: " << bomb->validate() << "\n";
    bomb->execute();
    //cout << "validating invalid order: " << badOrder->validate() << "\n";
    cout << "executing invalid order\n";
    badOrder->execute();
    OrderList.setOrderList(badOrder);
    OrderList.setOrderList(deploy);
    OrderList.setOrderList(advance);
    OrderList.setOrderList(bomb);
    OrderList.setOrderList(airlift);
    OrderList.setOrderList(negotiate);
    cout << "Order List: " << endl;
    for (int i=0; i<OrderList.getOrderList().size();i++) { //Displays OrderList on the terminal
        if (i==OrderList.getOrderList().size()-1) {
            cout << OrderList.getOrderList().at(i)->getName() << ".";
        }
        else {
            cout << OrderList.getOrderList().at(i)->getName() << ", ";
        }
    }
    cout << endl;
    OrderList.remove(airlift);
    OrderList.remove(deploy);
    cout << "Order List: " << endl;
    for (int i=0; i<OrderList.getOrderList().size();i++) {
        if (i==OrderList.getOrderList().size()-1) {
            cout << OrderList.getOrderList().at(i)->getName() << ".";
        }
        else {
            cout << OrderList.getOrderList().at(i)->getName() << ", ";
        }
    }
    cout << endl;
    OrderList.move(1,2);
    cout << "Order List: " << endl;
    for (int i=0; i<OrderList.getOrderList().size();i++) {
        if (i==OrderList.getOrderList().size()-1) {
            cout << OrderList.getOrderList().at(i)->getName() << ".";
        }
        else {
            cout << OrderList.getOrderList().at(i)->getName() << ", ";
        }
    }
    cout << endl;
    OrderList.move(1,4);
    cout << endl;
    cout << "Order List: " << endl;
    for (int i=0; i<OrderList.getOrderList().size();i++) {
        if (i==OrderList.getOrderList().size()-1) {
            cout << OrderList.getOrderList().at(i)->getName() << ".";
        }
        else {
            cout << OrderList.getOrderList().at(i)->getName() << ", ";
        }
    }
    cout << endl;
}