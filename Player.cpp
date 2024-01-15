#include "Player.h"

/* Constructor that creates a Player with a given name. */
Player::Player(string& n) {
	players_name = n;
	players_hand = new Hand();
}

/* Constructor which accepts an istream and reconstruct the Player from file. */
Player::Player(istream& in, const  CardFactory *set) {
	players_hand = new Hand(in, set);
}

/* Get the name of the player.*/
string Player::getName() {
	return players_name;
}

/* Get the number of coins currently held by the player. */
int Player::getNumCoins() {
	return numCoins;
}

/* Add a number of coins */
Player& Player::operator+=(int n) {
	numCoins += n;
	return *this;
}

/* Returns either 2 or 3*/
int Player::getMaxNumChains() {
	return numChains;
}

/* Returns the number of non-zero chains. */
int Player::getNumChains() {
	if (currChains.empty()) {
		return 0;
	}
	else {
		return sizeof(currChains);
	}
}

/* Returns the chain at position i.*/
Chain<Card*>& Player::operator[](int i) {
	return currChains.at(i);
}

/* Adds a empty third chain to the player for three coins. The function reduces the coin count for the player by two.
   If the player does not have enough coins then an exception NotEnoughCoins is thrown.*/
void  Player::buyThirdChain() {
	if (numChains < 3) {
		if (numCoins < 3) {
			throw NotEnoughCoins("You currently don't have enough coins to buy a third chain.");
		}
		else {
			numCoins = numCoins - 3;
			numChains++;
		}
		cout << "You currently already have 3 chains and 3 is the Maximum number of chains a player can have." << endl;
	}
}

/* Prints the top card of the player's hand (with arguement false) or all player's hand (with argument true) to the supplied ostream.*/
void Player::printHand(ostream& out, bool ntop) {
	if (ntop) {
		print(out, *players_hand);
	}
	else {
		cout << "Player's top card:";
		Card* tmp = players_hand->top();
		tmp->print(out);
	}
}
Player::~Player() {
	delete players_hand;
}

ostream& operator<<(ostream& out, Player& player) {
	vector<Chain<Card*>>chain = player.getChain();
	int nChain = player.getNumChains();
	int index = 0;
	
	out << player.getName()
		<< "\t"
		<< player.getNumCoins()
		<< ((player.getNumCoins() > 2) ? "coins\n" : "coin\n");
	while (index < nChain) {
		//Chain card Name e.g Red
		out << chain[index].getChain()[0]->getName()
			<< "\t";
		//Prints the card based on how many there is in the chain e.g R R R R.
		for (int x = 0; x < int(chain[index].getChain().size());x++) {
			chain[index].getChain()[0]->print(out);
			out << " ";
		}
		//out << (out, chain[index]);
		index++;
	}
	return out;
}
