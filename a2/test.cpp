#include <gtest/gtest.h>
#include "main.h"
#include <string>

TEST(CreateShipTest, createship){
    ship* s = ShipPrototype::makeShip("carrier");
    string result = s->name();
    EXPECT_EQ(0, result.compare("carrier"));
}

TEST(SerializeTest, serialize){
    vector<ship*> ships;
    ships.push_back(ShipPrototype::makeShip("carrier"));
    int result = serialize(ships, "config.txt");
    EXPECT_EQ(1, result);
}

TEST(DeserializeTest, deserialize){
    vector<ship*> ships;
    ofstream file;
    file.open("testconfig.txt");
    file << "destroyer" << endl;
    file.close();
    ships = deserialize("testconfig.txt");
    string result = ships.back()->name();
    EXPECT_EQ(0, result.compare("destroyer"));
}

TEST(PrintShipsTest, printship){
    vector<ship*> ships;
    ships.push_back(ShipPrototype::makeShip("patrol"));
    vector<string> results = printShips(ships);
    for(int i = 0; i < ships.size(); i++){
        EXPECT_EQ(0, results[i].compare(ships[i]->name()));
    }
}