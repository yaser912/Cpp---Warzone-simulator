#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
using namespace std;

// To load a map file and create a map
class MapLoader {
public:

    MapLoader(string path); // Constructor to take the path
    MapLoader(const MapLoader& mapLoader); // Copy Constructor
    ~MapLoader(); // Destructor
    MapLoader& operator=(const MapLoader& mapLoader);  // Overloading assignment 
    friend ostream& operator<<(ostream& out, const MapLoader& mapLoader); // For inserting string 
   

    bool readMapFile(); // Read the .map file
    Map* createMap(); // Create a Map object


private:

    // To store attributes of the Continents from the map file
    struct continents {
        vector<int> contID;
        vector<string> contNames;
        vector<int> bonusArmy;
    } continentsinfo;

    // To store attributes of the Territory from the map file
    struct territories {
        vector<int> terrId;
        vector<string> terrName;
        vector<int> terrContinentId;
        vector<int> terrArmies;
    } territoriesinfo;

    // To store attributes of borders from the map file
    struct borders {
        vector<vector<string> > nextTerrID;
    } bordersinfo;

    string pathMap; // path of the .map file

    void removeinfo(); // Remove the arrays of the structs 
    
   // split strings to store accordingly
    vector<string> split(const string& line, char delim); 
    bool splitContinentLine(string oneline); 
    bool splitTerritoryLine(string oneline); 
    bool splitBorderLine(string oneline); 

  
};
