//file: Cards.cpp
#include "Cards.h"
#include "Orders.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <time.h>
#include <sstream>
#include "Global.h"

using namespace std;

//Class Deck
Deck::Deck (int size){
    //Populate cardDeck vector with random card ptrs
    for(int i = 0; i < size; i++){
        Card *newCard = new Card;
        cardDeck.push_back(newCard);
    }
}
Deck::~Deck(){
    for(Card *c: cardDeck){
        delete(c);
        c = NULL;
    }
}

void Deck::draw(Hand *hand) {
    if(!cardDeck.empty()){
        hand->addToHand(cardDeck.back());
        cardDeck.pop_back();
    }
    else if (cmdDisplay)
        cout << "The Deck is empty.";
}

void Deck::addToDeck(Card *c){
    cardDeck.push_back(c);
}

ostream & operator << (ostream &out, const Deck &d){
    out << "Deck: \n";
    for(int i = 0; i < d.cardDeck.size(); i++)
        out << "\t" << *(d.cardDeck)[i] << '\n';
    return out << endl;
}


//************************************************************************************************
//Class Hand
//Constructor
Hand::Hand(int num) {
    sizeOfHand = num;
}
Hand::~Hand(){
    for(Card *c: cardsInHand){
        delete(c);
        c = NULL;
    }
}

vector<Card*> Hand::getHand(){
    return cardsInHand;
}

Card* Hand::getCard(int i){
    return cardsInHand[i];
}

void Hand::addToHand (Card* addCard) {
    //Push Card pointer into Hand vector
    if(cardsInHand.size() < sizeOfHand)
        cardsInHand.push_back(addCard);
    else if (cmdDisplay)
        cout << "Hand is full, please play a card to proceed" << endl;
}

void Hand::handToDeck(int index) {
    Card *cardTransferred;
    if(!cardsInHand.empty() && index < sizeOfHand){
        //Pop Card from vector
        cardTransferred = cardsInHand[index];
        engine->deck->addToDeck(cardTransferred);
        cardsInHand.erase(cardsInHand.begin() + index);
    }
    else if (cmdDisplay)
        cout << "The Hand is empty.";
}

bool Hand::hasCard(string type)
{
    for (Card* card : cardsInHand)
    {
        if (card->getType() == type)
        {
            return true;
        }
    }
    return false;
}

bool Hand::removeCard(string type)
{
    for (int i = 0; i < cardsInHand.size(); i++)
    {
        if (cardsInHand[i]->getType() == type)
        {
            cardsInHand.erase(cardsInHand.begin() + i);
            return true;
        }
    }
    return false;
}

ostream& operator<< (ostream &out, const Hand &h){
    out << "Hand: \n";
    for(Card* c : h.cardsInHand)
        out << "\t" << c->getType() << '\n';
    return out << endl;
}

//************************************************************************************************
//Class Card
//Constructor randomizes card type
Card::Card() {
    int i = rand()%4;
    switch(i){
        case 0:
            this->cardType = "bomb";
            this->order = new Bomb();
            break;
        case 1:
            this->cardType = "blockade";
            this->order = new Blockade();
            break;
        case 2:
            this->cardType = "airlift";
            this->order = new Airlift();
            break;
        case 3:
            this->cardType = "diplomacy";
            this->order = new Negotiate();
            break;
    }
}

Card::Card(string type)
{
    this->cardType = type;
}

Card::Card(const Card& card)
{
    string type = card.cardType;
    if(type == "bomb")
    {
        this->cardType = "bomb";
        this->order = new Bomb();
    }
    else if(type == "reinforcement")
    {
        this->cardType = "reinforcement";
        this->order = new Deploy();
    }
    else if(type == "blockade")
    {
        this->cardType = "blockade";
        this->order = new Blockade();
    }
    else if(type == "airlift")
    {
        this->cardType = "airlift";
        this->order = new Airlift();
    }
    else if(type == "diplomacy")
    {
        this->cardType = "diplomacy";
        this->order = new Negotiate();
    }
}


Card::~Card(){
    if (order != NULL) {
        delete(order);
        order = NULL;
    }
}

void Card::play(int index, Hand *h, Deck *d, OrderList *ol) {

    //card to order
    string cardType = h->getCard(index)->getType();
    Order* o = nullptr;
    std::istringstream is(cardType);
    is >> &o;
    ol->setOrderList(o);

    //Transfer Card from Hand to Deck
    if(index < ((*h).getHand()).size())
        h->handToDeck(index);
    else if (cmdDisplay)
        cout << "ERROR";
}

string Card::getType()
{
    return cardType;
}

ostream & operator << (ostream &out, const Card &c){
    out << c.cardType;
    return out;
}