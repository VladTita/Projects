#include "Orders.h"
#include "Global.h"
#include<cxxabi.h>
std::array<string, 7> order = {"invalid", "deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
string delim = " ";
istream &operator>>(istream &in, Order **o)
{
    delete *o;
    string name;
    getline(in, name);

    string params = name.substr(name.find(" ") + 1);
    name = name.substr(0, name.find(" "));

    auto itr = find(order.begin(), order.end(), name);
    *o = new Order();
    if (itr != order.end())
    {
        delete *o;
        const int index = itr - order.begin();
        switch (index)
        {
        case 1:
            *o = new Deploy(params);
            break;
        case 2:
            *o = new Advance(params);
            break;
        case 3:
            *o = new Bomb(params);
            break;
        case 4:
            *o = new Blockade(params);
            break;
        case 5:
            *o = new Airlift(params);
            break;
        case 6:
            *o = new Negotiate(params);
            break;
        default:
            *o = new Order(params);
            break;
        }
        (*o)->orderType = index;
    }
    return in;
}

Order::Order(){}
Deploy::Deploy(){}
Advance::Advance(){}
Bomb::Bomb(){}
Blockade::Blockade(){}
Airlift::Airlift(){}
Negotiate::Negotiate(){}

Order::~Order(){

}
Deploy::~Deploy() {
    subject->Detach(this);
}
Advance::~Advance() {
    subject->Detach(this);
}
Bomb::~Bomb() {
    subject->Detach(this);
}
Blockade::~Blockade() {
    subject->Detach(this);
}
Airlift::~Airlift() {
    subject->Detach(this);
}
Negotiate::~Negotiate() {
    subject->Detach(this);
}

Order::Order(string params){
}

Deploy::Deploy(string params) { // Deploy is a sub-class of Order
    subject->Attach(this);
    //deploy <armyUnits> <targetTerritory>
    armyUnits = stoi(params.substr(0, params.find(delim)));
    string terrName = params.substr(params.find(delim) + 1);
    targetTerritory = engine->map->getTerritoryByName((params.substr(params.find(delim) + 1)));
}

Advance::Advance(string params) { //Advance is a sub-class of Order
    subject->Attach(this);
    //advance <armyUnits> <sourceTerritory> <targetTerritory>
    armyUnits = stoi(params.substr(0, params.find(delim)));
    params = params.substr(params.find(delim) + 1);
    sourceTerritory = engine->map->getTerritoryByName(params.substr(0, params.find(delim)));
    targetTerritory = engine->map->getTerritoryByName(params.substr(params.find(delim) + 1));
}

Bomb::Bomb(string params) { //Bomb is a sub-class of Order
    subject->Attach(this);
    //bomb <targetTerritory>
    targetTerritory = engine->map->getTerritoryByName(params);
}

Blockade::Blockade(string params) { //Blockade is a sub-class of Order
    subject->Attach(this);
    //blockade <targetTerritory>
    targetTerritory = engine->map->getTerritoryByName(params);
}

Airlift::Airlift(string params) { //Airlift is a sub-class of Order
    subject->Attach(this);
    //airlift <armyUnits> <sourceTerritory> <targetTerritory>
    armyUnits = stoi(params.substr(0, params.find(delim)));
    params = params.substr(params.find(delim) + 1);
    sourceTerritory = engine->map->getTerritoryByName(params.substr(0, params.find(delim)));
    targetTerritory = engine->map->getTerritoryByName(params.substr(params.find(delim) + 1));
}

Negotiate::Negotiate(string params) { //Negotiate is a sub-class of Order
    subject->Attach(this);
    //negotiate <targetPlayer>
    for (Player* player : engine->players)
    {
        if (player->getName() == params)
        {
            targetPlayer = player;
            break;
        }
    }
}

string Order::getName() {
    return abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr);
}

void Order::execute() {
    if (cmdDisplay)
        cout << "\nError: invalid order" << endl;
    subject->Notify();
}

void Deploy::execute() { // Deploy is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Deploy Order" << endl;
    player->removeReinforcementsFromPool(armyUnits);
    targetTerritory->addArmy(armyUnits);
    subject->Notify();
}

