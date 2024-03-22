#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "map.h"
#include "GameEngine.cpp"
#include "GameObservers.h"

int main() {
    Map* map = new Map(3);
    Game_Statistics_Observer gameStatOb = Game_Statistics_Observer(map->getNumOfTerritory());
    Phase_Observer phaseOb = Phase_Observer();


    Player p1("Frank");
    Player p2("Chang");

    Continent* c1 = new Continent(1, "Europe", 5);
    Continent* c2 = new Continent(1, "Russia", 5);

    Territory* A0 = new Territory(0, "Great Britain", c1->getContinentID(), 0);
    Territory* A1 = new Territory(1, "Iceland", c1->getContinentID(), 0);
    Territory* A2 = new Territory(1, "Moscow", c2->getContinentID(), 0);

    c1->addTerritory(A0);
    c1->addTerritory(A1);

    c2->addTerritory(A2);

    map->addContinent(c1);
    map->addContinent(c2);

    p1.addTerritory(A0);
    p1.addTerritory(A1);

    p2.addTerritory(A2);

    p1.attach(&gameStatOb);
    p2.attach(&phaseOb);

    gameStatOb.addPlayer(&p1);
    gameStatOb.addPlayer(&p2);
    phaseOb.addPlayer(&p1);
    phaseOb.addPlayer(&p2);

    gameStatOb.boot();
    system("Pause");
    p1.issueOrder();
    system("Pause");
    p2.issueOrder();
    system("Pause");

    return 0;

}
