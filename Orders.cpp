#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h>
#include <sstream>

using namespace std;

////////////////////////////////////////////////// ORDER /////////////////////////////////////////////////////////

//Default Constructor for Order 
Order::Order()
{
	//player = nullptr;
	//target = nullptr;

}

//Copy constructor 
Order::Order(const Order& toCopy) 
{
	this->player = toCopy.player;
	this->next = toCopy.next;
}

// constructor with player
Order::Order(Player* p) //: player(p)
{
	this->player = p;
}

//constructor with player and target
Order::Order(Player* p, Territory* t) : player(p), next(t)
{
}

// virtual 
Order::~Order()
{
	this->player = NULL;
}

//Assignment operator for the Order base class
Order& Order::operator=(const Order& rightSide) {
	player = rightSide.player;
	next = rightSide.next;
	return *this;
}

//Acts as an equal operator that returns true if two orders are given by same player and therefore won't execute 
bool Order::operator==(const Order& comparison)
{
	return player == comparison.player && executed == comparison.executed;
}

//Get the player that executes a particular order
Player* Order::getPlayer()
{
	return player;
}

//Get the target that where the order has been or will be executed
Territory* Order::getTarget()
{
	return next;
}


//Set the player executing a particular order
void Order::setPlayer(Player* p)
{
	if (p != NULL)
	{
		player = p;
	}
}

//Set the target where the order has been or will be executed 
void Order::setTarget(Territory* t)
{
	if (next != NULL)
	{
		next = t;

	}
}

//Stream insertion operator for the base Order class
std::ostream& operator<<(std::ostream& out, const Order& order)
{
	return out << "An order is in the list";
}

///////////////////////////////////////////////////////////// DEPLOY ////////////////////////////////////////////

//Default constructor for the Deploy class
Deploy::Deploy(): Order()
{
	numOfArmies = 0; 
}

//Copy constructor for the Deploy class
Deploy::Deploy(const Deploy& deploy) :Order(deploy)
{
	this->territory = deploy.territory;
	this-> numOfArmies = deploy.numOfArmies;
}

Deploy::Deploy(Player* p, Territory* target, int numberOfArmies):Order(p, target)
{
	numOfArmies = numberOfArmies;
}

// Virtual
Deploy::~Deploy()
{
	this->territory = NULL;
}

// Assignment operator for the Deploy class
Deploy& Deploy::operator=(const Deploy& deploy)
{
	Order::operator=(deploy);
	territory = deploy.territory;
	numOfArmies = deploy.numOfArmies;
	return *this;
}

//validate method for the deploy order
bool Deploy::validate()
{
	if (territory->getOwner() == getPlayer())
	{
		cout << "Deploy order is valid." << endl;
		return true;
	}
	cout << "Deploy order is not valid." << endl;
	return false;
}

//execute method for the deploy order
void Deploy::execute()
{
	if (validate())
	{
		getTarget()->setArmies(getTarget()->getArmies() + getNumOfArmies());
		cout << "Deploying " << getNumOfArmies() << " armies to " << getTarget()->getTerrName() << endl;
	}
}

// get the number of armies
int Deploy::getNumOfArmies()
{
	return numOfArmies;
}

// set the number of armies
bool Deploy::setNumOfArmies(int number)
{
	numOfArmies = number;
	return true;
}

// returns string indicating type of Order
string Deploy::getType() 
{ 
	return "Deploy"; 
}

// Stream insertion operator for Deploy class order
ostream& operator << (std::ostream& o, const Deploy& deploy)
{
	return o << "A deploy order has been issued.";
}

//////////////////////////////////////////////////// ADVANCE //////////////////////////////////////////////////

//Default constructor 
Advance::Advance()
{
	current = nullptr;
	numOfArmies = 0;
}

