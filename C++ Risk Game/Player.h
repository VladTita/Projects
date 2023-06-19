#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Territory.h"
#include "Orders.h"
#include "Cards.h"

class PlayerStrategy;

class Player
{
    public:
        Player(string type, string name);
        ~Player();
        int getPlayerId() const;
        string getName() const;
        vector<Territory*> getTerritories() const;
        bool hasTerritories();
        void addTerritory(Territory *territory);
        void removeTerritory(Territory *territory);
        void reset();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        int getReinforcementPool() const;
        int addReinforcementsToPool(int num);
        int removeReinforcementsFromPool(int num);
        bool issueOrder();
        Hand* getHand() const;
        friend ostream & operator << (ostream&, const Player&);
        OrderList* orders;
        PlayerStrategy* ps;


    private:
        int playerId;
        string name;
        int reinforcementPool;
        vector<Territory*> territories;
        Hand* hand;

        const static int MAX_CARDS_HAND = 5;
        static int idCount;



};

#endif