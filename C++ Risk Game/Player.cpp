#include "Player.h"
#include "PlayerStrategies.h"
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;
int Player::idCount = 0;
Player::Player(string strat, string name)
{
    this->playerId = idCount++;
    this->name = name;
    this->orders = new OrderList{};
    this->hand = new Hand{MAX_CARDS_HAND};
    this->reinforcementPool = 0;

    if (strat == "human")
        this->ps = new HumanPlayerStrategy(this);
    else if (strat == "aggressive")
        this->ps = new AggressivePlayerStrategy(this);
    else if (strat == "benevolent")
        this->ps = new BenevolentPlayerStrategy(this);
    else if (strat == "neutral")
        this->ps = new NeutralPlayerStrategy(this);
    else if (strat == "cheater")
        this->ps = new CheaterPlayerStrategy(this);
}


Player::~Player()
{
    this->playerId = playerId;
    this->name = name;
    delete this->orders;
    delete this->hand;
}

int Player::getPlayerId() const
{
    return playerId;
}

string Player::getName() const
{
    return name;
}

vector<Territory*> Player::getTerritories() const
{
    return territories;
}

vector<Territory*> Player::toAttack()
{
    return ps->toAttack();
}

vector<Territory*> Player::toDefend()
{
    return ps->toDefend();
}

int Player::getReinforcementPool() const
{
    return reinforcementPool;
}

int Player::addReinforcementsToPool(int num)
{
    return reinforcementPool += num;
}

int Player::removeReinforcementsFromPool(int num)
{
    return reinforcementPool -= num;
}

bool Player::hasTerritories()
{
    return !territories.empty();
}

void Player::addTerritory(Territory* territory)
{
    territory->owner = this;
	territories.push_back(territory);
}

void Player::removeTerritory(Territory* territory)
{
    if (dynamic_cast<NeutralPlayerStrategy*>(ps) != nullptr) {
        dynamic_cast<NeutralPlayerStrategy*>(ps)->isAggressive = true;
    }
    territories.erase(find(territories.begin(), territories.end(), territory));
    territory->owner = NULL;
}

void Player::reset()
{
    territories.clear();
    orders->getOrderList().clear();
    hand->getHand().clear();
    reinforcementPool = 0;
    if (dynamic_cast<NeutralPlayerStrategy*>(ps) != nullptr) {
        dynamic_cast<NeutralPlayerStrategy*>(ps)->isAggressive = false;
    }
}

bool Player::issueOrder()
{
    return ps->issueOrder();
}

Hand* Player::getHand() const
{
    return this->hand;
}

ostream & operator << (ostream &out, const Player &p){
    out << "ID: " << p.getPlayerId() << " - Name: " << p.getName();
    out << "\n\tReinforcement Pool: " << p.getReinforcementPool();
    out << "\n\tHand:\n";
    for (Card* card : p.getHand()->getHand()) {
        out << "\t\t" << *card << "\n";
    }
    out << "\n\tTerritories:\n";
    for (Territory* territory : p.getTerritories()) {
        out << "\t\t" << territory->getName() << "\n";
    }
    return out;
}