// Parametrized constructor for the Advance class
Advance::Advance(Player* player, Territory* current, Territory* next, int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

//Copy constructor for the Advance class
Advance::Advance(const Advance& advance) : Order(advance)
{
	this->current = advance.current;
	this->next = advance.next;
}

//Assignment operator for the Advance class
Advance& Advance::operator=(const Advance& advance)
{
	Order::operator=(advance);
	current = advance.current;
	next = advance.next;
	numOfArmies = advance.numOfArmies;
	return *this;
}

Advance::~Advance()
{
	this->current = NULL;
	this->next = NULL;
}

//Validate method for Advance class, validating the currentand next territories are adjacent
bool Advance::validate()
{
	if (current->getOwner() == getPlayer() && current->isAdjacent(next->index))
	{
		cout << "Advance order is valid." << endl;
		return true;
	}
	cout << "Advance order is not valid." << endl;
	return false;
}


//Execute method if validate() returns true
void Advance::execute()
{
	if (validate())
	{
		cout << "Advance order executed." << endl;
		executed = true;

		if (next->getOwner() == getPlayer()) // if defending
		{
			int armiesToMove = std::min((int)numOfArmies, current->numberOfArmies);
			if (armiesToMove != numOfArmies)
				numOfArmies = armiesToMove;
			current->removeTroops(numOfArmies);
			next->addTroops(numOfArmies);

			cout << "ADVANCE ORDER: Player " << player->getPlayerNumber() << " advancing..\n" << "Advancing " << numOfArmies << " armies from " << current->name << " to " << next->name << ".\n";
		}
		else // if attacking
		{
			while (next->numberOfArmies > 0 || current->numberOfArmies > 0)
			{
				srand(time(NULL));

				if (rand() % 10 < 6)
					next->removeTroops(1);

				else if (rand() % 10 < 7)
					current->removeTroops(1);
				numOfArmies--;
			}

			if (next->numberOfArmies == 0) // if next owner loses
			{
				next->getOwner()->removeTerritory(next); // remove Territory from losing player
				next->setOwner(player); // change owner to winner
				next->addTroops(numOfArmies);
				cout << "ADVANCE ORDER: Player " << player->getPlayerNumber() << " won.\n" << " Won " << next->name << " territory, " << " and won " << numOfArmies << " armies." << endl;
			}

			if (current->numberOfArmies == 0) //if player loses
			{
				cout << "ADVANCE ORDER: Attacking player " << player->getPlayerNumber() << " lost; has 0 armies on " << current->name << " territory. Attack ended." << endl;
			}
		}

	}
}
// get current territory
Territory* Advance::getCurrent()
{
	return current;
}

// get the number of armies
int Advance::getNumberOfArmies()
{
	return numOfArmies;
}

// set the current territory
bool Advance::setCurrent(Territory* source)
{
	if (source != NULL)
	{
		current = source;
		return true;
	}

	return false;
}

// set number of armies 
bool Advance::setNumberOfArmies(int numberOfArmies)
{
	numOfArmies = numberOfArmies;
	return true;
}

string Advance::getType() 
{
	return "Advance"; 
}

//Stream insertion operator for Advance class order
ostream& operator << (std::ostream& o, const Advance& advance)
{
	return o << "An advanced order has been issued.";
}

///////////////////////////////////////////////////////// BOMB /////////////////////////////////////////////////////////

// Default constructor
Bomb::Bomb()
{

}

//Parametrized constructor for the Bomb class
Bomb::Bomb(Player* player, Territory* current, Territory* next) : Order(player)
{
	this->current = current;
	this->next = next;
}


//Copy constructor for the Bomb class
Bomb::Bomb(const Bomb& bomb) : Order(bomb)
{
	this->current = bomb.current;
	this->next = bomb.next;
}

Bomb::~Bomb()
{
	this->current = NULL;
	this->next = NULL;
}

//Assignment operator for the Bomb class
Bomb& Bomb::operator=(const Bomb& bomb)
{
	Order::operator=(bomb);
	current = bomb.current;
	next = bomb.next;
	return *this;
}

//Validate method for Bomb class, validating the current and next territories are adjacent
bool Bomb::validate()
{
	if (current->isAdjacent(next->index) && current->getOwner() == getPlayer() && next->getOwner() != getPlayer())
	{
		cout << "Bomb order is valid." << endl;
		return true;
	}
	cout << "Bomb order is not valid." << endl;
	return false;
}

/*Execute method if validate() returns true
*/
void Bomb::execute()
{
	if (validate())
	{
		cout << "Bomb order executed." << endl;
		executed = true;

		int numDestroyed = (int)(next->numberOfArmies / 2.0);

		next->removeTroops(numDestroyed);

		cout << "BOMB ORDER: Bombing " << next->name << " territory, reducing half of its forces.\n";
	}

	cout << "Bomb order is invalid: execute() method fails to execute." << endl;
}

string Bomb::getType() 
{ 
	return "Bomb"; 
}

//Stream insertion operator for Bomb class order
ostream& operator << (std::ostream& o, const Bomb& bomb)
{
	return o << "A bomb order has been issued";
}

///////////////////////////////////////////////////////////// BLOCKADE ///////////////////////////////////////////////////////

//Default constructor for the Blockade class
Blockade::Blockade() : Order()
{

}

//Parametrized constructor for the Blockade class
Blockade::Blockade(Player* player, Territory* next) : Order(player)
{
	this->next = next;
}

//Copy constructor for the Blockade class
Blockade::Blockade(const Blockade& blockade) : Order(blockade)
{
	this->next = blockade.next;
}

Blockade::~Blockade()
{
	this->next = NULL;
}

//Assignment operator for the Blockade class
Blockade& Blockade::operator=(const Blockade& blockade)
{
	Order::operator=(blockade);
	next = blockade.next;
	return *this;
}

//Validate method for Blockade class, validating the owner of the target territory is myself
bool Blockade::validate()
{
	if (next->getOwner() == getPlayer())
	{
		cout << "Blockade order validated." << endl;
		return true;
	}
	cout << "Blockade order is not valid." << endl;
	return false;
}

//Execute method if validate() returns true
void Blockade::execute()
{
	if (validate())
	{
		cout << "Blockade order executed." << endl;
		executed = true;

		next->addTroops(next->numberOfArmies * 2);

		next->setOwner(player); //neutral player //TODO: Come back to this when neutral player implemented

		cout << "BLOCKADE ORDER: Blockading " << next->name << " territory, doubling its forces, making it neutral.\n";
	}

	cout << "Blockade order is invalid: execute() method fails to execute." << endl;
}

string Blockade::getType() 
{ 
	return "Blockade"; 
}

//Stream insertion operator for Blockade class order
ostream& operator << (std::ostream& o, const Blockade& b)
{
	return o << "A blockade order has been issued";
}

////////////////////////////////////////////////// AIRLIFT ////////////////////////////////////////////////////////////

//Default constructor for the Airlift class
Airlift::Airlift() : Order()
{
	next = nullptr;
	numOfArmies = 0;
}

//Parametrized constructor for the Airlift class
Airlift::Airlift(Player* player, Territory* current, Territory* next, int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

//Copy constructor for the Airlift class
Airlift::Airlift(const Airlift& airlift) : Order(airlift)
{
	this->current = airlift.current;
	this->next = airlift.next;
}

Airlift::~Airlift()
{
	this->current = NULL;
	this->next = NULL;
}

//Assignment operator for the Airlift class
Airlift& Airlift::operator=(const Airlift& airlift)
{
	Order::operator=(airlift);
	current = airlift.current;
	next = airlift.next;
	return *this;
}

//Validate method for Airlift class, validating the owner of the target territory is myself, as well as numOfArmies is positive
bool Airlift::validate()
{
	if (current->getOwner() == getPlayer())
	{
		cout << "Airlift order validated." << endl;
		return true;
	}
	cout << "Airlift order is not valid." << endl;
	return false;
}

/*Execute method if validate() returns true
*/
void Airlift::execute()
{
	if (validate())
	{
		cout << "Airlift order executed." << endl;
		executed = true;

		if (next->getOwner() == getPlayer())
		{
			int armiesToMove = std::min((int)numOfArmies, current->numberOfArmies);
			if (armiesToMove != numOfArmies)
				numOfArmies = armiesToMove;
			current->removeTroops(numOfArmies);
			next->addTroops(numOfArmies);

			cout << "AIRLIFT ORDER: Player " << player->getPlayerNumber() << " airlifting..\n" << "Airlifting " << numOfArmies << " armies from " << current->name << " to " << next->name << ".\n";
		}
		else
		{
			while (next->numberOfArmies > 0 || current->numberOfArmies > 0)
			{
				srand(time(NULL));

				if (rand() % 10 < 6)
					next->removeTroops(1);

				else if (rand() % 10 < 7)
					current->removeTroops(1);
				numOfArmies--;
			}

			if (next->numberOfArmies == 0)
			{
				next->getOwner()->removeTerritory(next); // remove Territory from losing player
				next->setOwner(player);
				next->addTroops(numOfArmies);

				cout << "AIRLIFT ORDER: Player" << player->getPlayerNumber() << " won.\n" << " Won " << next->name << " territory, " << " and won " << numOfArmies << " armies." << endl;
			}

			if (current->numberOfArmies == 0) //if player loses
			{
				cout << "AIRLIFT ORDER: Attacking player " << player->getPlayerNumber() << " lost; has 0 armies on " << current->name << " territory. Attack ended." << endl;
			}
		}
	}
	cout << "Airlift order invalid: execute() method fails to execute." << endl;
}

string Airlift::getType() 
{ 
	return "Airlift"; 
}

Territory* Airlift::getCurrent()
{
	return current;
}
int Airlift::getNumberOfArmies()
{
	return numOfArmies;
}
bool Airlift::setCurrent(Territory* source)
{
	if (source != NULL)
	{
		current = source;
		return true;
	}

	return false;
}

bool Airlift::setNumberOfArmies(int numberOfArmies)
{
	numOfArmies;
	return true;
}

//Stream insertion operator for Airlift class order
ostream& operator << (std::ostream& o, const Airlift& airlift)
{
	return o << "An airlift order has been issued.";
}

////////////////////////////////////////////////////// NEGOTIATE ////////////////////////////////////////////////////////

//Default constructor for the Negotiate class
Negotiate::Negotiate() : Order()
{
	opponent = nullptr;
}

//Parametrized constructor for the Negotiate class
Negotiate::Negotiate(Player* current, Player* opponent) : Order(current)
{
	this->opponent = opponent;
}

//Copy constructor for the Negotiate class
Negotiate::Negotiate(const Negotiate& negotiate) : Order(negotiate)
{
	this->opponent = negotiate.opponent;
}

Negotiate::~Negotiate()
{
	this->opponent = NULL;
}

//Assignment operator for the Negotiate class
Negotiate& Negotiate::operator=(const Negotiate& negotiate)
{
	Order::operator=(negotiate);
	this->opponent = negotiate.opponent;
	return *this;
}

//Validate method for Negotiate class, validating that the enemy target territory is not one of my territories
bool Negotiate::validate()
{
	if (getPlayer() != opponent)
	{
		cout << "Negotiate order validated." << endl;
		return true;
	}
	cout << "Negotiate order is not valid." << endl;
	return false;
}

//Execute method if validate() returns true
void Negotiate::execute()
{
	if (validate())
	{
		cout << "Negotiate order executed." << endl;
		executed = true;

		cout << "NEGOTIATE ORDER: Negotiating.. No attack is being performed this turn. (do nothing)\n";
	}

	cout << "Negotiate order is invalid: execute() method fails to execute." << endl;
}

string Negotiate::getType() 
{ 
	return "Negotiate"; 
}

//Stream insertion operator for Negotiate class order
ostream& operator << (std::ostream& o, const Negotiate& negotiate)
{
	return o << "A negotiate order has been issued.";
}

Player* Negotiate::getPlayer_opponent()
{
	return opponent;
}

////////////////////////////////////////////////////////////// ORDER LIST /////////////////////////////////////////////////////

//Default constructor for the OrdersList class
OrdersList::OrdersList()
{
	// create vector of Order which is empty
	vector<Order*> o;
	this->ordersList = o;
}

// Create a new vector of the Orders in this OrdersList and return it
vector<Order*> OrdersList::getOrdersList()
{
	vector<Order*> o;
	for (int i = 0; i < ordersList.size(); i++)
	{
		o.push_back(ordersList.at(i));
	}
	return o;
}

//Copy constructor for the OrdersList class
OrdersList::OrdersList(const OrdersList& oList)
{
	ordersList = oList.ordersList;
}

//Assignment operator for the OrdersList class
OrdersList& OrdersList::operator=(const OrdersList& oList)
{
	ordersList = oList.ordersList;
	return *this;
}

//Add method, adding an order to the OrdersList
void OrdersList::add(Order* order)
{
	ordersList.push_back(order);
}

//Remove method, removing an order from the OrdersList
void OrdersList::remove(int index)
{
	//if position out of bound, cannot remove
	if (index < 0 || index >= ordersList.size())
		return;

	ordersList.erase(ordersList.begin() + index);
}

//Move method, moving an order from a position to another position in the OrdersList
void OrdersList::move(int oldPosition, int newPosition)
{
	//if position out of bound, cannot move
	if (oldPosition < 0 || oldPosition >= ordersList.size())
		return;

	int newOrderIndex = min(max(newPosition, 0), (int)ordersList.size());

	Order* toMove = ordersList[oldPosition];
	ordersList.erase(ordersList.begin() + oldPosition);
	ordersList.insert(ordersList.begin() + newOrderIndex, toMove);
}

// Destructor. Deletes pointer of each Order contained in the OrdersList vector, and the OrdersList pointer itself.
OrdersList::~OrdersList()
{
	for (int i = 0; i < this->ordersList.size(); i++)
	{
		delete this->ordersList[i];
		this->ordersList[i] = NULL;
	}
	// remove allocated memory locations
	this->ordersList.clear(); 
}

/*Stream insertion operator for OrdersList class
*/
ostream& operator <<(ostream& out, const OrdersList& oList)
{
	stringstream ss;

	ss << "Current list:" << endl;

	for (Order* order : oList.ordersList)
	{
		ss << "\t" << "An order of " << typeid(*order).name() << " is in the list,\n";
	}

	return out << ss.str() << "==============================" << endl;
}