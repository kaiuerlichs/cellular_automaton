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



// Required includes, defines and namespace setting
#define RESET   "\033[0m"
#define CYAN    "\033[36m"

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
        void loadPreset();
        void loadSaveFile();
        void run1DAutomaton(int width, int numberOfIterations, string seed, string rule, bool wrap);
        void run2DAutomaton(int width, int height, int numberOfIterations, string seed);
        void run3DAutomaton(int width, int height, int numberOfIterations, string seed);
};



// End of header guard
#endif