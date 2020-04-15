#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <vector>

#include "Player.h"
#include "Store.h"
#include "Game.h"
#include "Misfortunes.h"

using namespace std;

Store store;//creates object of class store, which handles all game functions related to money and supplies
Game game;//create object of class game, handles all game functions related to travelling 
vector<Player> players;//creates vector of player obejcts
Misfortunes misfortunes;//creates object of class Misfortunes
int randomNumbersDriver(int min, int max)
{
    // rand() % (max-min+1) + min
    return (rand() % (max-min+1)) + min;
}
void introduction()//prints out an introductory paragraph
{
    char character;
    cout << "Your goal is to travel from Independence, Missouri to Oregon City (2040 miles) by the end of fall" << endl;
    cout << "(November 30th, 1847). However, the trail is arduous. Each day costs you food and has risks." << endl;
    cout << "You can hunt and rest, but you have to get there before winter!" << endl << endl;
    cout << "Enter any character to continue" << endl;
    if (cin >> character)
    {
        return;
    }
    
}
void namePlayers()//assigns names to the vector of player objects
{
    cout << endl;
    for (int i = 0; i < 5; i++)//the vector is populated with 5 players
        {
            if (i == 0)
            {
                players.push_back(Player(true));//the first player in the players array is the main player
            }
            else//next 4 players are party members
            {
                players.push_back(Player(false));
            }
        }
        cout << endl;
        return;
}
int getNumPlayers()//helper function which determines how many living players there are
{
    int counter = 0;
    for (int i = 0; i < 5; i++)//loops through all player objects to see who is alive
    {
        if (players[i].getLife() == true)
        {
            counter++;
        }
    }
    return counter;
}
void statusUpdate()
{
    cout << endl;
    cout << "Current date: ";
    cout << game.getDate() << endl;
    cout << "Miles Travelled: " << game.getMiles() << endl;
    cout << "Distance to next milestone: " << game.getMilesToMilestone() << " miles" << endl;
    cout << "Food available: " << store.getFood() << " pounds" << endl;
    cout << "Bullets available: " << store.getBullets() << endl;
    cout << "Cash available: $" << store.getMoney() << endl;
    cout << endl;
    return;
}
bool checkEndGame()//checks if win and loss conditions have been met
{
    bool flag = false;
    if (store.getFood() <= 0 || store.getOxen() == 0 || players[0].getLife() == false || store.getWheels() <= -1)//loss conditions
    {
        flag = true;
        cout << endl;
        cout << "You have died of dysentery!" << endl;
        cout << players[0].getName() << endl;
        cout << "Miles travelled: " << game.getMiles() << endl;
        cout << "Food remaining: " << store.getFood() << " pounds" << endl;
        cout << "Cash remaining: $" << store.getMoney() << endl;
    }
    else if (game.getMiles() >= 2040)//win condition
    {
        flag = true;
        cout << "Congratulations! You made it to Oregon City!" << endl;
    }
    if (flag == true)//at the end of the game, results are written into a text file
    {
        ofstream myStream;
        myStream.open("results.txt");
        myStream << endl;
        myStream << players[0].getName() << endl;
        myStream << "Miles travelled: " << game.getMiles() << endl;
        myStream << "Food remaining: " << store.getFood() << " pounds" << endl;
        myStream << "Cash remaining: $" << store.getMoney() << endl;
        myStream << endl;
    }
    return flag;
}
void displayOptions()//the menu which has the turn options 
{
    cout << "1. Rest" << endl;
    cout << "2. Continue on the trail" << endl;
    cout << "3. Hunt" << endl;
    cout << "4. Quit" << endl;
    cout << "What would you like to do?" << endl;
}
void calcMisfortune()//handles execution of misfortune events with the help of misfortunes object
{
    int number = 0;
    number = misfortunes.misfortunePick();//0- nothing happens, 1-wheel, 2-illness, 3- ox
    if (number == 1)
    {
        store.useWheels(1);
        cout << "Oh no! One of the wagon wheels has broken!" << endl;
        cout << "You have " << store.getWheels() << " wheels remaining." << endl << endl;
    }
    else if (number == 2)//a party member falls ill
    {
        string response = "";
        int integer = randomNumbersDriver(0,4);
        players[integer].setHealth(false);
        cout << "Oh no! " << players[integer].getName() << " has dysentery." << endl;
        cout << "Would you like to use a medical kit?(Y/N)" << endl;//player has the option of using a medical kit to save the ill party member
        cin >> response;
        if (response != "Y" && response != "y" && response != "N" && response != "n")//checks for invalid input
        {
        
            cout << "Invalid input. You choose to press on." << endl;
            if (randomNumbersDriver(0, 100) < 70)//player has 70% chance of dying with no medKit and no rest
            {
                players[integer].setLife(false);//player's life bool is set to false
                cout << players[integer].getName() << " has died." << endl;
            }
            
        }
        if (response == "Y" || response == "y")
        {
            if (store.getMedkits() > 0)
            {
                store.useMedKits(1);//1 medical kit is used
                if (randomNumbersDriver(0, 100) > 50)//player has 50% chance of dying
                {
                    players[integer].setLife(false);//player's life bool is set to false since they are dead
                    cout << players[integer].getName() << " has died." << endl;
                }
                else
                {
                    players[integer].setHealth(true);//the ill person is healed by the medical kit
                    cout << players[integer].getName() << " has recovered." << endl;
                }
            }
            else//no medKits remaining
            {
                cout << "You have no medical kits to use." << endl;//execution jumps to asking about rest if no med kits are available
                response = "n";
            }
        }
        if (response == "N" || response == "n")
        {
            cout << "Would you like to rest for 3 days to allow " << players[integer].getName() << " to recover?(Y/N)" << endl;
            cin >> response;
            if (response == "Y" || response == "y")//30% chance of dying
            {
                game.addDays(3);//mandatory 3 days of rest
                cout << "You have rested for 3 days." << endl;
                if (randomNumbersDriver(0, 100) <= 30)//player dies
                {
                    players[integer].setLife(false);//player's life bool is set to false
                    cout << players[integer].getName() << " has died." << endl;
                }
                else//player recovers
                {
                    players[integer].setHealth(true);//player's health bool is set to true
                    cout << players[integer].getName() << " has recovered." << endl;
                }
            }
            else if (response == "n" || response == "N")//70% chance of dying
            {
                cout << "You choose to press on" << endl;
                if (randomNumbersDriver(0, 100) < 70)//player dies
                {
                    players[integer].setLife(false);//player's life bool is set to false
                    cout << players[integer].getName() << " has died." << endl;
                }
                else
                {
                    cout << players[integer].getName() << " has recovered." << endl;
                }
            }
            else//in the case of invalid input, the player automatically pushes on
            {
                cout << "Invalid input. You choose to press on." << endl;
                if (randomNumbersDriver(0, 100) < 70)//player dies
                {
                    players[integer].setLife(false);//player's life bool is set to false
                    cout << players[integer].getName() << " has died." << endl;
                }
                else
                {
                    cout << players[integer].getName() << " has recovered." << endl;
                }
            }
        }
    }
    else if (number == 3)//ox dies
    {
        store.useOxen(1);
        cout << "Oh no! An ox has died" << endl;
        cout << "You have " << store.getOxen() << " oxen remaining." << endl;
    }
}
void turnLoop()
{
    string choice = "";//tracks player's choice
    string decision = "";//tracks player's decision
    int number = 0;//int variable used for a variety of things within switch statement
    int players = 5;
   while (choice != "4") 
   {
       displayOptions();
       cin >> choice;
       if (choice != "1" && choice != "2" && choice != "3" && choice != "4")//checks for invalid user input
       {
           cout << "Invalid input" << endl;
           choice = "5";//if input is invalid, switch statement will go to the default case which will prompt user for a new input
       }
       switch(stoi(choice))
       {
           case 1://rest
           number = game.rest();// rest function returns number of days rested
           store.useFood(number * getNumPlayers() * 3);//food is consumed at a rate of 3 pounds per person per day
           break;
           case 2://travel
           number = game.travel();//travel function returns a number based on if you hit a milestone
           store.useFood(getNumPlayers() * 3 * 14);//each player consumes 3 pounds of food for 2 weeks
           if (number == 1)//if you hit a fort
           {
               
               while (decision != "3")//you can go to the store, rest or continue when at a fort
               {
                   decision = "";
                   cout << "What would you like to do?" << endl;
                   cout << "1. Rest" << endl;
                   cout << "2. Go to store" << endl;
                   cout << "3. Continue on the trail" << endl;
                   cin >> decision;
                   if (decision != "1" && decision != "2" && decision != "3")//checks for invalid input
                   {
                       cout << "Invalid input. You choose to continue on the trail." << endl;
                       decision = "3";
                   }
                   switch(stoi(decision))
                   {
                       case 1://rest
                       store.useFood(game.rest() * 3 * getNumPlayers());// rest: 3 pounds of food per person per day
                       break;
                       case 2://store
                       store.purchaseItems();//you get to buy things at forts
                       break;
                       case 3://continue on trail
                       cout << "Good Bye! Good luck on the rest of your journey." << endl << endl;
                       break;
                       default:
                       cout << "Invalid input. Enter a number between 1 and 3." << endl;
                       break;
                   }
               }
               //store.purchaseItems();//you get to buy things at forts
           }
           else if (number == 2)//if you hit a river
           {
               string decision = "";
               cout << "Would you like to rest before crossing the river?(Y/N)" << endl;//at rivers you can rest before crossing
               cin >> decision;
               if (decision == "y" || decision == "Y")
               {
                   cout << "You rest for 1 day before crossing" << endl;
                   store.useFood(getNumPlayers() * 3);//each living player consumes 3 pounds of food
                   cout << "After resting you are ready to cross the river." << endl; 
               }
                
               else if (decision == "n" || decision == "N")
               {
                   cout << "You prepare to cross the river immediately" << endl;
               }
               else
               {
                   cout << "Invalid input. You decide to cross the river right away." << endl;
               }
               cout << endl << "Would you like to ferry across the river? It costs $10 per person(Y/N)" << endl;
               cin >> decision; 
               if (decision == "Y" || decision == "y")
               {
                   store.spendMoney(getNumPlayers() * 10);//ferry costs 10 dollars per person
               }
               cout << "The crossing was successful." << endl << endl;//the crossing works either way
           }
           break;
           case 3://hunt
           game.addDays(1);//a hunting turn takes one day
           store.hunt();//call hunting function
           break;
           case 4://quit game
           cout << "Good Bye. Thanks for playing Oregon Trail!" << endl;
           return;
           break;
           default:
           cout << "Invalid input. Enter an integer between 1 and 4" << endl;
           break;
       }
       calcMisfortune();//misfortune has a chance of occuring at end of every turn
       store.raiders(game.getMiles());//raider attack has a chance of occuring at the end of every turn, takes argument of miles travelled
       if (checkEndGame() == true)// if any end game condition is met, the game ends
       {
           return;
       }
       statusUpdate();//status update is provided before the beginning of the next turn
   }
   return;
}
int main ()
{
    srand(time(0));//seed the rand function so that numbers are truly random
    char character;
    cout << "Welcome to Oregon Trail! Enter any character to begin the game." << endl;
    if (cin >> character)
    {
        //execute game
        introduction();//provides introductory paragraph
        namePlayers();//get names for the main player and party members
        game.setDate();//asks player to select a start date for their journey
        store.purchaseItems();//send player to the store for the first time
        statusUpdate();//status update is provided before beginning
        cout << "Time to begin your journey! Good luck!" << endl << endl;
        turnLoop();//game begins cycling through turns, loop ends when game is over
    }
    return 0;
}