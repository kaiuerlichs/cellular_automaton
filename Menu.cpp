#include <iostream>
#include "Menu.h"
using namespace std;

int main()
{
    
}

void Menu::displayMainMenu(){
    int userChoice;
    do{
        std::cout<<"[0] Quit\n[1] Run 1D Program\n";
        userChoice = getUserChoice(0, 1);
         switch(userChoice)
         {
            case 0:
                std::cout<<"fuck off then\n";
                userChoice = 0;
            case 1:
                std::cout<<"Please enter width:";
                int width = getUserChoice(1, 100);
                std::cout<<"Please enter number of iterations:";
                int iterations = getUserChoice(1, 1000);
                std::cout<<"Please enter rule:";
                int width = getUserChoice(0, 256);
                std::cout<<"Should automaton be wrapped [0]false [1]true:";
                int width = getUserChoice(0, 1);
                //seed
                //colour

                break;
            // case 2:
            //     std::cout<<"run 2D function here\n";
            //     break;
            // case 3:
            //     std::cout<<"run 3D function here\n";
            //     break;
            // case 4:
            //     std::cout<<"Load file\n";
            //     break;
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

char* Menu::convertToBinary(int number){
    //initialise arrays
    int remainderArray[8] = {0,0,0,0,0,0,0,0};
    char binaryArray[8];

    //convert to binary
    int i = 0;
    while (number > 0) {
        remainderArray[i] = number % 2;
        number = number / 2;
        i ++;
    }
    //convert int -> char
    for (int j = 7; j >= 0; j--) {
        binaryArray[j] = '0' + remainderArray[j];
    }
    return binaryArray;//this is wrong!!
}

char* Menu::createRandomSeed(){


   //initialise variables
    int randSize= (rand() % 50) + 1;
    int loop = 0;
    int randomNumber;
    char seed[randSize];
    int iteration;
    


    // get random number between 0 and 256
    // turn intop binary and return it



   do
   {
       //gets random number from 0 to randsize
        randomNumber = (rand() % randSize);
        //sets the array's data node for the random number to #
        seed[randomNumber] = '1';
        loop = (rand() % 4);
        iteration++;

    // checks if the loop should randomly end or if the array is full
   }while (loop != 1 || iteration >= randSize);

    return seed;
}

  


