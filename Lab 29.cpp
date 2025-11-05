// COMSC-210 | Lab 29-Alpha | Daniel Santisteban
// IDE used: VS Code

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

void printPlayers(map<string,array<list<Item>,3>>& Player);

const int maxRarity=10,lowRarity=1;
const int maxDurability=10,lowDurability=0; // If 
struct Item{
    string itemname;
    int durability;
    int Rarity;
};

int main(){
    map<string,array<list<Item>,3>> Player;

    return 0;
}