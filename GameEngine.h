#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
using namespace std;

//TASHFIA ADDED
void selectMap(); //To select a Map
int numOfPlayers(); //To select the number of players
void createDeck();
bool StartPhaseObserver();

//YASER ADDED
void startupPhase(int numberOfPlayers, Map* map);
void showPart2(int numberOfPlayers);


