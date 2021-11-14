#ifndef MENU_H
#define MENU_H

class Menu{
    public:
        void displayMainMenu();
        int getUserChoice(int lowerBound, int upperBound);   
        char* convertToBinary(int number, int numOfBits);
        int convertToDecimal(char number[], int numOfBits);
        char* createRandomSeed(int size);
};

#endif