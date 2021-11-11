#include <iostream>
#include "Menu.h"
using namespace std;

int main()
{
    int userChoice;
    do{
        std::cout<<"[0] Quit\n[1] Run 1D Program\n";
        std::cin>>userChoice;

         switch(userChoice)
         {
            case 0:
                std::cout<<"fuck off then\n";
                return 0;

            case 1:
                std::cout<<"run 1D function here\n";
                break;
            /*case 2:
                std::cout<<"run 2D function here\n";
                break;

            case 3:
                std::cout<<"run 3D function here\n";
                break;
            case 4:
                std::cout<<"Load file\n";
                break;
            */



        }

    }while(userChoice!=0);
}

void Menu::displayMenu(){

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

int Menu::convertToBinary(){

    return 0;
}

char Menu::createRandomSeed(){

   //initialise variables
    int randSize= (rand() % 50) + 1;
    int loop = 0;
    int randomNumber;
    char seed[randSize];
    int iteration;
    


   do
   {
       //gets random number from 0 to randsize
        randomNumber = (rand() % randSize);
        //sets the array's data node for the random number to #
        seed[randomNumber] = '#';
        loop = (rand() % 4);
        iteration++;

    // checks if the loop should randomly end or if the array is full
   }while (loop != 1 || iteration >= randSize);

    return seed[randSize];
}
