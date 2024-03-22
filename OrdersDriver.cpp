#include "Map.h"
#include "Orders.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Player* p1 = new Player("Farah");
	Player* p2 = new Player("Franco");
	Player* p3 = new Player("Yasir");

	Map m;
	m.name = "World_Map";

	Territory* t1 = new Territory(1, "Canada", 0,122,345);
	Territory* t2 = new Territory(2, "United States", 0,64,246);
	Territory* t3 = new Territory(3, "Mexico", 0,76,323);
	Territory* t4 = new Territory(4, "Vietnam", 1,123,563);


	m.addAdjTerritory(t1, t2);
	m.addAdjTerritory(t2, t3);

	t1->setOwner(p1);
	t2->setOwner(p2);
	t3->setOwner(p3);

	Deploy* deploy_1 = new Deploy(p1, t1, 10);
	Advance* advance_1 = new Advance(p2, t2, t1, 20);
	Bomb* bomb_1 = new Bomb(p3, t3, t2);
	Blockade* blockade_1 = new Blockade(p1, t1);
	Airlift* airlift_1 = new Airlift(p1, t2, t4, 15);
	Negotiate* negotiate_1 = new Negotiate(p2, p3);

	cout << *deploy_1 << endl;
	cout << *advance_1 << endl;
	cout << *bomb_1 << endl;
	cout << *blockade_1 << endl;
	cout << *airlift_1 << endl;
	cout << *negotiate_1 << endl << endl;

	cout << "===========================================" << endl;
	cout << "Testing validate() and execute() methods..." << endl;
	cout << "===========================================" << endl << endl;

	p1->addReinforcements(20);
	cout << "Deploy class:\n" << endl;
	cout << "Initially, territory has " << t1->numberOfArmies << " armies and its owner has " << p1->getReinforcementPool() << " reinforcements.\n" << endl;
	deploy_1->execute();
	cout << "\nAfter, territory has " << t1->numberOfArmies << " armies and its owner has " << p1->getReinforcementPool() << " reinforcements." << endl;

	cout << endl << endl;

	cout << "Advance class:\n" << endl;
	advance_1->execute();

	cout << endl << endl;

	cout << "Bomb class:\n" << endl;
	bomb_1->execute();

	cout << endl << endl;

	cout << "Blockade class:\n" << endl;
	blockade_1->execute();

	cout << endl << endl;

	cout << "Airlift class:\n" << endl;
	airlift_1->execute();

	cout << endl << endl;

	cout << "Negotiate class:\n" << endl;
	negotiate_1->execute();

	cout << endl << endl;

	cout << "==============================" << endl;
	cout << "OrderList test" << endl;
	cout << "==============================" << endl << endl;

	OrdersList* ol = new OrdersList();
	ol->add(deploy_1);
	ol->add(advance_1);
	ol->add(bomb_1);
	ol->add(blockade_1);
	ol->add(airlift_1);
	ol->add(negotiate_1);

	cout << *ol << endl;

	cout << "checking the moving and removing methods." << endl;
	cout << "removing Advance order object and Bomb order object\n" << endl;

	ol->remove(1);
	ol->remove(2);

	cout << *ol << endl;

	cout << "moving the positions of Bomb order object from 2 to index 3\n" << endl;

	ol->move(2, 3);

	cout << *ol << endl;

	cout << "moving the positions of Airlift order object from index=5 to index 6\n" << endl;

	ol->move(5, 6);

	cout << *ol << endl;

	cout << "removing Bomb order object at index 3\n" << endl;

	ol->remove(3);

	cout << *ol << endl;

	return 0;
}