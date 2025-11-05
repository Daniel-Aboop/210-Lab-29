// COMSC-210 | Lab 29-Alpha | Daniel Santisteban
// IDE used: VS Code

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <random>

using namespace std;



const int maxRarity=10,lowRarity=1; //If other item has higher rarity take swap items.
const int maxDurability=10,lowDurability=0; // If durability reaches 0 Item breaks
struct Item{
    string itemname;
    int durability;
    int Rarity;

    void checkdurability(){
        if(durability<=lowDurability){
            itemname="";
        }
    }
};

void printPlayers(map<string,array<list<Item>,3>>& Player);
void trading(map<string,array<list<Item>,3>>& Player);
void lootingItems(map<string,array<list<Item>,3>>& Player);
void itemDamage(map<string,array<list<Item>,3>>& Player);
void repairitem(map<string,array<list<Item>,3>>& Player);
void robbed(map<string,array<list<Item>,3>>& Player);
void replaceitems(map<string,array<list<Item>,3>>& Player);

int main(){
    map<string,array<list<Item>,3>> Player;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> ranNum(1, 100);// Number for % chances
    uniform_int_distribution<int> ranPartyMem(1, 8);// Random Party member chosen for event.
    

    return 0;
}