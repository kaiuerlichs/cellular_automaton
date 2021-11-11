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
        cout <<"please enter a number between: "<< lowerBound << "and "<< upperBound<< ": ";
        cin >> userChoice;
        if (userChoice >= lowerBound && userChoice <= upperBound)
        {
            valid = false;
        }
        else{
            cout<< "please enter a valid choice"<< endl;
        }

    }



    return valid;

}

int Menu::convertToBinary(){

    return 0;
}

int Menu::createRandomSeed(){

   
    int randSize= (rand() % 50) + 1;
    int loop = 0;
    int randomNumber;  
    int seed[randSize];
    int iteration;


   do
   {
       
       seed[iteration] = (rand() % randSize) + 1;
       iteration++;
       loop = (rand() % 4);
   }
    while (loop != 1);
   
    


    return seed[randSize];
}
