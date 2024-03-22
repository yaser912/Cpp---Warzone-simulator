#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "GameEngine.h"
using namespace std;

int main() {
    //---------------------------------------TASHFIA ADDED-------------------------------------------------
    cout << "----------------------------WELCOME TO WARZONE--------------------------------\n\n";
    cout << "----------------------------- PART 1 -----------------------------------------\n";
    selectMap(); //1)To select a map
    int numPlayers = numOfPlayers();//2)To enter and store the number of players and create a deck
    createDeck();
	bool StartObserver = StartPhaseObserver(); //3) TO switch OFF/ON observer and store the decision
	//--------------------------------------YASER ADDED--------------------------------------------------
	cout << "\n\n----------------------------- PART 2 -----------------------------------------\n\n";
	cout << "Game startup phase with the amount of players entered before:\n";
	showPart2(numPlayers);
   
    return 0;
}

//--------------------------------------TASHFIA ADDED--------------------------------------------------
//TO promote user to select a map
void selectMap() {

    //keep promoting user, until he enters a valid map
    int x = 0;
    while (x == 0) {
        cout << "\nHere is a list of maps available in the directory:\n-canada\n-google\n-mexico\n";
        cout << "\n1)Please type the name of the map you want to load: ";
        string mapname;
        cin >> mapname;
        string mapExtension = "maps//" + mapname + ".map";
        cout << "\nsearching for the map file: " << mapExtension << "\n";

        // file paths stored in an array
        vector<string> files = { mapExtension }; //"maps//google.map" and more can be added here as well. 

        // creating a Maploader to read
        for (int i = 0; i < files.size(); i++) {
            MapLoader* loader = new MapLoader(files[i]);
            if (loader->readMapFile()) {  //checking the directory and reading
                loader->createMap(); // creating the map
                cout << "\nMap Created.\n\n";

                delete loader; //For part 2. 
                x = 1;
            }
            else {
                cout << "Please select a map again.\n";
                x = 0;
                delete loader; //For part 2. 
            }

        }
    }
}


//To set the player names 
Player p[5];
//To promote user to enter the number of players.
int numOfPlayers() {

    //To set the number of playes
    int numOfPlayers = 0;
    cout << "\n\n2)Please enter the number of players (Must be between 2 and 5): ";
    cin >> numOfPlayers;
    while (!(numOfPlayers >= 2 && numOfPlayers <= 5)) {
        cout << "The numbers of players that you entered is invalid. Please enter again: ";
        cin >> numOfPlayers;
    }


    for (int i = 0; i < numOfPlayers; i++) {
        string name;
        cout << "\nEnter the name for player #" << (i + 1) << ": ";
        cin >> name;
        Player newPlayer(name);

        p[i] = newPlayer;

    }
    cout << endl;

    //Display the player array.
    cout << "\nThanks for join! ";
    for (int i = 0; i < numOfPlayers; i++) {
        cout << "\nPlayer #" << (i + 1) << ": " << p[i];

    }
    cout << endl;



    //returns the number of players.
    return numOfPlayers;
}

//To create a deck with right number of cards
void createDeck() {
    Hand* handObject;
    vector<string> orderList; // basic vector of strings to hold the list of orders
    Deck* deck1 = new Deck();
    Deck* deck2 = deck1; //Using the copy constructor to create a new deck object. 
    Hand* handlist = new Hand();
    Hand* handlist2 = handlist; //Using the copy constructor to create a new hand object.
    cout << "\nA deck with " << deck2->deck->size() << " cards has been created.\n";
    cout << "Each player currently has " << handlist2->hand->size() << " cards in their hand.\n\n";

}

//To promote user to switch ON/OFF the observer phase
bool StartPhaseObserver() {
	char ans;
	cout << "\nDo you want to switch on Observer at the start Phases? \n Type 'Y', if yes anything else is considered a no: ";
	cin >> ans;
	if (ans == 'Y') {
		cout << "Switching ON the Observer Mode.\n";
		return true;
	}
	else
		cout << "Observer Mode is OFF.\n";
	return false;

}

