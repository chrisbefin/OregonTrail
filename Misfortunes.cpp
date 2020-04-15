#include "Misfortunes.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
    
    int randomNumbersMisfortunes(int min, int max)//helper function, returns number between two given bounds
    {
    return (rand() % (max-min+1)) + min;
    }
    Misfortunes::Misfortunes()
    {
        //nothing needs to be initialized in constructor since there are no private data members for this class
    }
    int Misfortunes::misfortunePick()//the number returned indicates which misfortune occured
    {
        //0-nothing occurs, 1-wheel breaks, 2- illness, 3- ox dies
        bool flag = false;//if flag is true, a misfortune is chosen at random
        int number = randomNumbersMisfortunes(0, 100);
        if (number <= 40)
        {
            flag = true;
        }
        if (flag == true)
        {
            number = randomNumbersMisfortunes(1,3);
            return number;
        }
        return number;
    }