#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

#include "Player.h"
#include "Map.h"

using namespace std;

class Player {
public:
	int getPlayerNumber();
	void removeTerritory(Territory* toRemove);
	Player(string playerName);
	int reinforcementPool;
	void addReinforcements(int toAdd);
	int getReinforcementPool();
};


class Territory{
public:
	
	Player* getOwner();
	void setOwner(Player* player);
	bool   setArmies(int);
	int    getArmies();
	string getTerrName();
	bool isAdjacent(int id);
	int index;
	bool addTroops(int n);
	bool removeTroops(int n);
	int numberOfArmies;
	string name;
	Territory(int terrID, string terrName, int terrContinentID, int terrArmies, int playerID);
};

class Map {

public:
	void addAdjTerritory(Territory* t1, Territory* t2);
	string name;
};

//////////////////////////////////////////////////////// ORDER ////////////////////////////////////////////////////////////
class Order
{
public:
	Player* player;

	//Default Constructor
	Order();

	//Copy constructor
	Order(const Order& toCopy);

	//Assignment operator
	Order& operator = (const Order& rightSide);

	//Validates an order
	virtual bool validate() = 0;

	//Executes an order
	virtual void execute() = 0;

	// declared as virtual so appropriate subclass destructor can be called.
	virtual ~Order();

	// Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const Order& order);

	// constructor with player
	Order(Player* player);

	//constructor with player and territory 
	Order(Player* player, Territory* territory);

	// this method will check if 2 orders given by same player, if so then order won't be executed
	bool operator==(const Order& comparison);

	//getters
	Player* getPlayer();
	Territory* getTarget();

	//setters
	void setPlayer(Player* player);
	void setTarget(Territory* target);

protected:
	bool executed = false;

private:
	//Player* player;
	Territory* next;

};

///////////////////////////////////////////////////////// DEPLOY ////////////////////////////////////////////////////

// Deploy the armies to one of the player's territories 
class Deploy : public Order
{

private:
	Territory* territory;
	int numOfArmies;

public:
	// Default constructor
	Deploy();

	// Copy constructor 
	Deploy(const Deploy& toCopy);

	//Assignment operator
	Deploy& operator = (const Deploy& rightSide);

	//Overloaded constructor
	Deploy(Player* player, Territory* territory, int numOfArmies);

	//Validates a deploy order
	bool validate();

	//Executes a deploy order
	void execute();

	// declared as virtual so appropriate subclass destructor can be called.
	~Deploy();

	// Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const Deploy& deploy);

	//getter
	int getNumOfArmies();

	//setter
	bool setNumOfArmies(int numberOfArmies);

	// returns string indicating type of Order
	string getType();

};


////////////////////////////////////////////////////// ADVANCE /////////////////////////////////////////////////////

//Advance armies from current territory to the next territory
class Advance : public Order
{
private:
	Territory* current;
	int numOfArmies;

public:

	Territory* next;

	//Default constructor
	Advance();

	//overloaded constructor
	Advance(Player* player, Territory* current, Territory* next, int numOfArmies);

	// copy constructor
	Advance(const Advance& toCopy);

	// declared as virtual so appropriate subclass destructor can be called.
	~Advance();

	//Assignment operator
	Advance& operator = (const Advance& rightSide);

	// validates advance order
	virtual bool validate();

	// Validates execute order
	virtual void execute();

	// Overloaded stream insertion operator
	friend ostream& operator<<(std::ostream& out, const Advance& advance);

	// returns string indicating type of Order
	string getType();

	// getters
	Territory* getCurrent();
	int getNumberOfArmies();

	// setters
	bool setCurrent(Territory* current);
	bool setNumberOfArmies(int numberOfArmies);

};

////////////////////////////////////////////////// BOMB //////////////////////////////////////////////
//Bomb order, shrinking target territory forces by half
class Bomb : public Order
{
private:
	Territory* current;
	Territory* next;

public:
	Bomb();

	//Overloaded constructor
	Bomb(Player* player, Territory* current, Territory* next);

	//Copy constructor
	Bomb(const Bomb& bomb);

