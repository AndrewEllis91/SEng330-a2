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

using namespace std;

/**
 * Base class for the creating the different ships
 */
class ship{
public:
    virtual ship* clone() = 0;
    virtual void type() = 0;
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
 *  Program Entry Point
 */
int main(int argc, char** argv) {
    //TODO: Serialize last configuration and attempt to load a previous config
    
    vector<ship*> ships;
    string choice;
    cout << "Type a ship to add\n";
    cout << "Type q followed by enter to finish\n";
    while(true){
        if(choice.compare("q") == 0){break;}
        cin >> choice;
        ships.push_back(ShipPrototype::makeShip(choice));
    }
    cout << "The Selected Ships Are:\n";
    for(int i = 0; i < ships.size() - 1; i++){
        cout << "Ship" << i + 1 << ": ";
        ships[i]->type();
    }
    return 0;
}

