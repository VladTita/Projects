#include "CardsDriver.h"
#include "Cards.h"
#include "Orders.h"

#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

void testCards()
{
    int dNum = 5;
    int hNum = 2;
    Deck *newDeck = new Deck(dNum);
    Hand *newHand = new Hand(hNum);
    OrderList *ol = new OrderList();

    cout << *newDeck << '\n';
    cout << *newHand << '\n';
    cout << "----------------------\n";
    for (int i = 0; i < hNum; i++)
        (*newDeck).draw(newHand);

    cout << *newDeck << '\n';
    cout << *newHand << '\n';
    cout << "----------------------\n";

    for (int i = 0; i < hNum; i++)
        newHand->getCard(0)->play(0, newHand, newDeck, ol);

    cout << *newDeck << '\n';
    cout << *newHand << '\n';
}