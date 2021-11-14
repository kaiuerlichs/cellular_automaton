/**
 * FILE: Menu.h
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file defines the Menu class and its members
 */



// Beginning of header guard
#ifndef MENU_H
#define MENU_H



// Required includes and namespace setting
#include <string>
using namespace std;

/**
 * @brief The Menu class controls the main control flow of the program
 */
class Menu{
    public:
        void displayMainMenu();
        int getUserChoice(int lowerBound, int upperBound);   
        string convertToBinary(int number, int numOfBits);
        int convertToDecimal(string number, int numOfBits);
        string createRandomSeed(int size);
};



// End of header guard
#endif