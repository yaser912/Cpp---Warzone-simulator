#pragma once
#include <iostream>
#include <vector>

using namespace std;


//Card class
class Card {
public:
	std::vector<string>* orders;

	//default and copy constructor declarations
	Card();
	Card(const Card& card);
	//getters and setters
	string getname();

	void setName(std::string set_name);
	//overloaded assignment operator declaration
	void operator =(const Card right);
	//play method
	void play(Card& card_to_play, vector<string>& orderList, vector<Card>* handList, vector<Card>* deck);
private:
	string typeOfCard;
	//overloaded stream insertion operator
	friend ostream& operator << (ostream& out, Card& c);
	//overloaded equality operator
	friend bool operator ==(Card a, Card b);
};

//Deck class
class Deck : public Card {
public:
	std::vector<Card>* deck;
	//default and copy constructor
	Deck();
	Deck(const Deck& deck);
	//draw method declaration
	Card draw(Deck* deck, int randomNumber);
	//overloaded assignment operator
	void operator =(const Deck right);

private:
	//overloaded stream insertion operator
	friend ostream& operator << (ostream& out, Deck& d);
};

//Hand class
class Hand : public Deck {

public:
	std::vector<Card>* hand;
	//default and copy constructor
	Hand();
	Hand(const Hand& hand);
	//overloaded assignment operator
	void operator =(const Hand right);
private:
	//overloaded stream insertion operator
	friend ostream& operator << (ostream& out, Hand& h);

};
//helper function
int compare_strings(string s1, string s2);

