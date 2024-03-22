#pragma once
#include "Map.h"
#include "GameObservers.h"
#include <vector>
#include <string>

#ifndef PLAYER
#define PLAYER
using namespace std;
//This class defines objects of Warzone Cards, where each card object is part of a finite deck of Warzone cards
class Cards {

private:
	string typeOfCard;

public:

	//Default constructor
	Cards();

	//Creates a card object with a certain type of Warzone card
	Cards(string type);

	//Copy constructor
	Cards(const Cards& cardObject);

	// Overloaded assignment operator
	Cards& operator =(const Cards& rightSide);

	//Overloaded stream insertion operator
	friend ostream& operator<< (ostream& os, const Cards& cards);

	//Gets the type of the Warzone card
	string getCardType() const;
};

//This class defines objects of Warzone player orders
class Order {

private:
	string typeOfOrder;

public:
	//Default constructor
	Order();

	//Creates an order object that has a kind of Warzone player order
	Order(string kindOfOrder);

	//Copy constructor
	Order(const Order& orderObject);

	// Overloaded assignment operator
	Order& operator =(const Order& rightSide);

	// Overloaded stream insertion operator
	friend ostream& operator<< (ostream& os, const Order& order);

	//Gets the type of Warzone player order
	string getTypeOfOrder() const;
};

// This class defines a player object which owns a collection of Territory objects, a hand of Card objects and a list of 
//order obejcts,that are to be created and executed in the current turn
class Player : public Subject {

private:
	string name;
	int renforcementPool;
	vector<Territory*> collectionOfTerritories;
	vector<Cards> handOfCards;
	vector<Order> listOfOrders;

public:
	// Default constructor
	Player();

	// Creates a Player object which contains a player's name
	Player(string playerName);

	//Copy constructor
	Player(const Player& playerObject);

	// Overloaded assignment operator
	Player& operator =(const Player& rightSide);

	// Overloaded stream insertion operator
	friend ostream& operator<< (ostream& os, const Player& player);

	// Returns the players collection of territories
	vector<Territory*> getCollectionOfTerritories();

	// Returns a list of pointers to territories that are to be attacked.
	vector<Territory*> toAttack();

	// Returns a list of pointers to territories that are to be defended.
	vector<Territory*> toDefend();

	// Gets the players name
	string getPlayerName();

	// Returns the players number of armies
	int getNumberOfArmies();

	// Sets the players number of armies
	void setNumberOfArmies(int numOfArmies);

	// Decides which orders will be placed in the player's orders list
	void issueOrder();

	// Shows the players cards
	void showCards();

	//Adds a card to a players hand
	void addCard(string cardName);

	//Adds a reference of a Territory object to the players collection of Territrory pointers
	void addTerritory(Territory* territory);

	//Show the players list of territories
	void showTerritories();

	Phase getPhase();

};
#endif