//--------------------------------------YASER ADDED--------------------------------------------------
void startupPhase(int numberOfPlayers, Map* map) {
	srand((unsigned)time(0));	//seed to generate random number
	int randomNumber = (rand() % numberOfPlayers); //assign random number between 0 and the number of players.
	vector<int> orderVector;	//This vector will contain randomly generated numbers that will determine the order of play of the players	

	//create the players + assign them the order of play
	switch (numberOfPlayers) {

	case 1:
	{
		//There is only one player, random order is not needed
		Player p1("Player 1");
		int counter = 0;	//The index of the current territory being added to the player's list of territories.
		int continentCounter = 0;
		cout << "\n\nIt is currently PLAYER 1's turn\n\n" << endl;
		//Assign all territories to this one player
		while (counter < map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter < map->getContinents()->size()) {

			for (int i = 0; i < map->getContinents()->at(continentCounter)->getTerritory()->size(); i++) {


				cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 1\n\n" << endl;
				p1.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(i));
				counter++;

				//This is where we can add the main game loop for the player..

				if (counter >= map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter != 5) {
					cout << "\nThere are no more territories left to assign in this continent. Incrementing the continent counter.\n " << endl;
					counter = 0;
					continentCounter++;
				}
			}
		}
		break;
	}
	case 2:
	{
		//There are 2 players, We need to assign a random order between the 2.
		for (int i = 0; i < numberOfPlayers; i++) {
			orderVector.push_back(i);
		}
		//shuffle this vector randomly to determine the play order of players.
		random_shuffle(orderVector.begin(), orderVector.end());


		Player p1("Player 1");
		Player p2("Player 2");
		int counter = 0;	//The index of the current territory being added to the player's list of territories.
		int continentCounter = 0;
		//If there are 2 players, there are 40 armies assigned to each player. Each army is added to the player's reinforcement pool.
		p1.addArmy(40);
		p2.addArmy(40);




		while (counter < map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter < map->getContinents()->size()) {

			for (int i = 0; i < numberOfPlayers; i++) {

				if (orderVector.at(i) == 0) {
					cout << "It is currently PLAYER 1's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 1\n\n" << endl;
					p1.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 1) {
					cout << "It is currently PLAYER 2's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 2\n\n" << endl;
					p2.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}

				if (counter >= map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter != 5) {
					cout << "\nThere are no more territories left to assign in this continent. Incrementing the continent counter.\n " << endl;
					counter = 0;
					continentCounter++;
				}
			}
		}



		break;
	}
	case 3:
	{
		//fill order vector with number of players
		for (int i = 0; i < numberOfPlayers; i++) {
			orderVector.push_back(i);
		}
		//shuffle the order vector
		random_shuffle(orderVector.begin(), orderVector.end());

		//create the players
		Player p1("Player 1");
		Player p2("Player 2");
		Player p3("Player 3");
		int counter = 0;	//The index of the current territory being added to the player's list of territories.
		int continentCounter = 0;
		//If there are 3 players, there are 35 armies assigned to each player. Each army is added to the player's reinforcement pool.
		p1.addArmy(35);
		p2.addArmy(35);
		p3.addArmy(35);

		while (counter < map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter < map->getContinents()->size()) {

			for (int i = 0; i < numberOfPlayers; i++) {

				if (orderVector.at(i) == 0) {
					cout << "It is currently PLAYER 1's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 1\n\n" << endl;
					p1.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 1) {
					cout << "It is currently PLAYER 2's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 2\n\n" << endl;
					p2.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 2) {
					cout << "It is currently PLAYER 3's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 3\n\n" << endl;
					p3.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}

				if (counter >= map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter != 5) {
					cout << "\nThere are no more territories left to assign in this continent. Incrementing the continent counter.\n " << endl;
					counter = 0;
					continentCounter++;
				}
			}
		}

		break;
	}
	case 4:
	{
		//fill order vector with number of players
		for (int i = 0; i < numberOfPlayers; i++) {
			orderVector.push_back(i);
		}
		//shuffle the order vector
		random_shuffle(orderVector.begin(), orderVector.end());

		//create the players
		Player p1("Player 1");
		Player p2("Player 2");
		Player p3("Player 3");
		Player p4("Player 4");
		int counter = 0;	//The index of the current territory being added to the player's list of territories.
		int continentCounter = 0;
		//If there are 4 players, there are 30 armies assigned to each player. Each army is added to the player's reinforcement pool.
		p1.addArmy(30);
		p2.addArmy(30);
		p3.addArmy(30);
		p4.addArmy(30);

		while (counter < map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter < map->getContinents()->size()) {

			for (int i = 0; i < numberOfPlayers; i++) {


				if (orderVector.at(i) == 0) {
					cout << "It is currently PLAYER 1's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 1\n\n" << endl;
					p1.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 1) {
					cout << "It is currently PLAYER 2's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 2\n\n" << endl;
					p2.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 2) {
					cout << "It is currently PLAYER 3's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 3\n\n" << endl;
					p3.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 3) {
					cout << "It is currently PLAYER 4's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 4\n\n" << endl;
					p4.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}




				if (counter >= map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter != 5) {
					cout << "\nThere are no more territories left to assign in this continent. Incrementing the continent counter.\n " << endl;
					counter = 0;
					continentCounter++;
				}

				if (continentCounter == 5) {
					//No more territories left, break out of loop
					break;
				}
			}
		}

		break;
	}
	case 5:
	{
		//fill order vector with number of players
		for (int i = 0; i < numberOfPlayers; i++) {
			orderVector.push_back(i);
		}
		//shuffle the order vector
		random_shuffle(orderVector.begin(), orderVector.end());

		//create the players
		Player p1("Player 1");
		Player p2("Player 2");
		Player p3("Player 3");
		Player p4("Player 4");
		Player p5("Player 5");
		int counter = 0;	//The index of the current territory being added to the player's list of territories.
		int continentCounter = 0;
		//If there are 5 players, there are 25 armies assigned to each player. Each army is added to the player's reinforcement pool.
		p1.addArmy(25);
		p2.addArmy(25);
		p3.addArmy(25);
		p4.addArmy(25);
		p5.addArmy(25);

		while (counter < map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter < map->getContinents()->size()) {

			for (int i = 0; i < numberOfPlayers; i++) {

				if (orderVector.at(i) == 0) {
					cout << "It is currently PLAYER 1's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 1\n\n" << endl;
					p1.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 1) {
					cout << "It is currently PLAYER 2's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 2\n\n" << endl;
					p2.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 2) {
					cout << "It is currently PLAYER 3's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 3\n\n" << endl;
					p3.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 3) {
					cout << "It is currently PLAYER 4's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 4\n\n" << endl;
					p4.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}
				if (orderVector.at(i) == 4) {
					cout << "It is currently PLAYER 5's turn\n\n" << endl;
					cout << "Adding the territory " << map->getContinents()->at(continentCounter)->getTerritory()->at(counter)->getTerrName() << " To PLAYER 5\n\n" << endl;
					p5.addTerritory(map->getContinents()->at(continentCounter)->getTerritory()->at(counter));
					counter++;

					//This is where the main game loop should be added.
				}

				if (counter >= map->getContinents()->at(continentCounter)->getTerritory()->size() && continentCounter != 5) {
					cout << "\nThere are no more territories left to assign in this continent. Incrementing the continent counter.\n " << endl;
					counter = 0;
					continentCounter++;
				}

				if (continentCounter == 5) {
					//No more territories left, break out of loop
					break;
				}
			}
		}

		break;

	}
	}

}

