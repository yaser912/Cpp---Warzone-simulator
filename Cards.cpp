#include "Cards.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//************************                ************************   
//************************      CARDS     ************************ 
//setter
void Card::setName(std::string set_name) {
	Card::typeOfCard = set_name;
}
//getter
std::string Card::getname() {
	return typeOfCard;
}
//default constructor
Card::Card() {
	typeOfCard = "no type given";
}

//copy constructor
Card::Card(const Card& card) {

	typeOfCard = card.typeOfCard;
}
//overloaded output stream operator
ostream& operator<< (ostream& out, Card& c)
{
	out << c.getname();
	return out;
}
//Overloaded comparison stream operator " == "
bool operator ==(Card a, Card b) {
	return (a.getname() == b.getname());
}
//Overloaded assignment operator
void Card::operator =(const Card right) {

	typeOfCard = right.typeOfCard;
}


//Play method
void Card::play(Card& card_to_play, vector<string>& orderList, vector<Card>* handList, vector<Card>* deck) {
	string current_card;
	string bomb = "bomb";
	string reinforcement = "reinforcement";
	string blockade = "blockade";
	string airlift = "airlift";
	string diplomacy = "diplomacy";


	current_card = card_to_play.getname();

	if ((current_card.compare(bomb)) == 0) {
		string bombOrder = "Instructions to follow if we play the BOMB card.";
		orderList.push_back(bombOrder);
	}

	if ((current_card.compare(reinforcement)) == 0) {
		string reinforcementOrder = "Instructions to follow if we play the REINFORCEMENT card.";
		orderList.push_back(reinforcementOrder);
	}

	if ((current_card.compare(blockade)) == 0) {
		string blockadeOrder = "Instructions to follow if we play the BLOCKADE card.";
		orderList.push_back(blockadeOrder);
	}

	if ((current_card.compare(airlift)) == 0) {
		string airliftOrder = "Instructions to follow if we play the AIRLIFT card.";
		orderList.push_back(airliftOrder);
	}

	if ((current_card.compare(diplomacy)) == 0) {
		string diplomacyOrder = "Instructions to follow if we play the DIPLOMACY card.";
		orderList.push_back(diplomacyOrder);
	}

	cout << "\nYou are now playing the card:  " << current_card << endl;
	cout << "\n The instructions for " << current_card << " have been sent to the order list." << endl;
	deck->push_back(card_to_play);
	handList->erase(std::remove(handList->begin(), handList->end(), card_to_play), handList->end());

}


//************************               ************************   
//************************      DECK     ************************ 

//Default Constructor
Deck::Deck() {

	deck = new std::vector<Card>;
	Card bomb;
	bomb.setName("bomb");

	Card reinforcement;
	reinforcement.setName("reinforcement");

	Card blockade;
	blockade.setName("blockade");

	Card airlift;
	airlift.setName("airlift");

	Card diplomacy;
	diplomacy.setName("diplomacy");

	deck->push_back(bomb);
	deck->push_back(reinforcement);
	deck->push_back(blockade);
	deck->push_back(airlift);
	deck->push_back(diplomacy);
}


//Copy Constructor
Deck::Deck(const Deck& d) {

	deck = new std::vector<Card>();

	for (int i = 0; i < d.deck->size(); i++)
	{
		deck->push_back(d.deck->at(i));
	}
};

//Draw method
Deck::Card Deck::draw(Deck* deck, int randomNumber) {

	Card card_drawn;
	card_drawn = deck->deck->at(randomNumber);
	deck->deck->erase(deck->deck->begin() + randomNumber); // remove the card that was drawn from the deck.
	return card_drawn;


}
//Overloaded output stream operator
std::ostream& operator<<(ostream& out, const Deck& deck)
{

	int i;
	for (int i = 0; i < deck.deck->size(); i++) {
		out << "The cards in the deck are:  " << deck.deck->at(i).getname() << "\n";
	}
	return out;
}

//Overloaded assignment operator
void Deck::operator =(const Deck d) {

	deck = d.deck;

}


//************************                ************************   
//************************      HAND     ************************ 
//Default constructor
Hand::Hand() {

	hand = new std::vector<Card>;

}
//Copy constructor
Hand::Hand(const Hand& h) {

	hand = new std::vector<Card>();

	for (int i = 0; i < h.hand->size(); i++)
	{
		hand->push_back(h.hand->at(i));
	}
}

//Overloaded output stream operator
ostream& operator<< (ostream& out, Hand& h)
{

	out << h.getname();
	return out;
}
//Overloded assignment operator
void Hand::operator =(const Hand right) {

	hand = right.hand;
}

//************************						     ************************   
//************************      HELPER FUNCTIONS     ************************ 


//Compare 2 strings by making them both lower case

int compare_strings(string s1, string s2) {
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return 1; //Same
	return 0; //Different
}

