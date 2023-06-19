#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <array>
#include "LoggingObserver.h"

using namespace std;

class Player;
class Territory;

extern std::array<string, 7> order;

class Order
{
public:
    Order();
    ~Order();
    Order(string params);
    virtual void execute();
    string getName();
    virtual bool validate(Player* player);
    Player* player;

    friend istream &operator>>(istream &in, Order **o);

private:
    int orderType;
};

class Deploy : public Order, public Observer {
    public:
	    void Update();
        Deploy();
        virtual ~Deploy();
        Deploy(string params);
        void execute() override;
        bool validate(Player* player) override;
        int armyUnits;
        Territory* targetTerritory;
};

class Advance : public Order, public Observer {
    public:
	    void Update();
        Advance();
        virtual ~Advance();
        Advance(string params);
        void execute() override;
        bool validate(Player* player) override;
        int armyUnits;
        Territory* sourceTerritory;
        Territory* targetTerritory;
};

class Bomb : public Order, public Observer {
    public:
	    void Update();
        Bomb();
        virtual ~Bomb();
        Bomb(string params);
        void execute() override;
        bool validate(Player* player) override;
        Territory* targetTerritory;
};

class Blockade : public Order, public Observer {
    public:
	    void Update();
        Blockade();
        virtual ~Blockade();
        Blockade(string params);
        void execute() override;
        bool validate(Player* player) override;
        Territory* targetTerritory;
};

class Airlift : public Order, public Observer {
    public:
	    void Update();
        Airlift();
        virtual ~Airlift();
        Airlift(string params);
        void execute() override;
        bool validate(Player* player) override;
        int armyUnits;
        Territory* sourceTerritory;
        Territory* targetTerritory;
};

class Negotiate : public Order, public Observer {
    public:
	    void Update();
        Negotiate();
        virtual ~Negotiate();
        Negotiate(string params);
        void execute() override;
        bool validate(Player* player) override;
        Player* sourcePlayer;
        Player* targetPlayer;
};

void testOrdersLists();

class OrderList : public Observer {
    public:
	    void Update();
        OrderList();
        ~OrderList();
        vector<Order*> getOrderList();
        void setOrderList(Order* order);
        void remove(Order* removeOrder);
        void move(int position1, int position2);
    private:
        vector<Order*> orderList;
};