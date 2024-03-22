#pragma once
#include "GameObservers.h"
#include <iostream>
#include <list>
#include <vector>
#include "Map.h"
#include "Player.h"

//Subject constructor
Subject::Subject() {
    static int i = 0;
    observers = new std::list<Observer*>();
    i++;
}
//Copy constructor
Subject::Subject(const Subject& toCopy) {
    observers = toCopy.observers;
}
//Assignment Operator
Subject& Subject::operator= (const Subject& other) {
    return *this;
}
//stream insertion operator
std::ostream& operator<<(std::ostream& stream, const Subject& o)
{
    stream << "Subject";
    return stream;
}
//deconstructor
Subject::~Subject() {
    delete observers;
}
//attch subject to observer
void Subject::attach(Observer* o) { 
    observers->emplace_back(o); 
}
//detach subject to observer
void Subject::detach(Observer* o) { 
    auto position = observers->begin();
    for (Observer* observer : *observers) {
        if (observer = o) {
            observers->erase(position);
            break;
        }
        position = position++;
    }
}
//notify the observer
void Subject::notify() {
    for (auto observer: *observers) {
        observer->update();
    }
}


//phase observer constructor
Phase_Observer::Phase_Observer() {

}
//deconstructor
Phase_Observer:: ~Phase_Observer() {

}
//copy constructor
Phase_Observer::Phase_Observer(const Phase_Observer& toCopy) {
    this->players = toCopy.players;
    this->updated = toCopy.updated;
}
//Assignment Operator
Phase_Observer& Phase_Observer::operator= (const Phase_Observer& other) {
    return *this;
}
//stream insertion operator
std::ostream& operator<<(std::ostream& stream, const Phase_Observer& o)
{
    stream << "Phase Observer";
    return stream;
}
//addplayer
void Phase_Observer::addPlayer(Player* player) {
    this->players.push_back(player);
}
//update
void Phase_Observer::update() {
 //from now, we only have reinforcement phase in game engine, in order to get player name and phase status, we make an empty getPhase() method in the player.h and player.cpp in order to fix it in the future
    Player* phaseNow = nullptr;
    //phasenow represent the current phase
    for (Player* player : players) {
        if (player->getPhase() != None) {
            phaseNow = player;
        }
    }
    //a switch is given to tell user which phase is current in
    if (phaseNow != nullptr) {
        
        switch (phaseNow->getPhase()) {
        
        case Phase::Reinforcement:
            std::cout << phaseNow->getPlayerName() + "Reinforcement phase" << std::endl;
            break;

        case Phase::Issuing_Orders:
            std::cout << phaseNow->getPlayerName() + "Issuing order phase" << std::endl;
            break;

        case Phase::Orders_Execution:
            std::cout << phaseNow->getPlayerName() + "Orders execution phase" << std::endl;
            break;

        }
    }
}

//game statistics observer constructor
Game_Statistics_Observer::Game_Statistics_Observer(int terrNumber) {
    this->terrNumber = terrNumber;
}
//copy constructor
Game_Statistics_Observer::Game_Statistics_Observer(const Game_Statistics_Observer& toCopy) {
    this->status = toCopy.status;
    this->terrNumber = toCopy.terrNumber;
    this->players = toCopy.players;
}
//assignment operator
Game_Statistics_Observer& Game_Statistics_Observer::operator=(const Game_Statistics_Observer& other)
{
    return *this;
}
//stream insertion operator
std::ostream& operator<<(std::ostream& stream, const Game_Statistics_Observer& o)
{
    stream << "Game Statistics Observer";
    return stream;
}
//deconstructor
Game_Statistics_Observer:: ~Game_Statistics_Observer() {

}
//boot method to turn on game statistics observer
void Game_Statistics_Observer::boot() {
    status = true; 
}

//void Game_Statistics_Observer::addPlayer(Player* player) {
//    this->players.push_back(player);
//}

//remove player can remove the player who have lost all the territories
void Game_Statistics_Observer::removePlayer(Player* player) {
    this->players.erase(players.begin());
}

//update and show information
void Game_Statistics_Observer::update() {

    for (Player* player : players) {
        //show what percentage of the world is currently being controlled by each player
        float value, percentage;
        value = (float)player->getCollectionOfTerritories().size() / (float)terrNumber;
        percentage = value * 100.0f;
        std::cout << player->getPlayerName() << "own occupied " << percentage << "% territories"<<std::endl;
    }
    //if the game statistics observer is on, it will calaculate the how many territories the player current have
    if (status) {
        
        for (int i = 0; i < players.size(); i++) {
            //if the player conquered all the territories, show player win the game
            if (players[i]->getCollectionOfTerritories().size() == terrNumber) {
                std::cout << "Congratulations! " << players[i]->getPlayerName() << " wins!!!" << std::endl;
            }
            //if the player lose all the territories, show player out and lose the game
            else if (players[i]->getCollectionOfTerritories().size() == 0) {
                std::cout << "Unfortunately " << players[i]->getPlayerName() << " lose all the territories, OUT :( " << std::endl;
                removePlayer(players[i]);
            }

        }
    }

}



