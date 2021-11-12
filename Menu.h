#ifndef MENU_H
#define MENU_H

class Menu{
    public:
        void displayMainMenu();
        int getUserChoice(int lowerBound, int upperBound);   
        char* convertToBinary(int number);
        char* createRandomSeed();
};

#endif