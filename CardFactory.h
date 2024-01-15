#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <fstream>

#include "Deck.h"
#include <time.h>

using namespace std;

/*
* The card factory serves as a factory for all the beancards.
* CardFactory will generate all cards, and so, we will explore the factory pattern.
* A factory ensures that there is only a single unit in the program that is responsible to create and delete cards. Other parts of the program will only use pointers to access the cards. 
* Note that means, we will delete the copy constructor and assignment operator in Card.
*/

class CardFactory {
	public:
		/* Returns a pointer to the only instance of CardFactory*/
		static CardFactory* getFactory(istream& in);
		/* Returns a deck with all 104 bean cards.*/
		Deck getDeck();
		/* Destory the cardFactory*/
		~CardFactory();
	private:
		CardFactory(istream& in);
		Deck* currentDeck = nullptr;
};
#endif