void Advance::execute() { //Advance is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Advance Order" << endl;
    sourceTerritory->removeArmy(armyUnits);
    if (sourceTerritory->owner == targetTerritory->owner)
    {
        targetTerritory->addArmy(armyUnits);
    }
    else
    {
        //ATTACK
        int i = 0;
        while (armyUnits > 0 && targetTerritory->getArmyCount() > 0)
        {
            if (armyUnits < i && targetTerritory->getArmyCount() < i)
            {
                i = 0;
            }
            if (armyUnits > i && 1 + (rand() % 100) <= 60)
            {
                targetTerritory->removeArmy(1);
            }
            if (targetTerritory->getArmyCount() > i && 1 + (rand() % 100) <= 70)
            {
                armyUnits--;
            }
            i++;
        }
        if (targetTerritory->getArmyCount() == 0)
        {
            targetTerritory->owner->removeTerritory(targetTerritory);
            sourceTerritory->owner->addTerritory(targetTerritory);
            targetTerritory->addArmy(armyUnits);
        }
    }
    subject->Notify();
}

void Bomb::execute() { //Bomb is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Bomb Order" << endl;
    if (!player->getHand()->removeCard("bomb"))
    {
        cout << "\nCan not execute. Card not found." << endl;
    }
    int bombed = targetTerritory->getArmyCount()/2;
    targetTerritory->removeArmy(bombed);
    subject->Notify();
}

void Blockade::execute() { //Blockade is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Blockade Order" << endl;
    if (!player->getHand()->removeCard("blockade"))
    {
        if (cmdDisplay)
            cout << "\nCan not execute. Card not found." << endl;
    }
    targetTerritory->addArmy(targetTerritory->getArmyCount());
    player->removeTerritory(targetTerritory);
    subject->Notify();
}

void Airlift::execute() { //Airlift is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Airlift Order" << endl;
    if (!player->getHand()->removeCard("airlift"))
    {
        if (cmdDisplay)
            cout << "\nCan not execute. Card not found." << endl;
    }
    sourceTerritory->removeArmy(armyUnits);
    targetTerritory->addArmy(armyUnits);
    subject->Notify();
}

void Negotiate::execute() { //Negotiate is a sub-class of Order
    if (cmdDisplay)
        cout << "\nExecuting Negotiate Order" << endl;
    if (!player->getHand()->removeCard("diplomacy"))
    {
        if (cmdDisplay)
            cout << "\nCan not execute. Card not found." << endl;
    }
    protectedPlayers->setOrderList(this);
    subject->Notify();
}

OrderList::OrderList() {
    subject->Attach(this);
}

OrderList::~OrderList() {
    subject->Detach(this);
}

vector<Order*> OrderList::getOrderList() { //Accessor method that returns the vector OrderList
    return orderList;
}

void OrderList::setOrderList(Order* order) { //Mutator method that adds an Order to the end of the vector OrderList
    orderList.push_back(order);
    subject->Notify();
}

void OrderList::remove(Order* removeOrder) { //Remove method that removes an Order from the list
    for (int i = 0; i < orderList.size(); i++) {
        if(orderList.at(i) == removeOrder)
        {
            orderList.erase(orderList.begin()+i); //Removes the concerned Order
        }
    }
}

void OrderList::move(int position1, int position2) { //Move method that swaps two Orders to adjust the order of OrderList
    if (cmdDisplay)
        cout << "Moving Orders in positions " << position1 << " and " << position2 << endl;
    if (position1 < 0 || position2 < 0 || position1 >= orderList.size() || position2 >= orderList.size()) {
        if (cmdDisplay)
            cout << "Positions invalid. Move operation not executed.";
    }
    else {
        Order* temp;
        temp = orderList.at(position1); //Temporary placeholder to preserve Order at position1
        orderList.at(position1) = orderList.at(position2);
        orderList.at(position2) = temp;
    }
}

bool Order::validate(Player* player) {
    this->player = player;
    return false;
}

