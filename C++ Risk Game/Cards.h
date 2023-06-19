// file : Cards.h
#ifndef CARDS_H
#define CARDS_H
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

class Hand;
class Card;
class Order;
class OrderList;

 //Class Deck declaration
class Deck {
    public:
        Deck(int);
        ~Deck();
        void draw(Hand*);
        void addToDeck(Card*);
        friend ostream & operator << (ostream&, const Deck&);
    private:
        vector<Card*> cardDeck;
};

//Class Hand declaration
class Hand {
    public:
        Hand(int);
        ~Hand(); 
        vector<Card*> getHand();
        Card* getCard(int);
        void addToHand(Card*);
        void handToDeck(int);
        bool hasCard(string type);
        bool removeCard(string type);
        friend ostream & operator << (ostream&, const Hand&);
    private:
        int sizeOfHand;
        vector<Card*> cardsInHand;
};

//Class Card declaration
class Card {
    public:
        Card();
        Card(string type);
        Card(const Card&);
        ~Card();
        void play(int, Hand*, Deck*, OrderList*);
        friend ostream & operator << (ostream&, const Card&);
        string getType();
    private:
        Order *order;
        string cardType;
 };

 #endif
