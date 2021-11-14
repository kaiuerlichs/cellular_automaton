#ifndef MENU_H
#define MENU_H

#include <string>
using namespace std;

class Menu{
    public:
        void displayMainMenu();
        int getUserChoice(int lowerBound, int upperBound);   
        string convertToBinary(int number, int numOfBits);
        int convertToDecimal(char number[], int numOfBits);
        string createRandomSeed(int size);
};

#endif