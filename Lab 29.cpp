// COMSC-210 | Lab 29-Alpha | Daniel Santisteban
// IDE used: VS Code

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <array>
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
    int rarity;
    bool robbed=false;
    Item(){
        itemname="";
        durability=0;
        rarity=0;
    }
    void checkdurability(){
        if(durability<=lowDurability){
            itemname="";
        }
    }
    void checkRarity(int rarity,string itemname){
        if(this->rarity<rarity){
            this->itemname=itemname;
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
//Added the randomprob and random party member and item for ease of access of a random number within those bounds
int randomprob(){
        int rand1= rand() % 100 + 1;
        return rand1;
}
int randomPartyMember(){
    int rand2=rand()%10+1;
    return rand2;
}
int randomitemNum(){
    int rand3=rand()%3+1;
}

// Added random item generator while not truly random it gets the job done and its meant to replace lost items etc
Item randomItem(int choice){
    Item temp;
    string weapon[]={"Shadowfang", "Nightblade", "Stormpiercer", "Doombringer", "Frostfang","Oblivion", "Venomstrike", "Moonstrike", "Soulreaper", "Thunderclaw"};
    string armor[] = {"Dragonplate", "Ironhide", "Moonshield", "Grimmail", "Crystal Vest","Steelguard", "Shadowplate", "Lightmail", "Boneguard", "Stormplate"};
    string potions[]={"Health Elixir", "Mana Draught", "Healing Salve", "Potion of Swiftness","Elixir of Fire", "Potion of Shadows", "Healing Draught", "Potion of Strength","Elixir of Wisdom", "Potion of Speed"};
    if(choice==0){
        temp.itemname=weapon[rand()%10];
        temp.durability=rand()%11;
        temp.rarity=rand()%10+1;
        return temp;
    }
    else if(choice==1){
        temp.itemname=armor[rand()%10];
        temp.durability=rand()%11;
        temp.rarity=rand()%10+1;
        return temp;
    }
    else{
        temp.itemname=potions[rand()%10];
        temp.durability=rand()%11;
        temp.rarity=rand()%10+1;
        return temp;
    }
}

// File path for testing. C:\\Users\\hope4\\Desktop\\COMSC 210 Work\\210-Lab-29\\PartyData.txt
int main(){
    srand(time(0));
    map<string,array<list<Item>,3>> Players;
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
    // This fills out our map data structure.
    while(getline(file,line)){
        string Playername=line;
        array<list<Item>, 3> itemsTemp;
        for(int i=0;i<3;i++){
            Item temp;
            getline(file,temp.itemname);
            getline(file,line);
            temp.durability=stoi(line);
            getline(file,line);
            temp.rarity=stoi(line);
            itemsTemp[i].push_back(temp);
        }
        Players[Playername]=itemsTemp;
    }
    file.close();
    //Prints players at the start of our function
    printPlayers(Players);
    cout<<"Simulation begins now"<<endl;
    for(int i=0;i<30;i++){
        cout<<"Iteration: "<<i+1<<endl;
        if(randomprob()<=60){
            cout<<"Trading"<<endl;
            int temp1=randomPartyMember();
            int temp2=randomPartyMember();
            while(temp1==temp2){
                    temp2=randomPartyMember();
            }
        }
        if(randomprob()<=40){
            cout<<"Looting"<<endl;
        }
        if(randomprob()<=30){
            cout<<"Item loss durability"<<endl;
        }
        if(randomprob()<=5){
            cout<<"Robbed by thieves"<<endl;
        }
        if(randomprob()<=50){
            cout<<"replacing items"<<endl;
        }
        cout<<endl;
    }   
    return 0;
}
    //Prints out all players in the map
void printPlayers(map<string,array<list<Item>,3>>& Player){
        //For loop starts here and prints out the players name
    for(auto&[Playername,itemArray]:Player){
        cout<<"Player: "<<Playername<<endl;
            //Loops 3 times to traverse the array of our struct item.
            for(int i=0;i<3;i++){
                for(auto& item:itemArray[i]){
                    cout<<item.itemname<<endl;
                    cout<<"Durability: "<<item.durability<<endl;
                    cout<<"Rarity: "<<item.rarity<<endl;
                }
            }
            cout<<endl;
    }

}