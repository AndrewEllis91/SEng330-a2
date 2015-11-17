/* 
 * File:   main.h
 * Author: AndrewPC
 *
 * Created on November 16, 2015, 8:49 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <string>

using namespace std;

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
 * The ship prototype factory that handles making new ships and stores an
 * array of the prototypes.
 */
class ShipPrototype{
public:
    static ship* makeShip(string choice);
private:
    static ship* shipPrototypes[6];
};

vector<string> printShips(vector<ship*> ships);
int serialize(vector<ship*> ships, const char* filename);
vector<ship*> deserialize(const char* filename);

#endif	/* MAIN_H */

