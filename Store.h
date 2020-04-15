#ifndef STORE_H
#define STORE_H

using namespace std;

class Store
{
    public:
    Store();//constructor initializes the object
    double purchaseItems();//runs a loop which allows the user to purchase any category of items they want
    void displayMenu();//displays the menu which has all of the purchasing options
    void spendMoney(int);//subtracts from player's total money
    void useFood(int);//subtracts from player's total food
    void useBullets(int);//subtracts from player's total bullets
    void useWheels(int);//subtracts from player's total wagon wheels
    void useMedKits(int);//subtracts from player's total medical kits
    void useOxen(int);//subtracts from player's total oxen
    double getMoney();//returns amount of money
    int getFood();//returns amount of food
    int getBullets();//returns amount of bullets
    int getWheels();//returns amount of wheels
    int getMedkits();//returns amount of medical kits
    int getOxen();//returns amount of oxen
    void hunt();//function executes a hunt
    bool puzzle();//gives a player 3 tries to guess a number, returns true if they succeed
    void raiders(int);//function determines if a raider attack occurs and then potentially executes raider attack
    
    private:
    int fortNum;//indicates how many forts the player has been to, which impacts item prices
    double money;//tracks how much remaining money the player has
    double priceMultiplier;
    double foodPrice;//tracks price of food
    int yokePrice;//tracks price of oxen
    int bulletsPrice;//tracks price of bullets
    int wheelsPrice;//tracks price of wheels
    int medKitsPrice;//tracks price of medical kits
    int wheels;//number of spare wagon wheels
    int oxen;//number of spare oxen
    int food;//tracks pounds of food 
    int bullets;//tracks number of bullets
    int medKits;//tracks number of medKits
    
};

#endif