	// declared as virtual so appropriate subclass destructor can be called.
	~Bomb();

	Bomb& operator = (const Bomb& bomb);

	//Validates a bomb order
	virtual bool validate();

	//Executes a bomb order
	virtual void execute();

	// returns string indicating type of Order
	string getType();

	// Overloaded stream insertion operator
	friend ostream& operator<<(std::ostream& out, const Bomb& bomb);
};

/////////////////////////////////////////////////// BLOCKADE ////////////////////////////////////////////////

//Blockade order, increasing target territory armies by times 3 and makes it neutral 
class Blockade : public Order
{
private:
	Territory* next;
public:

	// Default constructor
	Blockade();

	//Overloaded constructor
	Blockade(Player* player, Territory* next);

	//Copy constructor
	Blockade(const Blockade& toCopy);

	// declared as virtual so appropriate subclass destructor can be called.
	~Blockade();

	//Assignment operator
	Blockade& operator = (const Blockade& rightSide);

	//Validates a blockade order
	virtual bool validate();

	//Executes a blockade order
	virtual void execute();

	// returns string indicating type of Order
	string getType();

	// Overloaded stream insertion operator
	friend ostream& operator<<(std::ostream& out, const Blockade& blockade);
};

////////////////////////////////////////////// AIRLIFT ///////////////////////////////////////////////////////////

//Airlift armies to any target territories
class Airlift : public Order
{
private:
	Territory* current;
	Territory* next;
	int numOfArmies;

public:
	// default constructor
	Airlift();

	//Overloaded constructor
	Airlift(Player* player, Territory* current, Territory* next, int numOfArmies);

	//Copy constructor
	Airlift(const Airlift& toCopy);

	// declared as virtual so appropriate subclass destructor can be called.
	~Airlift();

	//Assignment operator
	Airlift& operator = (const Airlift& rightSide);

	//Validates an airlift order
	virtual bool validate();

	//Executes an airlift order
	virtual void execute();

	// Overloaded stream insertion operator
	friend ostream& operator<<(std::ostream& out, const Airlift& airlift);

	// returns string indicating type of Order
	string getType(); 

	// getters
	Territory* getCurrent();
	int getNumberOfArmies();

	// setters
	bool setCurrent(Territory* current);
	bool setNumberOfArmies(int numberOfArmies);
};

///////////////////////////////////////////////////// NEGOTIATE ///////////////////////////////////////////////////////////

//Negotiate order that does nothing during current turn
class Negotiate : public Order
{
private:
	Player* opponent;
public:
	// default constructor
	Negotiate();

	//Overloaded constructor
	Negotiate(Player* current, Player* opponent);

	//Copy constructor
	Negotiate(const Negotiate& toCopy);

	// declared as virtual so appropriate subclass destructor can be called.
	~Negotiate();

	//Assignment operator
	Negotiate& operator = (const Negotiate& rightSide);

	//Validates a negotiate order
	virtual bool validate();

	//Executes a negotiate order
	virtual void execute();

	// returns string indicating type of Order
	string getType();

	// Overloaded stream insertion operator
	friend ostream& operator<<(std::ostream& out, const Negotiate& negotiate);

	//getter
	Player* getPlayer_opponent();
};

///////////////////////////////////////////////// ORDER LIST //////////////////////////////////////////////////////////////

//OrderList class, implementing a vector
class OrdersList
{
private:
	vector<Order*> ordersList;

public:
	//Default Constructor
	OrdersList();

	// copy constructor
	OrdersList(const OrdersList& toCopy);

	//Destructor that clears the adjacent order in the vector
	~OrdersList();

	//Assignment operator
	OrdersList& operator=(const OrdersList& rightSide);

	//Move order up or down in the list
	void move(int oldPosition, int newPosition);

	//Add order to list (so the order is made at the end of the list)
	void add(Order* order);

	//Remove order to list
	void remove(int index);

	friend ostream& operator <<(std::ostream& out, const OrdersList& oL);

	//getter
	vector<Order*> getOrdersList();

private:
	vector<Order*> ordersList;
};
