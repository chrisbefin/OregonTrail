#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(bool flag)
{
    if (flag == true)//if argument bool is true, the object being constructed is the main player
    {
        cout << "First off, we'll need to know the names of you and your companions" << endl;
        cout << "What is your name?" << endl;
        cin >> name;//input is assigned to the name data member
        main = true;
        
    }
    else
    {
        cout << "What is the name of your party member?" << endl;//this is applied for all other party members
        cin >> name;
        main = false;
    }
    life = true;
    health = true;
}
string Player::getName()
{
    return name;
}
void Player::setLife(bool flag)//false is dead, true is alive
{
    life = flag;
}
bool Player::getLife()
{
    return life;
}
void Player::setHealth(bool flag)// true is healthy, false is ill
{
    health = flag;
}
bool Player::getHealth()
{
    return health;
}