void showPart2(int numberOfPlayers) {

	//create the map
	Map* map = new Map(0);

	//create all the continents
	Continent* Continent1 = new Continent(1, "Europe", 5);
	Continent* Continent2 = new Continent(2, "Africa", 5);
	Continent* Continent3 = new Continent(2, "North America", 5);
	Continent* Continent4 = new Continent(2, "South America", 5);
	Continent* Continent5 = new Continent(2, "Asia", 5);
	Continent* Continent6 = new Continent(2, "Austrailia", 5);
	//add the continents to the map
	map->addContinent(Continent1);
	map->addContinent(Continent2);
	map->addContinent(Continent3);
	map->addContinent(Continent4);
	map->addContinent(Continent5);
	map->addContinent(Continent6);


	//create the territories
	Territory* A0 = new Territory(0, "Great Britain", Continent1->getContinentID(), 0);
	Territory* A1 = new Territory(1, "Iceland", Continent1->getContinentID(), 0);
	Territory* A2 = new Territory(2, "N.Europe", Continent1->getContinentID(), 0);
	Territory* A3 = new Territory(3, "W.Europe", Continent1->getContinentID(), 0);
	Territory* A4 = new Territory(4, "S.Europe", Continent1->getContinentID(), 0);
	Territory* A5 = new Territory(5, "Scandinavia", Continent1->getContinentID(), 0);
	Territory* A6 = new Territory(6, "Ukraine", Continent1->getContinentID(), 0);
	Territory* A7 = new Territory(7, "Egypt", Continent2->getContinentID(), 0);
	Territory* A8 = new Territory(8, "North Africa", Continent2->getContinentID(), 0);
	Territory* A9 = new Territory(9, "East Africa", Continent2->getContinentID(), 0);
	Territory* A10 = new Territory(10, "Congo", Continent2->getContinentID(), 0);
	Territory* A11 = new Territory(11, "Madagascar", Continent2->getContinentID(), 0);
	Territory* A12 = new Territory(12, "South Africa", Continent2->getContinentID(), 0);
	Territory* A13 = new Territory(13, "Alaska", Continent3->getContinentID(), 0);
	Territory* A14 = new Territory(14, "Northwest Territory", Continent3->getContinentID(), 0);
	Territory* A15 = new Territory(15, "Greendland", Continent3->getContinentID(), 0);
	Territory* A16 = new Territory(16, "Alberta", Continent3->getContinentID(), 0);
	Territory* A17 = new Territory(17, "Ontario", Continent3->getContinentID(), 0);
	Territory* A18 = new Territory(18, "Quebec", Continent3->getContinentID(), 0);
	Territory* A19 = new Territory(19, "Western United States", Continent3->getContinentID(), 0);
	Territory* A20 = new Territory(20, "Eastern United States", Continent3->getContinentID(), 0);
	Territory* A21 = new Territory(21, "Maxico", Continent3->getContinentID(), 0);
	Territory* A22 = new Territory(22, "Venezuela", Continent4->getContinentID(), 0);
	Territory* A23 = new Territory(23, "Peru", Continent4->getContinentID(), 0);
	Territory* A24 = new Territory(24, "Brazil", Continent4->getContinentID(), 0);
	Territory* A25 = new Territory(25, "Argentina", Continent4->getContinentID(), 0);
	Territory* A26 = new Territory(26, "Ural", Continent5->getContinentID(), 0);
	Territory* A27 = new Territory(27, "Siberia", Continent5->getContinentID(), 0);
	Territory* A28 = new Territory(28, "Yakutsk", Continent5->getContinentID(), 0);
	Territory* A29 = new Territory(29, "Kanchatka", Continent5->getContinentID(), 0);
	Territory* A30 = new Territory(30, "Kazakhstan", Continent5->getContinentID(), 0);
	Territory* A31 = new Territory(31, "Irkutsk", Continent5->getContinentID(), 0);
	Territory* A32 = new Territory(32, "Mongolia", Continent5->getContinentID(), 0);
	Territory* A33 = new Territory(33, "Japan", Continent5->getContinentID(), 0);
	Territory* A34 = new Territory(34, "Middle East", Continent5->getContinentID(), 0);
	Territory* A35 = new Territory(35, "China", Continent5->getContinentID(), 0);
	Territory* A36 = new Territory(36, "India", Continent5->getContinentID(), 0);
	Territory* A37 = new Territory(37, "Siam", Continent5->getContinentID(), 0);
	Territory* A38 = new Territory(38, "Indonesia", Continent6->getContinentID(), 0);
	Territory* A39 = new Territory(39, "New Guinea", Continent6->getContinentID(), 0);
	Territory* A40 = new Territory(40, "Western Austrailia", Continent6->getContinentID(), 0);
	Territory* A41 = new Territory(41, "Eastern Austrailia", Continent6->getContinentID(), 0);

	//add the territories to the continents
	Continent1->addTerritory(A0);
	Continent1->addTerritory(A1);
	Continent1->addTerritory(A2);
	Continent1->addTerritory(A3);
	Continent1->addTerritory(A4);
	Continent1->addTerritory(A5);
	Continent1->addTerritory(A6);
	Continent2->addTerritory(A7);
	Continent2->addTerritory(A8);
	Continent2->addTerritory(A9);
	Continent2->addTerritory(A10);
	Continent2->addTerritory(A11);
	Continent2->addTerritory(A12);
	Continent3->addTerritory(A13);
	Continent3->addTerritory(A14);
	Continent3->addTerritory(A15);
	Continent3->addTerritory(A16);
	Continent3->addTerritory(A17);
	Continent3->addTerritory(A18);
	Continent3->addTerritory(A19);
	Continent3->addTerritory(A20);
	Continent3->addTerritory(A21);
	Continent4->addTerritory(A22);
	Continent4->addTerritory(A23);
	Continent4->addTerritory(A24);
	Continent4->addTerritory(A25);
	Continent5->addTerritory(A26);
	Continent5->addTerritory(A27);
	Continent5->addTerritory(A28);
	Continent5->addTerritory(A29);
	Continent5->addTerritory(A30);
	Continent5->addTerritory(A31);
	Continent5->addTerritory(A32);
	Continent5->addTerritory(A33);
	Continent5->addTerritory(A34);
	Continent5->addTerritory(A35);
	Continent5->addTerritory(A36);
	Continent5->addTerritory(A37);
	Continent6->addTerritory(A38);
	Continent6->addTerritory(A39);
	Continent6->addTerritory(A40);
	Continent6->addTerritory(A41);



	//Function call to the start up method.
	startupPhase(numberOfPlayers, map);
}


