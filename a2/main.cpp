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

using namespace std;

string filename = "config.txt";

/**
 * Base class for the creating the different ships
 */
class ship{
public:
    virtual ship* clone() = 0;
    virtual void type() = 0;
    virtual string name() = 0;
};

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
 * The ship prototype factory that handles making new ships and stores an
 * array of the prototypes.
 */
class ShipPrototype{
public:
    static ship* makeShip(string choice);
private:
    static ship* shipPrototypes[6];
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
void serialize(vector<ship*> ships){
    ofstream file;
    file.open("config.txt");
    for(int i = 0; i < ships.size(); i++){
        file << ships[i]->name() << endl;
    }
    file.close();
}

/**
 *  Deserialize the ship information contained in the file.
 *  Recreates the vector of selected ships by reading the ship names from the
 *  file and calling the clone function. 
 */
vector<ship*> deserialize(){
    vector<ship*> ships;
    ifstream file("config.txt");
    string line;
    while(getline(file, line)){
        ships.push_back(ShipPrototype::makeShip(line));
    }
    return ships;
}

/**
 *  Method for printing the selected ships to the console.
 */
void printShips(vector<ship*> ships){
    cout << "The Selected Ships Are:\n";
    for(int i = 0; i < ships.size(); i++){
        cout << "Ship" << i + 1 << ": ";
        ships[i]->type();
    }
}

/**
 *  Program Entry Point
 */
int main(int argc, char** argv) {
    //TODO: Serialize last configuration and attempt to load a previous config
    string choice;
    vector<ship*> ships;
    cout << "Do you want to use a pervious configuration? (y/n)\n";
    cin >> choice;
    if(choice.compare("y") == 0){
        ships = deserialize();
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
    printShips(ships);
    //Serialize the vector of ships
    serialize(ships);
    
    return 0;
}