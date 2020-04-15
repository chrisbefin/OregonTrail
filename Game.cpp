#include "Game.h"

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

    int randomNumbersGame(int min, int max)//helper function, returns number between two given bounds
    {
    // rand() % (max-min+1) + min
    return (rand() % (max-min+1)) + min;
    }
    int split (string str, char c, string array[], int size)//helper split function for reading in files
    {
    if (str.length() == 0) 
    {
         return 0;
    }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
                
            array[count++] = word;
            word = "";
        } 
        else 
        {
            word = word + str[i];
        }
    }
    return count;
}
    Game::Game()//constructor
    {
        miles = 0;
        days = 28;//if default date is chosen
        month = 3;//if default date is chosen
        day = 28;
        milestoneCounter = 0;
        ifstream myStream("milestones.txt");
        string line;
        int lineCounter = 0;
        while (getline(myStream, line))//reads milestones.txt into vectors
        {
            if ((lineCounter + 1) % 2 != 0)//if line number is odd
            {
                milestones.push_back(line);
            }
            else//line number is even
            {
                split(line, ' ', holder, 3);
                distances.push_back(stoi(holder[0]));// first substring is the distance
                depths.push_back(stoi(holder[1]));//second substrign is the depth of the milestone
            }
            lineCounter++;
        }
    }
    int Game::travel()//calculates and returns if a river, fort or nothing was hit
    {
        int type = 0;// 0 if you hit nothing, 1 if you hit fort, 2 if you hit river
        int distance = 0;
        days = days + 14;//travelling lasts 2 weeks
        distance = randomNumbersGame(70, 140);
        if (distance > getMilesToMilestone())//you can only go as far as the next milestone
        {
            distance = getMilesToMilestone();
            cout << "You have arrived at " << milestones[0] << endl;
            if (depths[0] == 0)//forts have a depth of zero
            {
                type = 1;
            }
            else //rivers have a non-zero depth
            {
                type = 2;
            }
            milestones.erase(milestones.begin());// once you hit a given milestone, it can be erased from the vector
            distances.erase(distances.begin());//this way the next milestone is always in the 0th index
            depths.erase(depths.begin());
        }
        miles = miles + distance;//travel between 70 and 140 miles each turn
        return type;
    }
    int Game::rest()//returns number of days rested
    {   
        int rest;
        rest = randomNumbersGame(1,3);
        cout << "You have rested " << rest << " days" << endl;
        days = days + rest;
        return rest;
    }
    int Game::getMiles()
    {
        return miles;
    }
    int Game::getDays()
    {
        return days;
    }
    void Game::addDays(int number)
    {
        days = days + number;
    }
    void Game::setDate()
    {
        string response;
        int number;
        cout << "Would you like to use the default start date of 03-28-1847?(Y/N)" << endl;
        cin >> response;
        if (response == "Y" || response == "y")//default departure date is chosen
        {
            cout << "Okey Dokey, March 28th it is. Have a nice trip!" << endl;
            return;
        }
        else if (response == "N" || response == "n")
        {
            cout << "Which month would you like to leave?(3/4)" << endl;
            cin >> response;
            if (response != "3" && response != "4")//checks for invalid input
            {
                cout << "Invalid input. Looks like somebody can't follow directions" << endl;
                cout << "You can just leave on March 28th" << endl;
                return;
            }
            else
            {
                number = stoi(response);//if they enter a valid input, that becomes the departure month
                month = number;
            }
            cout << "Which day would you like to leave?" << endl;
            string input;
            cin >> input;
            if (input[0] < 49 || input[0] > 57)//checks for invalid input- first number must be between 0-3
            {
                cout << "Invalid input. Looks like somebody can't follow directions" << endl;
                cout << "You can just leave on March 28th" << endl;
                return;
            }
            number = stoi(input);
            if (month == 3 && number <= 31 && number != 0)
            {
                day = number;//if it is a valid input, it becomes the departure day
                
            }
            else if (month == 4 && number <= 30 && number != 0)
            {
                day = number;//if it is a valid input, it becomes the departure day
                
            }
            else
            {
                cout << "Invalid input. Looks like somebody can't follow directions" << endl;
                cout << "You can just leave on March 28th" << endl;
                return;
            }
            if (month == 3)//alters total number of days depending on selected departure day
            {
                days = day;
                return;
            }
            if (month == 4)//if the player decides to leave in april, the total number of days increases by 31
            {
                days = day + 31;
                return;
            }
        }
        else
        {
            cout << "Invalid input. Looks like somebody can't follow directions" << endl;
            cout << "You can just leave on March 28th" << endl;
            return;
        }
    }
    string Game::getDate()
    {
        if (days > 0 && days <= 30)//if total days is less than 30, month is march
        {
            month = 3;
            day = days;
        }
        if (days > 31 && days <= 61)//days range for april
        {
            month = 4;
            day = days - 31;
        }
        if (days > 61 && days <= 92)//days range for may
        {
            month = 5;
            day = days - 61;
        }
        if (days > 92 && days <= 122)//days range for june
        {
            month = 6;
            day = days - 92;
        }
        if (days > 122 && days <= 153)//days range for july
        {
            month = 7;
            day = days - 122;
        }
        if (days > 153 && days <= 184)//days range for august
        {
            month = 8;
            day = days - 153;
        }
        if (days > 184 && days <= 204)//days range for september
        {
            month = 9;
            day = days - 184;
        }
        if (days > 204 && days <= 235)//days range for october
        {
            month = 10;
            day = days - 204;
        }
        if (days > 235 && days <= 265)//day ranges for november
        {
            month = 11;
            day = days - 235;
        }
        string date = "";
        cout << month << "/" << day << "/" << "1847";//prints the date in proper format
        return "";
    }
    int Game::getMilesToMilestone()//calculates the distance to the next milestone
    {
        int distance = 0;
        distance = distances[0] - miles;//the next value in the distances vector is the distance of the nearest milestone
        return distance;//distance to next milestone is difference between miles travelled and next value in distances array
    }