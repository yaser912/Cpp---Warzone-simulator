#include "Player.h"
#include <vector>
#include <iostream>;
using namespace std;


Cards::Cards() {

}

Cards::Cards(string type) {

	typeOfCard = type;
}

Cards::Cards(const Cards& cardObject) {

	typeOfCard = cardObject.typeOfCard;

}

Cards& ::Cards::operator =(const Cards& rightSide) {

	typeOfCard = rightSide.typeOfCard;

	return *this;
}

ostream& operator<<(ostream& os, const Cards& cards) {

	os << cards.typeOfCard;

	return os;
}

string Cards::getCardType() const {

	return typeOfCard;
}

Order::Order() {

}

Order::Order(string kindOfOrder) {

	typeOfOrder = kindOfOrder;
}

Order::Order(const Order& orderObject) {

	typeOfOrder = orderObject.typeOfOrder;

}

Order& ::Order::operator =(const Order& rightSide) {

	typeOfOrder = rightSide.typeOfOrder;

	return *this;
}

ostream& operator<<(ostream& os, const Order& order) {

	return os << order.typeOfOrder;
}

string Order::getTypeOfOrder() const {

	return typeOfOrder;
}

Player::Player() {

}

Player::Player(string playerName) {

	name = playerName;

}

Player::Player(const Player& playerObject) {

	name = playerObject.name;
	listOfOrders = playerObject.listOfOrders;
	collectionOfTerritories = playerObject.collectionOfTerritories;
	handOfCards = playerObject.handOfCards;
}

Player& Player::operator =(const Player& rightSide) {

	name = rightSide.name;
	listOfOrders = rightSide.listOfOrders;
	collectionOfTerritories = rightSide.collectionOfTerritories;
	handOfCards = rightSide.handOfCards;

	return *this;
}

ostream& operator<<(ostream& os, const Player& player) {

	os << player.name;

	for (int i = 0; i < player.collectionOfTerritories.size(); i++)

		os << player.collectionOfTerritories[i]->getTerrName();

	for (int j = 0; j < player.handOfCards.size(); j++)

		os << player.handOfCards[j].getCardType();

	for (int k = 0; k < player.listOfOrders.size(); k++)

		os << player.listOfOrders[k];

	return os;
}

vector<Territory*> Player::getCollectionOfTerritories() {

	return this->collectionOfTerritories;

}

vector<Territory*> Player::toAttack() {

	vector<Territory*> territoriesToAttack;

	territoriesToAttack.push_back(collectionOfTerritories[0]);
	territoriesToAttack.push_back(collectionOfTerritories[1]);

	return territoriesToAttack;
}

vector<Territory*> Player::toDefend() {

	vector<Territory*> territoriesToDefend;
	territoriesToDefend.push_back(collectionOfTerritories[0]);
	territoriesToDefend.push_back(collectionOfTerritories[1]);

	return territoriesToDefend;
}

string Player::getPlayerName() {

	return name;
}

int Player::getNumberOfArmies() {

	return renforcementPool;
}


void Player::setNumberOfArmies(int numOfArmies) {

	renforcementPool = numOfArmies;
}

void Player::issueOrder() {

	/*Order order1("deploy");
	Order order2("advance");

	listOfOrders.push_back(order1);
	listOfOrders.push_back(order2);
	cout << this->name << " has the folowing list of orders" <<endl;
	cout << "[" << endl;
	cout << listOfOrders[0].getTypeOfOrder() <<endl;
	cout << listOfOrders[1].getTypeOfOrder() <<endl;
	cout << "]" << endl;
	cout << endl;*/


}

void Player::showCards() {

	cout << this->getPlayerName() << " has the following hand of cards:\n" << "[" << endl;

	for (int i = 0; i < handOfCards.size(); i++) {

		Cards card = handOfCards[i];

		cout << card.getCardType() << endl;
	}

	cout << "]" << endl << endl;

}

void Player::addCard(string cardName) {

	Cards card(cardName);

	handOfCards.push_back(card);
}

void Player::addTerritory(Territory* territory) {

	collectionOfTerritories.push_back(territory);
}

void Player::showTerritories() {

	cout << this->getPlayerName() << " has the following list of territories" << endl;
	cout << "[" << endl;

	for (vector<Territory*>::iterator i = collectionOfTerritories.begin(); i != collectionOfTerritories.end(); ++i) {
		cout << (*i)->getTerrName() << endl;
	}

	cout << "]" << endl;
	cout << endl;
}

Phase getPhase() {
	//return the current phase
}


