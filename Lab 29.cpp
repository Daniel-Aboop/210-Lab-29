// COMSC-210 | Lab 29-Alpha | Daniel Santisteban
// IDE used: VS Code

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

const int maxDurability=10,lowDurability=0; // If durability reaches 0 Item breaks
const int maxRarity=10,lowRarity=1; //If other item has higher rarity take swap items.
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

// File path for testing. C:\\Users\\hope4\\Desktop\\COMSC 210 Work\\210-Lab-29\\PartyData.txt
int main(){
    srand(time(0));
    map<string,array<list<Item>,3>> Players;
    int ranNum = rand() % 100 + 1; // Number for % chances
    int ranPartyMem = rand() % 10 + 1; // Random Party member chosen for event.
     cout<<"Enter file path! ";
    string filepath;
    getline(cin,filepath);
    ifstream file(filepath);
    if(!file){
        cout<<"error opening file"<<endl;
        return 1;
    }
    else{
        cout<<"opened file!"<<endl;
    }
    string line;
    while(getline(file,line)){
        string Playername=line;
         array<list<Item>, 3> itemsTemp;
        for(int i=0;i<3;i++){

        }
    }
    file.close();
    return 0;
}