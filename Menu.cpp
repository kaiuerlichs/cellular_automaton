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
           /* case 2:
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

int Menu::getUserChoice(0,0){

    return 0;
    
}

int Menu::convertToBinary(){

    return 0;
}

int Menu::createRandomSeed(){

    return 0;
}