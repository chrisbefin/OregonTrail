#include "Store.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
    
    int randomNumbersStore(int min, int max)//helper function, returns number between two given bounds
    {
    // rand() % (max-min+1) + min
    return (rand() % (max-min+1)) + min;
    }
    Store::Store()
    {
        money = 1000;//you only have 1000 to spend cause you automatically buy a wagon
        wheelsPrice = 20;
        bulletsPrice = 2;
        foodPrice = 0.5;
        yokePrice = 50;//must purchase between 2 and 4
        medKitsPrice = 25;
        fortNum = 0;
        wheels = 0;
        bullets = 0;
        food = 0;
        oxen = 0;
        medKits = 0;
    }
    void Store::displayMenu()//displays purchasing options
    {
        cout << endl;
        cout << "Select a numberical option" << endl;
        cout << "1. Buy oxen" << endl;
        cout << "2. Buy food" << endl;
        cout << "3. Buy bullets" << endl;
        cout << "4. Buy wagon wheels" << endl;
        cout << "5. Buy medical kits" << endl;
        cout << "6. Leave the store" << endl;
    }
    double Store::purchaseItems()//runs a loop which allows the user to purchase any category of items they want
    {
        priceMultiplier = 1 + (fortNum * 0.25);//multiplier which is applied to prices as game goes on
        ifstream intro("store.txt");
        string line;
        if(fortNum == 0)
        {
            while (getline(intro, line))//prints introduction paragraph if it is the first time in store
            {
                cout << line << endl;
            }
        }
        string choice = "";//empty string which holds user input
        string number;
        int quantity = 0;
        double price = 0;
        double total = 0; //tracks total bill
        while (choice != "6")
        {
            displayMenu();
            cin >> choice;//getline(cin, choice);//must make sure choice is an int
            if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
            {
                cout << "Invalid input. You choose to leave the store." << endl;//checks if player input is valid
                choice = "6";//if it is not, the user will simply leave the store
            }
            switch (stoi(choice))
            {
                case 1://buy yoke of oxen
                price = yokePrice * priceMultiplier;
                cout << "How many yoke of oxen would you like to buy?" << endl;
                cout << "Each yoke costs $" << price << " and has 2 oxen." << endl;
                cin >> number;//getline (cin, number);
                quantity = stoi(number);
                if (money - (quantity * price) <= 0)
                {
                    cout << "You can't afford that" << endl;
                }
                else
                {
                    oxen = oxen + (quantity * 2);
                    money = money - (quantity * price);
                    total = total + (quantity * price);
                }
                break;
                case 2://buy food
                price = foodPrice * priceMultiplier;
                cout << "How many pounds of food would you like to buy?" << endl;
                cout << "Each pound costs $" << price << ". 200 lbs. per person is recommended." << endl;
                cout << "Caution: Your wagon can only hold a maximum of 1000 pounds of food." << endl;
                cin >> number;
                quantity = stoi(number);
                if (money - (quantity * price) <= 0)
                {
                    cout << "You can't afford that" << endl;
                }
                else
                {
                    food = food + quantity;
                    money = money - (quantity * price);
                    total = total + (quantity * price);
                }
                break;
                case 3://buy bullets
                price = bulletsPrice * priceMultiplier;
                cout << "How many boxes of bullets would you like to buy?" << endl;
                cout << "Each box costs $" << price << " and contains 20 bullets." << endl;
                cin >> number;
                quantity = stoi(number);
                if (money - (quantity * price) <= 0)
                {
                    cout << "You can't afford that" << endl;
                }
                else
                {
                    bullets = bullets + (quantity * 20);
                    money = money - (quantity * price);
                    total = total + (quantity * price);
                }
                break;
                case 4://buy wheels
                price = wheelsPrice * priceMultiplier;
                cout << "How many spare wagon wheels would you like to buy?" << endl;
                cout << "Each wheel costs $" << price << endl;
                cin >> number;
                quantity = stoi(number);
                if (money - (quantity * price) <= 0)
                {
                    cout << "You can't afford that" << endl;
                }
                else
                {
                    wheels = wheels + quantity;
                    money = money - (quantity * price);
                    total = total + (quantity * price);
                }
                break;
                case 5://buy medical kits
                price = medKitsPrice * priceMultiplier;
                cout << "How many medical kits would you like to buy?" << endl;
                cout << "Each kit costs $" << price << endl;
                cin >> number;//getline (cin, number);
                quantity = stoi(number);
                if (money - (quantity * price) <= 0)
                {
                    cout << "You can't afford that" << endl;
                }
                else
                {
                    medKits = medKits + quantity;
                    money = money - (quantity * price);
                    total = total + (quantity * price);
                    
                }
                break;
                case 6://quit
                cout << "good bye! Safe travels!" << endl;
                break;
                default:
                cout << "that is not an option." << endl << endl;
                break;
            }
            cout << "Your total bill is: " << total << " dollars" << endl << endl;
            
        }
        fortNum = fortNum + 1;// increments the variable which tracks how many forts the player has been to
        
        
        
    }
    void Store::spendMoney(int num)
    {
        money = money - num;
    }
    void Store::useFood(int num)
    {
        food = food - num;
    }
    void Store::useBullets(int num)
    {
        bullets = bullets - num;
    }
    void Store::useWheels(int num)
    {
        wheels = wheels - num;
    }
    void Store::useMedKits(int num)
    {
        medKits = medKits - num;
    }
    void Store::useOxen(int num)
    {
        oxen = oxen - num;
    }
    double Store::getMoney()
    {
        return money;
    }
    int Store::getFood()
    {
        if (food < 0)//you lose before food can become negative
        {
            return 0;
        }
        if (food > 1000)//max food the wagon can hold is 1000
        {
            cout << "The wagon can only hold 1000 pounds of food";
            food = 1000;
        }
        return food;
    }
    int Store::getBullets()
    {
        if (bullets < 0)//you cannot have negative bullets
        {
            bullets = 0;
        }
        return bullets;
    }
    int Store::getWheels()
    {
        return wheels;
    }
    int Store::getMedkits()
    {
        return medKits;
    }
    int Store::getOxen()
    {
        if (oxen < 0)//you cannot have a negative number of oxen
        {
            oxen = 0;
        }
        return oxen;
    }
    void Store::hunt()
    {
        string decision = "";//holds player input
        bool animal = false;//tracks if the player was able to kill an animal
        bool success;//tracks if the player completed the puzzle successfully
        if (randomNumbersStore(0, 100) <= 50)//rabbit
        {
            cout << "You got lucky! You encountered a rabbit." << endl;
            animal = true;//bool goes to true when an animal is found
            cout << "Do you want to hunt?(Y/N)" << endl;
            cin >> decision;
            if (decision == "Y" || decision == "y")
            {
                if (bullets >= 10)//must have at least 10 bullets to try to hunt
                {
                    cout << "You must successfully complete the puzzle to get the kill." << endl;
                    success = puzzle();
                    if (success == true)
                    {
                        cout << "Your hunt was successful." << endl;
                        bullets = bullets - 10;
                        food = food + 2;//2 pounds of meat from a rabbit
                    }
                    else
                    {
                        cout << "Your hunt was unsuccessful" << endl;
                    }
                }
                else
                {
                    cout << "You don't have enough bullets to hunt" << endl;
                }
            }
        }
        if (randomNumbersStore(0, 100) <= 25)//fox
        {
            cout << "You got lucky! You encountered a fox." << endl;
            animal = true;//bool goes to true when an animal is found
            cout << "Do you want to hunt?(Y/N)" << endl;
            cin >> decision;
            if (decision == "Y" || decision == "y")
            {
                if (bullets >= 10)//must have at least 10 bullets to try to hunt
                {
                    cout << "You must successfully complete the puzzle to get the kill." << endl;
                    success = puzzle();
                    if (success == true)
                    {
                        cout << "Your hunt was successful." << endl;
                        bullets = bullets - 8;
                        food = food + 5;
                    }
                    else
                    {
                        cout << "Your hunt was unsuccessful" << endl;
                    }
                }
                else
                {
                    cout << "You don't have enough bullets to hunt" << endl;
                }
            }
        }
        if (randomNumbersStore(0, 100) <= 15)//deer
        {
            cout << "You got lucky! You encountered a deer." << endl;
            animal = true;//bool goes to true when an animal is found
            cout << "Do you want to hunt?(Y/N)" << endl;
            cin >> decision;
            if (decision == "Y" || decision == "y")
            {
                if (bullets >= 10)//must have at least 10 bullets to try to hunt
                {
                    cout << "You must successfully complete the puzzle to get the kill." << endl;
                    success = puzzle();
                    if (success == true)
                    {
                        cout << "Your hunt was successful." << endl;
                        bullets = bullets - 5;
                        food = food + randomNumbersStore(30, 55);
                    }
                    else
                    {
                        cout << "Your hunt was unsuccessful" << endl;
                    }
                }
                else
                {
                    cout << "You don't have enough bullets to hunt" << endl;
                }
            }
        }
        if (randomNumbersStore(0, 100) <= 7)//bear
        {
            cout << "You got lucky! You encountered a bear." << endl;
            animal = true;//bool goes to true when an animal is found
            cout << "Do you want to hunt?(Y/N)" << endl;
            cin >> decision;
            if (decision == "Y" || decision == "y")
            {
                if (bullets >= 10)//must have at least 10 bullets to try to hunt
                {
                    cout << "You must successfully complete the puzzle to get the kill." << endl;
                    success = puzzle();
                    if (success == true)
                    {
                        cout << "Your hunt was successful." << endl;
                        bullets = bullets - 10;
                        food = food + randomNumbersStore(100, 350);
                    }
                    else
                    {
                        cout << "Your hunt was unsuccessful" << endl;
                    }
                }
                else
                {
                    cout << "You don't have enough bullets to hunt" << endl;
                }
            }
        }
        if (randomNumbersStore(0, 100) <= 5)//moose
        {
            cout << "You got lucky! You encountered a moose." << endl;
            animal = true;//bool goes to true when an animal is found
            cout << "Do you want to hunt?(Y/N)" << endl;
            cin >> decision;
            if (decision == "Y" || decision == "y")
            {
                if (bullets >= 10)//must have at least 10 bullets to try to hunt
                {
                    cout << "You must successfully complete the puzzle to get the kill." << endl;
                    success = puzzle();
                    if (success == true)
                    {
                        cout << "Your hunt was successful." << endl;
                        bullets = bullets - 12;
                        food = food + randomNumbersStore(300, 600);
                    }
                    else
                    {
                        cout << "Your hunt was unsuccessful" << endl;
                    }
                }
                else
                {
                    cout << "You don't have enough bullets to hunt" << endl;
                }
            }
        }
        if (food > 1000)
        {
            cout << "The wagon cannot carry more than 1000 pounds of food" << endl;
            food = 1000;
        }
        if (animal == false)
        {
            cout << "You weren't able to find any game." << endl << endl;
        }
        cout << "What would you like to have for dinner tonight?" << endl;//after the player hunts they decide what they would like to eat
        cout << "1. A brisket dinner prepared by celebrity chef Guy Fieri - 20 pounds of food" << endl;
        cout << "2. A hearty meatloaf - 12 pounds of food" << endl;
        cout << "3. A thin stew - 6 pounds of food" << endl;
        cin >> decision;
        if (decision == "1")
        {
            cout << "You eat well" << endl;
            food = food - 20;
        }
        else if (decision == "2")
        {
            cout << "You eat moderately well" << endl;
            food = food - 12;
        }
        else if (decision == "3")
        {
            cout << "You eat poorly" << endl;
            food = food - 8;
        }
        else
        {
            cout << "Invalid input" << endl;
            cout << "You misplace 50 pounds of food" << endl;
            food = food - 50;
        }
        
    }
    bool Store::puzzle()//function used by hunt and raider functions
    {
        bool flag = false;//tracks if the number is correctly guessed
        string input = "";
        int number = randomNumbersStore(1, 5);//the number that the user is trying to guess
        cout << "To successfully complete the puzzle, you have to guess the secret number." << endl;
        cout << "The number is between 1 and 5 and you have 3 tries to correctly guess it." << endl;//switched to 1-5 to make the game easier
        for (int i = 1; i <= 3; i++)
        {
            cout << "Guess #" << i << ": " << endl;
            cin >> input;
            if (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")//checks for invalid input
            {
                cout << "Invalid input. You do not guess a number." << endl;
            
            }
            else if (stoi(input) == number)
            {
                flag = true;
            }
        }
        if (flag == true)
        {
            cout << "Congratulations! You guessed correctly! The magic number was " << number << endl;
        }
        else
        {
            cout << "You weren't able to guess correctly :(" << endl;
            cout << "The magic number was " << number << endl;
        }
        return flag;
    }
    void Store::raiders(int miles)
    {
        string decision = "";//tracks what the player decides to do
        int choice = 0;//player decision converted to an integer
        bool win = false;//tracks if the player wins the fight
        double raiderProbability = ((((pow(((miles / 100) - 4), 2) + 72) / (pow(((miles / 100) - 4), 2) + 12)) - 1) / 10) * 100; //probability of a raider attack ocurring expressed as a percentage
        int number = randomNumbersStore(0, 100);
        if (number < raiderProbability)//raider attack occurs
        {
            cout << "Riders ahead! They look hostile!" << endl;
            cout << "1. Run" << endl;
            cout << "2. Attack" << endl;
            cout << "3. Surrender" << endl;
            cin >> decision;
            if (decision != "1" && decision != "2" && decision != "3")
            {
                cout << "Invalid input. You choose to surrender." << endl;
                decision = "3";
            }
            choice = stoi(decision);
            if (choice == 1)//player decides to run
            {
                cout << "You escape. But in your hurry to flee you left 1 ox, 10 lbs. of food and 1 wagon wheel." << endl;
                food = food - 10;
                if (wheels != 0)//you can only lose a wheel if you have 1 to spare
                {
                    wheels = wheels - 1;
                }
                oxen = oxen - 1;
            }
            else if (choice == 2)//player decides to fight
            {
                cout << "You must complete a puzzle to win the fight." << endl;
                win = puzzle();
                if (win == true)//player completes puzzle and wins fight
                {
                    cout << "You won the battle! You get 50 pounds of food and 50 bullets." << endl;
                    bullets = bullets + 50;
                    food = food + 50;
                }
                else//puzzle fails puzzle and loses fight
                {
                    cout << "You lost the battle! You lose 50 pounds of food and 50 bullets." << endl;
                    bullets = bullets - 50;
                    food = food - 50;
                }
            }
            else if (choice == 3)//player decides to surrender
            {
                cout << "You surrendered. You lose a quarter of your money" << endl;
                money = money - (money/4);
            }
        }
        else// no attack occurs
        {
            return;
        }
    }