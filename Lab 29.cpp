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
};
void printPlayers(map<string,array<list<Item>,3>>& Player);
void trading(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
void lootingItems(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
void repairitem(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
void itemdamage(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
void robbed(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
void replaceitems(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames);
//Added the randomprob and random party member and item for ease of access of a random number within those bounds
int randomprob(){
        int rand1= rand() % 100 + 1;
        return rand1;
}
int randomPartyMember(){
    int rand2=rand()%10;
    return rand2;
}
int randomitemNum(){
    int rand3=rand()%3;
    return rand3;
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
    vector<string> playernames;
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
    while(true){
        string Playername;
        if(!getline(file,Playername)){
            break;
        }
        playernames.push_back(Playername);
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
            trading(Players,playernames);
        }
        if(randomprob()<=40){
            lootingItems(Players,playernames);
        }
        if(randomprob()<=30){
            repairitem(Players,playernames);
        }
        if(randomprob()<=30){
            itemdamage(Players,playernames);
        }
        if(randomprob()<=5){
            robbed(Players,playernames);
        }
        if(randomprob()<=50){
            replaceitems(Players,playernames);
        }
        cout<<endl;
        
    }   
    cout<<"Results after simulation: "<<endl;
    printPlayers(Players);
    return 0;
}
    //Prints out all players in the map
void printPlayers(map<string,array<list<Item>,3>>& Player){
        //For loop starts here and prints out the players name
        cout<<endl;
    bool checkifempty=false;
    for(auto&[Playername,itemArray]:Player){
        cout<<"Player: "<<Playername<<endl;
        for(int i=0;i<3;i++){
            for(auto& item:itemArray[i]){
                if(item.itemname==""){
                    checkifempty=true;
                }
            }
        }
        if(checkifempty==true){
            cout<<Playername<<" has nothing!"<<endl;
            checkifempty=false;
        }
        else{
            //Loops 3 times to traverse the array of our struct item.
            for(int i=0;i<3;i++){
                for(auto& item:itemArray[i]){
                    cout<<item.itemname<<endl;
                    cout<<"Durability: "<<item.durability<<endl;
                    cout<<"Rarity: "<<item.rarity<<endl;
                }
            }
        }
        cout<<endl;
    }
}

void trading(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Trading started!"<<endl;
    int temp1=randomPartyMember();
    int temp2=randomPartyMember();
    while(temp1==temp2){
        temp2=randomPartyMember();
    }
    int temp3=randomitemNum();
    string tempName=playernames[temp1];
    string tempName2=playernames[temp2];
    if(Player.find(tempName) != Player.end() && Player.find(tempName2) != Player.end() && !Player[tempName][temp3].empty() &&  !Player[tempName2][temp3].empty()){
     
        Item tempItem=Player[tempName][temp3].front();
        Item tempItem2=Player[tempName2][temp3].front();
        cout<<"Trade successful!"<<endl;
        cout<<tempName<<" traded "<<tempItem.itemname<<" with "<<tempName2<<"'s "<<tempItem2.itemname<<endl;
        Player[tempName][temp3].front()=tempItem2;
        Player[tempName2][temp3].front()=tempItem;
       
    }
    else{
        cout<<"Trade failed because: ";
        if(Player[tempName][temp3].empty()){
            cout<<tempName<<" has a empty slot!"<<endl;
        }
        else if(Player[tempName2][temp3].empty()){
            cout<<tempName2<<" has a empty slot!"<<endl;
        }
    }
    cout<<endl;
}

void lootingItems(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Looting started!"<<endl;
    int choiceItem=randomitemNum();
    Item temp=randomItem(choiceItem);
    int randompartymember=randomPartyMember();
    string tempName=playernames[randompartymember];
    Item temp2=Player[tempName][choiceItem].front();

    if(temp2.robbed==true){
        cout<<tempName<<" gained "<<temp.itemname<<endl;
        Player[tempName][choiceItem].front()=temp;
    }

    else if(temp.rarity>temp2.rarity){
        cout<<tempName<<" swapped "<<temp2.itemname<<" for "<<temp.itemname<<endl;
        Player[tempName][choiceItem].front()=temp;
    }
    else{
        cout<<tempName<<" didnt want Random item it was a lower rarity"<<endl;
        cout<<endl;
    }
}

void repairitem(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Reparing started!"<<endl;
    int choiceItem=randomitemNum();
    int randompartymember=randomPartyMember();
    string tempName=playernames[randompartymember];
    auto& temp2 = Player[tempName][choiceItem].front();
    if(temp2.robbed==false){
        if(temp2.durability>=maxDurability){
            cout<<tempName<<" has max durability on "<<temp2.itemname<<" no repair was done"<<endl;
        }
        else{
            temp2.durability++;
            cout<<tempName<<" added +1 durability to "<<temp2.itemname<<endl;
            cout<<endl;
        }
    }
}

void itemdamage(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Durability loss!"<<endl;
    int choiceItem=randomitemNum();
    int randompartymember=randomPartyMember();
    string tempName=playernames[randompartymember];
    auto& temp2 = Player[tempName][choiceItem].front();
    if(temp2.robbed==false){
        temp2.durability--;
        if(temp2.durability==0){
            cout<<tempName<<"'s "<<temp2.itemname<<" has been broken!"<<endl;
            temp2.checkdurability();
        }
        else{
        cout<<tempName<<" lost 1 durability on "<<temp2.itemname<<endl;
        cout<<endl;
        }
    }
}

void robbed(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Random player being robbed...unlucky"<<endl;
    int randompartymember=randomPartyMember();
    string tempName=playernames[randompartymember];
    for(int i=0;i<3;i++){
    auto& temp2 = Player[tempName][i].front();
    temp2.robbed=true;
    temp2.itemname="";
    temp2.durability=0;
    temp2.rarity=0;
    }
    cout<<tempName<<" lost all of their items!"<<endl;
    cout<<endl;
}
void replaceitems(map<string,array<list<Item>,3>>& Player,const vector<string>& playernames){
    cout<<"Replacing lost items...."<<endl;
    int randompartymember=randomPartyMember();
    string tempName=playernames[randompartymember];
    int choiceItem=randomitemNum();
    auto& temp2 = Player[tempName][choiceItem].front();
    if(temp2.robbed==true){
        Item temp=randomItem(choiceItem);
        temp2=temp; 
    }
    else{
        cout<<tempName<<" does not need a item to be replaced..."<<endl;
    }
}