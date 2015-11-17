/** 
 * File:   main.cpp
 * Author: Andrew Ellis
 *
 * Created on November 12, 2015, 8:08 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include "main.h"

using namespace std;

/**
 * The carrier class that is cloned when requested by the user
 */
class carrier : public ship{
public:
    const static int length = 5;
    carrier* clone(){return new carrier;}
    void type(){
        cout << "This ship is a carrier!\n";
    }
    string name(){return "carrier";}
};

/**
 * The destroyer class that is cloned when requested by the user
 */
class destroyer : public ship{
public:
    const static int length = 3;
    destroyer* clone(){return new destroyer;}
    void type(){
        cout << "This ship is a destroyer!\n";
    }
    string name(){return "destroyer";}
};

/**
 * The battleship class that is cloned when requested by the user
 */
class battleship : public ship{
public:
    const static int length = 4;
    battleship* clone(){return new battleship;}
    void type(){
        cout << "This ship is a battleship!\n";
    }
    string name(){return "battleship";}
};

/**
 * The sub class that is cloned when requested by the user
 */
class sub : public ship{
public:
    const static int length = 3;
    sub* clone(){return new sub;}
    void type(){
        cout << "This ship is a sub!\n";
    }
    string name(){return "sub";}
};

/**
 * The patrol class that is cloned when requested by the user
 */
class patrol : public ship{
public:
    const static int length = 4;
    patrol* clone(){return new patrol;}
    void type(){
        cout << "This ship is a patrol boat!\n";
    }
    string name(){return "patrol";}
};


/**
 * The method for creating ships that calls the clone function.
 */
ship* ShipPrototype::makeShip(string choice){
    if(choice.compare("carrier") == 0){
        return shipPrototypes[1]->clone();
    }else if(choice.compare("destroyer") == 0){
        return shipPrototypes[2]->clone();
    }else if(choice.compare("battleship") == 0){
        return shipPrototypes[3]->clone();
    }else if(choice.compare("sub") == 0){
        return shipPrototypes[4]->clone();
    }else if(choice.compare("patrol") == 0){
        return shipPrototypes[5]->clone();
    }
}

/**
 * Method which creates the prototypes and stores them in an array to be
 * cloned when needed.
 */
ship* ShipPrototype::shipPrototypes[] = {
    0, new carrier, new destroyer, new battleship, new sub, new patrol
};


/**
 *  Serialize the vector of ships to a file called config.txt
 *  This method works by getting the name of each ship from the vector
 *  and writting them to the file to be read and recreated later.
 */
int serialize(vector<ship*> ships, const char* filename){
    ofstream file;
    file.open(filename);
    for(int i = 0; i < ships.size(); i++){
        file << ships[i]->name() << endl;
    }
    file.close();
    return 1;
}

/**
 *  Deserialize the ship information contained in the file.
 *  Recreates the vector of selected ships by reading the ship names from the
 *  file and calling the clone function. 
 */
vector<ship*> deserialize(const char* filename){
    vector<ship*> ships;
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        ships.push_back(ShipPrototype::makeShip(line));
    }
    return ships;
}

/**
 *  Method for printing the selected ships to the console.
 */
vector<string> printShips(vector<ship*> ships){
    vector<string> names;
    cout << "The Selected Ships Are:\n";
    for(int i = 0; i < ships.size(); i++){
        cout << "Ship" << i + 1 << ": ";
        ships[i]->type();
        names.push_back(ships[i]->name());
    }
    return names;
}

/**
 *  Program Entry Point
 */
int main(int argc, char** argv) {
    string choice;
    const char* filename = "config.txt";
    vector<ship*> ships;
    
    // Checks if the user wants to use a saved configuration
    cout << "Do you want to use a pervious configuration? (y/n)\n";
    cin >> choice;
    if(choice.compare("y") == 0){
        ships = deserialize(filename);
        printShips(ships);
        return 0;
    }else if(choice.compare("n") == 0){
        //continue
    }else{
        cout << "Bad Input: Exiting\n";
        return 0;
    }
    //Allow the user to select the ships to use then save selections to a file.
    cout << "Type a ship to add\n";
    cout << "Type q followed by enter to finish\n";
    while(true){
        cin >> choice;
        if(choice.compare("q") == 0){break;}
        ships.push_back(ShipPrototype::makeShip(choice));
    }
    // Prints the selected configuration
    printShips(ships);
    //Serialize the vector of ships
    serialize(ships, filename);
    
    return 0;
}