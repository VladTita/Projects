#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include "Player.h"
extern std::array<string, 5> strategies;

class PlayerStrategy
{
    public:
        PlayerStrategy(Player* player);
        ~PlayerStrategy();
        virtual bool issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        static bool verifyPlayerStrategy(string strat);
    protected:
        Player* player;
        int turnPlayed;
        int armyCount;
        int numAdvanceOrders;
        int numCardsToPlay;
        int numDeployOrders;

};

class HumanPlayerStrategy : public PlayerStrategy
{
    public:
        HumanPlayerStrategy(Player* player);
        ~HumanPlayerStrategy();
        bool issueOrder() override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

    private:
        bool done;
};

class AggressivePlayerStrategy : public PlayerStrategy
{
    public:
        AggressivePlayerStrategy(Player* player);
        ~AggressivePlayerStrategy();
        bool issueOrder() override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

};

class BenevolentPlayerStrategy : public PlayerStrategy
{
    public:
        BenevolentPlayerStrategy(Player* player);
        ~BenevolentPlayerStrategy();
        bool issueOrder() override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

};

class NeutralPlayerStrategy : public AggressivePlayerStrategy
{
    public:
        NeutralPlayerStrategy(Player* player);
        ~NeutralPlayerStrategy();
        bool issueOrder() override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
        bool isAggressive;

};

class CheaterPlayerStrategy : public PlayerStrategy
{
    public:
        CheaterPlayerStrategy(Player* player);
        ~CheaterPlayerStrategy();
        bool issueOrder() override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

};


#endif