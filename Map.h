#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <list>
using namespace std;




class Territory //country
{
public:

	Territory();
	Territory(int terrID, string terrName, int terrContinentID, int terrArmies);
	Territory(int terrID, string terrName, int terrContinentID, int terrArmies, int playerID);
	Territory(const Territory& territoryObject);
	Territory& operator =(const Territory& rightSide);
	friend ostream& operator<< (ostream& os, const Territory& territory);

	void addAdjTerr(Territory* territory);
	int getTerrID();
	int getTerrContinentID();
	void addArmies(int numOfArmies);
	int getTerrArmies();
	void setPlayerID(int nPlayerID);
	int getPlayerID();
	void setVisited(bool terrVisited);
	bool getVisited();
	string getTerrName();
	vector<Territory*> getAdjTerr();
	~Territory();

private:
	int* ID;
	string* name;
	int* continentID;
	int* PID;
	int* armies;
	vector<Territory*>* adjTerr;
	bool* visited;

};

class Continent
{
public:
	Continent(int continentID, string continentName, int continentArmies);
	Continent(const Continent& continentObject);
	Continent& operator =(const Continent& rightSide);
	friend ostream& operator<< (ostream& os, const Continent& continent);

	int getContinentID();
	int getContinentArmies();
	int getBonus();
	void setBonus(int bonusValue);
	void addTerritory(Territory* territory);
	vector<Territory*>* getTerritory();
	string getContinentName();
	~Continent();

private:
	int* ID;
	int* armies;
	int bonus;
	string* name;
	vector<Territory*>* territories;

};


class Map
{
public:
	Map(int numOfTerritory);
	Map(const Map& mapObject);
	Map& operator =(const Map& rightSide);
	friend ostream& operator<< (ostream& os, const Map& map);

	int getNumOfTerritory();
	void addContinent(Continent* continent);
	void validate1();
	void validate2();
	void validate3();
	void rezero();
	void show1();
	vector<Continent*>* getContinents();
	~Map();

private:
	int* num;
	vector<Continent*>* continents;
	vector<Territory*>* territories;

};

