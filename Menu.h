#ifndef MENU_H
#define MENU_H

class Menu{
    public:
        void displayMenu();
        int getUserChoice(int lowerBound, int upperBound);   
        int convertToBinary();
        int createRandomSeed();
};

#endif