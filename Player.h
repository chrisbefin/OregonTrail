#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player 
{
    public:
    Player(bool);//if bool is true, main player, if bool is false, other family member
    string getName();
    void setLife(bool);
    bool getLife();
    void setHealth(bool);
    bool getHealth();
    
    private:
    bool life;//true for alive, false for dead
    string name;//holds the name of the player/party member
    bool health;//true for healthy, false for sick
    bool main;//true for main player, false for party member
    
};

#endif