bool Deploy::validate(Player* player) { // Deploy is a sub-class of Order
    this->player = player;
    if (targetTerritory == NULL)
        return false;

    if (armyUnits <= 0)
        return false;

    if (player->getReinforcementPool() < armyUnits)
        return false;

    if (targetTerritory->owner != player)
        return false;

    return true;
}

bool Advance::validate(Player* player) { //Advance is a sub-class of Order
    this->player = player;
    if (player->getReinforcementPool() > 0)
        return false;

    if (sourceTerritory == NULL)
        return false;

    if (targetTerritory == NULL)
        return false;

    if (armyUnits <= 0)
        return false;

    if (armyUnits >= sourceTerritory->getArmyCount())
        return false;

    if (sourceTerritory->owner != player)
        return false;

    bool found = false;
    for (Territory* territory : sourceTerritory->getAdjTerritories())
    {
        if (territory == targetTerritory){
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    if (targetTerritory->owner != player)
    {
        for (Order* order : protectedPlayers->getOrderList())
        {
            Negotiate* negotiate = dynamic_cast<Negotiate*>(order);
            if (negotiate->sourcePlayer == player && negotiate->targetPlayer == targetTerritory->owner)
                return false;

            if (negotiate->sourcePlayer == targetTerritory->owner && negotiate->targetPlayer == player)
                return false;
        }
    }

    return true;
}

bool Bomb::validate(Player* player) { //Bomb is a sub-class of Order
    this->player = player;
    if (player->getReinforcementPool() > 0)
        return false;

    if (targetTerritory == NULL)
        return false;

    if (targetTerritory->owner == player)
        return false;

    if (!player->getHand()->hasCard("bomb"))
        return false;

    for (Order* order : protectedPlayers->getOrderList())
    {
        Negotiate* negotiate = dynamic_cast<Negotiate*>(order);
        if (negotiate->sourcePlayer == player && negotiate->targetPlayer == targetTerritory->owner)
            return false;

        if (negotiate->sourcePlayer == targetTerritory->owner && negotiate->targetPlayer == player)
            return false;
    }


    for (Territory* territory : player->getTerritories())
    {
        for (Territory* adjTerr : territory->getAdjTerritories())
        {
            if (adjTerr == targetTerritory)
            {
                return true;
            }
        }
    }

    return false;
}

bool Blockade::validate(Player* player) { //Blockade is a sub-class of Order
    this->player = player;
    if (player->getReinforcementPool() > 0)
        return false;

    if (targetTerritory == NULL)
        return false;

    if (targetTerritory->owner != player)
        return false;

    if (!player->getHand()->hasCard("blockade"))
        return false;

    return true;
}

bool Airlift::validate(Player* player) { //Airlift is a sub-class of Order
    this->player = player;
    if (player->getReinforcementPool() > 0)
        return false;

    if (sourceTerritory == NULL)
        return false;

    if (targetTerritory == NULL)
        return false;

    if (armyUnits <= 0)
        return false;

    if (sourceTerritory->owner != player)
        return false;

    if (targetTerritory->owner != player)
        return false;

    if (!player->getHand()->hasCard("airlift"))
        return false;

    return true;
}

bool Negotiate::validate(Player* player) { //Negotiate is a sub-class of Order
    this->player = player;
    sourcePlayer = player;
    if (player->getReinforcementPool() > 0)
        return false;

    if (sourcePlayer == targetPlayer)
        return false;

    if (sourcePlayer == NULL)
        return false;

    if (!player->getHand()->hasCard("diplomacy"))
        return false;

    return true;
}

void OrderList::Update() {
    /*myfile << "ORDER LIST:\n";
    for (Order* order : this->orderList)
    {
        myfile << "\t" << order->getName() << "\n";
    }*/
}

void Deploy::Update(){
    myfile << "Order: " << this->getName() << "\n";
}
void Advance::Update(){
    myfile << "Order: " << this->getName() << "\n";
}
void Bomb::Update(){
    myfile << "Order: " << this->getName() << "\n";
}
void Blockade::Update(){
    myfile << "Order: " << this->getName() << "\n";
}
void Airlift::Update(){
    myfile << "Order: " << this->getName() << "\n";
}
void Negotiate::Update(){
    myfile << "Order: " << this->getName() << "\n";
}