#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "Map.h"
class Player;
using namespace std;

#ifndef GAME_OBS
#define GAME_OBS
//three phases
enum Phase {
	Reinforcement=0,
	Issuing_Orders=1,
	Orders_Execution=2,
	None
};

//Abstract Observer class
class Observer {
public:
	~Observer() {}; ////deconstructor
	virtual void update() = 0; 
protected:
	Observer(){};
};

//Subject class
class Subject{

public:
	Subject();
	~Subject();////deconstructor
	virtual void attach(Observer* o); //attch subject to observer
	virtual void detach(Observer* o);//detach subject to observer
	virtual void notify(); //notify observer
	Subject(const Subject& toCopy);//Copy constructor
	Subject & operator= (const Subject& other);//Assignment operator
	friend ostream& operator<<(std::ostream& stream, const Subject& o);//stream insertion operator

private:
	std::list<Observer*>* observers;
	//concreat observers lists
};

//Phase_Observer class 
class Phase_Observer :public Observer {
public:
	Phase_Observer();
	~Phase_Observer();//deconstructor
	void update(); //update the information
	void addPlayer(Player* Player); //add the player
	Phase_Observer(const Phase_Observer& toCopy);//Copy constructor
	Phase_Observer& operator= (const Phase_Observer& other);//Assignment operator
	friend ostream& operator<<(std::ostream& stream, const Phase_Observer& o);//stream insertion operator
private:
	Phase updated = Phase::None;
	std::vector<Player*> players;

	
};

//Game_Statistics_Observer class
class Game_Statistics_Observer :public Observer {
public:
	Game_Statistics_Observer(int terrNumber);
	~Game_Statistics_Observer();////deconstructor
	void update(); //update the information
	void addPlayer(Player* Player); //add the player
	void removePlayer(Player* player); //delete the player
	void boot(); // turn on observers
	Game_Statistics_Observer(const Game_Statistics_Observer& toCopy);//Copy constructor
	Game_Statistics_Observer & operator=(const Game_Statistics_Observer& other);//Assignment operator
	friend ostream& operator<<(std::ostream& stream, const Game_Statistics_Observer& o);//stream insertion operator
private:
	std::vector<Player*> players;
	int terrNumber;
	bool status = false; //default status is false, when using boot() turn on the observers
};
#endif