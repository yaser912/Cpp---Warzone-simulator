#pragma once
#include "Map.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

Territory::Territory() {

}

Territory::Territory(int terrID, string terrName, int terrContinentID, int terrArmies)
{
	ID = new int(terrID);
	name = new string(terrName);
	continentID = new int(terrContinentID);
	PID = new int(0);
	armies = new int(terrArmies);
	visited = new bool(false);
	adjTerr = new vector<Territory*>();
}

Territory::Territory(int terrID, string terrName, int terrContinentID, int terrArmies, int playerID)
{
	ID = new int(terrID);
	name = new string(terrName);
	continentID = new int(terrContinentID);
	PID = new int(playerID);
	armies = new int(terrArmies);
	visited = new bool(false);
	adjTerr = new vector<Territory*>();
}

Territory::Territory(const Territory& territoryObject) {

	ID = territoryObject.ID;
	name = territoryObject.name;
	continentID = territoryObject.continentID;
	PID = territoryObject.PID;
	armies = territoryObject.armies;
}

Territory& ::Territory::operator =(const Territory& rightSide) {

	ID = rightSide.ID;
	name = rightSide.name;
	continentID = rightSide.continentID;
	PID = rightSide.PID;
	armies = rightSide.armies;

	return *this;
}

ostream& operator<<(ostream& os, const Territory& territory) {

	os << territory.ID;
	os << territory.name;
	os << territory.continentID;
	os << territory.PID;
	os << territory.armies;

	return os;
}

//add adjacent territory
void Territory::addAdjTerr(Territory* territory)
{
	adjTerr->push_back(territory);
}

int Territory::getTerrID()
{
	return *ID;
}

int Territory::getTerrContinentID()
{
	return *continentID;
}

void Territory::addArmies(int numOfArmies)
{
	*armies = *armies + numOfArmies;
}

int Territory::getTerrArmies()
{
	return *armies;
}

void Territory::setPlayerID(int nPlayerID)
{
	*PID = nPlayerID;
}

int Territory::getPlayerID()
{
	return *PID;
}

bool Territory::getVisited()
{
	return *visited;
}

void Territory::setVisited(bool terrVisited)
{
	*visited = terrVisited;
}

string Territory::getTerrName()
{
	return *name;
}

//get adjacent territory
vector<Territory*> Territory::getAdjTerr() {
	return *adjTerr;
}

Territory::~Territory() {
	delete ID;
	delete name;
	delete continentID;
	delete armies;
	delete PID;
	for (auto adj : *adjTerr)
		delete adj;
	delete adjTerr;
}

Continent::Continent(int continentID, string continentName, int continentArmies)
{
	ID = new int(continentID);
	name = new string(continentName);
	armies = new int(continentArmies);
	territories = new vector<Territory*>();
}

Continent::Continent(const Continent& continentObject)
{
	ID = continentObject.ID;
	name = continentObject.name;
	armies = continentObject.armies;
	territories = continentObject.territories;
}

Continent& ::Continent::operator =(const Continent& rightSide)
{
	ID = rightSide.ID;
	name = rightSide.name;
	armies = rightSide.armies;
	territories = rightSide.territories;

	return *this;
}

ostream& operator<< (ostream& os, const Continent& continent)
{
	os << continent.ID;
	os << continent.name;
	os << continent.armies;
	os << continent.territories;

	return os;
}

int Continent::getContinentID()
{
	return *ID;
}

int Continent::getContinentArmies()
{
	return *armies;
}

int Continent::getBonus() {

	return bonus;
}

void Continent::setBonus(int bonusValue) {

	bonus = bonusValue;
}
void Continent::addTerritory(Territory* territory)
{
	territories->push_back(territory);
}

vector<Territory*>* Continent::getTerritory()
{
	return territories;
}

string Continent::getContinentName()
{
	return *name;
}

Continent::~Continent()
{
	delete ID;
	delete name;
	delete armies;
	for (auto territory : *territories)
		delete territory;
	delete territories;
}



Map::Map(int numOfTerritory)
{
	num = new int(numOfTerritory);
	continents = new vector<Continent*>();
}

Map::Map(const Map& mapObject)
{
	num = mapObject.num;
	continents = mapObject.continents;
}

Map& ::Map::operator=(const Map& rightSide)
{
	num = rightSide.num;
	continents = rightSide.continents;

	return *this;
}

ostream& operator<<(ostream& os, const Map& map)
{
	os << map.num;
	os << map.continents;

	return os;
}

Map::~Map() {
	delete num;
	for (auto con : *continents)
		delete con;
	delete continents;
}

void Map::addContinent(Continent* continent) {
	continents->push_back(continent);
}

int Map::getNumOfTerritory()
{
	return *num;
}

vector<Continent*>* Map::getContinents() {
	return continents;
}

//reset visitedtimes
void Map::rezero()
{
	for (int a = 0; a <= continents->size() - 1; a++)
	{
		vector<Territory*> lists = *continents->at(a)->getTerritory();
		for (int b = 0; b <= lists.size() - 1; b++)
		{
			lists.at(b)->setVisited(false);
		}
	}

}

//validate the map is a connected graph
void Map::validate1()
{
	list<Territory*> BFSqueue;
	int visitedTimes = 0;
	Territory* startTerritory = continents->at(0)->getTerritory()->at(0);
	BFSqueue.push_back(startTerritory);
	visitedTimes = visitedTimes + 1;

	while (!BFSqueue.empty())
	{
		startTerritory = BFSqueue.front();
		startTerritory->setVisited(true);
		BFSqueue.pop_front();
		for (auto adj : startTerritory->getAdjTerr())
		{
			if (!(adj->getVisited()))
			{
				adj->setVisited(true);
				visitedTimes = visitedTimes + 1;
				BFSqueue.push_back(adj);
			}
		}
	}

	if (visitedTimes >= *num)
	{
		cout << "***The map is a connected graph!*** \n" << endl;
	}
	else
	{
		cout << "***The map is a NOT connected graph!*** \n " << endl;
	}
	rezero();
}

//validate subgraph is a connected graph
void Map::validate2()
{
	list<Territory*> BFSqueue;
	int visitedTimes = 0;
	Territory* startTerritory;

	for (auto continent : *continents) {
		visitedTimes = 0;
		BFSqueue.push_back(continent->getTerritory()->at(0));
		visitedTimes = visitedTimes + 1;
		while (!BFSqueue.empty())
		{
			startTerritory = BFSqueue.front();
			startTerritory->setVisited(true);
			BFSqueue.pop_front();
			for (auto adjTerr : startTerritory->getAdjTerr())
			{
				if (!adjTerr->getVisited() && (adjTerr->getTerrContinentID() == continent->getContinentID()))
				{
					adjTerr->setVisited(true);
					visitedTimes = visitedTimes + 1;
					BFSqueue.push_back(adjTerr);
				}
			}
		}

		if (visitedTimes >= continent->getTerritory()->size())
		{
			cout << "***Subraph for continent " << continent->getContinentName() << " is a connected graph!***" << endl << endl;
		}
		else
		{
			cout << "***Subraph for continent " << continent->getContinentName() << " is nNOT a connected graph***" << endl << endl;
		}
	}
	rezero();
}

//show continents
void Map::show1()
{
	for (auto continent : *continents)
	{
		cout << "***" << continent->getContinentName() << "***" << endl << endl;
	}

}
