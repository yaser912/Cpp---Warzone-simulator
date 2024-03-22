#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Map.h"
#include "MapLoader.h"

using namespace std;

// Constructor
MapLoader::MapLoader(string path) {
    pathMap = path;
}

// Copy Constructor
MapLoader::MapLoader(const MapLoader& mapLoader) {
    pathMap = mapLoader.pathMap;
    continentsinfo = mapLoader.continentsinfo;
    territoriesinfo = mapLoader.territoriesinfo;
    bordersinfo = mapLoader.bordersinfo;
}

// Destructor
MapLoader::~MapLoader() {
    pathMap = "";
    removeinfo(); 
    //cout << "MAP DELETED! \n";
}

// Remove the arrays of the structs 
void MapLoader::removeinfo() {
    continentsinfo.contID.clear();
    continentsinfo.contNames.clear();
    continentsinfo.bonusArmy.clear();
    territoriesinfo.terrId.clear();
    territoriesinfo.terrName.clear();
    territoriesinfo.terrContinentId.clear();
    territoriesinfo.terrArmies.clear();
    bordersinfo.nextTerrID.clear();
}

// Assignment operator
MapLoader& MapLoader::operator=(const MapLoader& mapLoader) {
    pathMap = mapLoader.pathMap;
    continentsinfo = mapLoader.continentsinfo;
    territoriesinfo = mapLoader.territoriesinfo;
    bordersinfo = mapLoader.bordersinfo;

    return *this;
}

//Insertion operator
ostream& operator<<(ostream& out, const MapLoader& mapLoader) {
    out << "Path: " << mapLoader.pathMap << "\n";
    return out;
}


int forID = 0; //To add continent ID


// Read data from the map file and store them accordingly. 
bool MapLoader::readMapFile() {

    ifstream mapFile(pathMap); // Open the map file

    if (mapFile.is_open()) { // If the map file opens

        string oneLine; // To read a line
        int counter = -1; // for switch, to read file accordingly

        // Read the entire text file and one line at a time
        while (getline(mapFile, oneLine)) {

            // Find the text [continents] from the map folder
            if (oneLine.find("[continents]") != string::npos) {

                counter = 1; // This indicates the next lines will be continents and we have to store those values
                continue; // This line should be skipped.
            }
            // Find the text [countries] from the map folder
            else if (oneLine.find("[countries]") != string::npos) {
                
                counter = 2;// This indicates the next lines will be territories and we have to store those values
                continue; // This line should be skipped.
            }
            // Find the text [borders] from the map folder
            else if (oneLine.find("[borders]") != string::npos) {
                
                counter = 3;// This indicates the next lines will be borders and we have to store those values
                continue; // This line should be skipped.
            }

            //To store important values of the files
            if (!oneLine.empty()) {

                switch (counter) {
                case 1:
                    splitContinentLine(oneLine); // To store in continentinfo
                    break;
                case 2:
                    splitTerritoryLine(oneLine); // To store in territoriesinfo
                    break;
                case 3:
                    splitBorderLine(oneLine); // To store in bordersinfo
                    break;
                }
            }
        }
        mapFile.close();
  
        cout << "Found the Map File and completly read it."<<endl;
        
  
    }
    else {   // If cannot open the map file.
        cout << "Unable to open the Map file of the path: " << pathMap << endl;
        return 0;
    }


    //TO TEST IF FILES ARE STORED in the STRUCTS TERRITORY AND CONTINENT
     /*
        for (int i = 0; i < territoriesinfo.terrContinentId.size(); i++)
        cout << territoriesinfo.terrContinentId[i] << "\n";
      */
    
    return 1;
}


// split the line with continent information and store
bool MapLoader::splitContinentLine(string oneline) {

    vector<string> hold = split(oneline, ' ');
    if (hold.size() >= 2) { // To validate the map format

        //to convert to type int from string
        stringstream convert(hold[1]);
        int val = 0;
        convert >> val;
        forID = forID + 1; // for continent id

        // store the read data in the continents struct
        continentsinfo.contID.push_back(forID);
        continentsinfo.contNames.push_back(hold[0]);
        continentsinfo.bonusArmy.push_back(val);
        return 1;
    }
    return 0;
}


// split the line with territory information and store
bool MapLoader::splitTerritoryLine(string oneline) {

    vector<string> hold = split(oneline, ' ');
    
    if (hold.size() >= 5) {  // To validate the map format

       // store the read data in the continents struct
        //to convert to type int from string
        stringstream convert1(hold[0]);
        int val1 = 0;
        convert1 >> val1;
        territoriesinfo.terrId.push_back(val1);

        territoriesinfo.terrName.push_back(hold[1]);

        stringstream convert2(hold[2]);
        int val2 = 0;
        convert2 >> val2;
        territoriesinfo.terrContinentId.push_back(val2);

        stringstream convert3(hold[3]);
        int val3 = 0;
        convert3 >> val3;
        territoriesinfo.terrArmies.push_back(val3);

        return 1;
    }
    return 0;
}

// split the line with border information and store (CHECK)
bool MapLoader::splitBorderLine(string oneline) {
    vector<string> hold = split(oneline, ' ');

    if (hold.size() > 0) { // To validate the map format
        bordersinfo.nextTerrID.push_back(hold);
        return 1;
    }
    return 0;
} // NOTE: The first column is the id of the territory so its skiped, the following beside it is its next territory


// Divid a string with a specified delimiter, return an array of values
vector<string> MapLoader::split(const string& oneline, char delim) {
    vector<string> space;
    stringstream sstream(oneline);
    string value;

    while (getline(sstream, value, delim)) {
        space.push_back(value);
    }
    return space;
}

// create a Map obj using data continers
Map* MapLoader::createMap() {
    Map* map = new Map(territoriesinfo.terrContinentId.size()); // new Map


    //Adding territories to the continents and then to the map
    for (int i = 0; i < continentsinfo.contNames.size(); i++) {
        Continent* continent = new Continent(continentsinfo.contID[i], continentsinfo.contNames[i], continentsinfo.bonusArmy[i]);

        cout << "\n\n " << continentsinfo.contNames[i] << "\n"; //to test continent

        for (int j = 0; j < territoriesinfo.terrName.size(); j++) {
            Territory* territory = new Territory(territoriesinfo.terrId[j], territoriesinfo.terrName[j], territoriesinfo.terrContinentId[j], territoriesinfo.terrArmies[j]);

            if (continentsinfo.contID[i] == territoriesinfo.terrContinentId[j]) {

                cout << territoriesinfo.terrId[j] << " " << territoriesinfo.terrName[j] << "\n";  //to test territories

                continent->addTerritory(territory);
            }
        }
        map->addContinent(continent);
    }


    // add borders -------LEFT
    for (int i = 0; i < bordersinfo.nextTerrID.size(); i++) {
        for (int j = 1; bordersinfo.nextTerrID[i].size() > 1 && j < bordersinfo.nextTerrID[i].size(); j++) {
            int a = stoi(bordersinfo.nextTerrID[i][j]);
      


        }
    }


    return map;
}
