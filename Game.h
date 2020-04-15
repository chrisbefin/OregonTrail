#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

using namespace std;

class Game
{
    public:
    Game();//constructor, loop which continues running until the game is over
    int travel();//calculates and returns number of miles travelled
    int rest();//returns number of days rested
    int getMiles();//returns distance travelled
    int getDays();//returns number of days
    void addDays(int);//adds inputted number of days to total
    void setDate();//determines start date
    string getDate();//prints the date as a string
    int nextMilestone();//returns the distance to the next milestone
    int getMilesToMilestone();//finds the distance to the next milestone
    
    private:
    int miles;//tracks miles travelled
    int days;//tracks how long the journey has taken, 03/01 is day 1
    vector<int> depths;//vector which holds the depths and miles of the river crossings and forts
    vector<int> distances;//vector which holds the distances of all the landmarks
    vector<string> milestones;//vector which hold the names of the milestones (both rivers and forts)    
    string holder[2];//array which temporarily holds depths and distances of milestones for reading file in
    int month;//the current month
    int day;//the current day within the current month
    int milestoneCounter;//counts how many milestones have been passed through
    
    
};

#endif