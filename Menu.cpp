#include "Menu.h"
#include "Automaton.h"
#include <iostream>
using namespace std;

int main()
{
    Menu menu;
    menu.displayMainMenu();
}

void Menu::displayMainMenu(){
    int userChoice;
    do{
        std::cout<<"[0] Quit\n[1] Run 1D Program\n[2] Use Convertersn";
        userChoice = getUserChoice(0, 1);
        switch(userChoice) {
            case 0:
                std::cout<<"~~ Exiting ~~" << endl;
                userChoice = 0;
                break;
            case 1: { // {} to makevariables local to this case
                //get informations
                std::cout<<"Please enter width:" << endl;
                int width = getUserChoice(1, 100);

                std::cout<<"Please enter number of iterations:" << endl;
                int iterations = getUserChoice(1, 1000);

                std::cout<<"Please enter rule:" << endl;
                string rule;
                cin >> rule;

                std::cout<<"Should automaton be wrapped [0]false [1]true:" << endl;
                int wrappedChoice = getUserChoice(0, 1);
                bool wrapped;
                if(wrappedChoice == 1) {
                    wrapped = true;
                } else
                {
                    wrapped = false;
                }
                
                string seed;
                do {
                    std::cout<<"Please enter the seed (must be " << width << " long: " << endl;
                } while((int)seed.length() != width);

                //run automaton
                Automaton1D automaton = Automaton1D(width, iterations, seed, rule, wrapped);
                automaton.runAutomaton();

                //saving
                std::cout<<"Would you like to save this output to a file?\n[0] No [1] Yes" << endl;
                int saveChoice = getUserChoice(0, 1);
                if(saveChoice == 1) {
                    std::cout<<"-- save to file --";
                }
                std::cout<<"Would you like to save this as a preset?\n[0] No [1] Yes" << endl;
                saveChoice = getUserChoice(0, 1);
                if(saveChoice == 1) {
                    std::cout<<"-- save as preset --";
                }
                break;
            }
            case 2: { // {} to makevariables local to this case
                std::cout<<"Which way would you like to convert?\n[0] Binary->Decimal [1] Decimal->Binary" << endl;
                int convertChoice = getUserChoice(0, 1);
                if(convertChoice == 1) {
                    std::cout<<"-- binary conv --";
                } else if (convertChoice == 2)
                {
                    std::cout<<"Enter how many bits you'd like to store this in" << endl;
                    int bits = getUserChoice(1, 64);
                    std::cout<<"Enter decimal number you'd like to convert (maximum " << (2^bits) << endl;
                    int decimal = getUserChoice(1, (2^bits));
                    convertToBinary(bits, decimal);
                }
                break;
            }
            default:
                std::cout<<"invalid";
                break;
        }
    }while(userChoice!=0);
}



int Menu::getUserChoice(int lowerBound, int upperBound){
    int userChoice;
    bool valid = true;

    while (valid)
    {
        // gets user input
        cout <<"please enter a number between: "<< lowerBound << "and "<< upperBound<< ": ";
        cin >> userChoice;
        //input validation
        if (userChoice >= lowerBound && userChoice <= upperBound)
        {
            valid = false;
        }
        else{
            cout<< "please enter a valid choice"<< endl;
        }

    }

    //returns value
    return userChoice;

}

string Menu::convertToBinary(int number, int numOfBits){
    //initialise arrays
    int remainderArray[numOfBits];
    //loop and set all values to 0
    for (int c = 0; c < numOfBits-1; c++) {
        remainderArray[c] = 0;
    }
    char binaryArray[numOfBits];

    //convert to binary
    int i = 0;
    while (number > 0) {
        remainderArray[i] = number % 2;
        number = number / 2;
        i ++;
    }
    //convert int -> char
    for (int j = numOfBits-1; j >= 0; j--) {
        binaryArray[j] = '0' + remainderArray[j];
    }
    return binaryArray;
}

int Menu::convertToDecimal(char number[], int numOfBits){
    
    //initialise values
    int counter = 0;
    int decimal = 0;
    //loop through binary number right to left
    for(int i = numOfBits-1; i >= 0; i--) {
        //if 1 then add to total
        if(number[i] == '1') {
            decimal = decimal + (2^counter);
        }
        counter++;
    }
    return decimal;
}

string Menu::createRandomSeed(int Size){
   //initialise variables
    
    int loop = 0;
    int randomNumber;
    char seed[Size];
    int iteration;
    // get random number between 0 and 256
    // turn intop binary and return it
   do
   {
       //gets random number from 0 to randsize
        randomNumber = (rand() % Size);
        //sets the array's data node for the random number to #
        seed[randomNumber] = '1';
        loop = (rand() % 4);
        iteration++;

    // checks if the loop should randomly end or if the array is full
   }while (loop != 1 || iteration >= Size);

   for (int i = 0; i < Size; i++)
   {
       if (seed[i] != '1')
       {
           seed[i] = '0';
       }
       
   }
    return seed;
}

  


