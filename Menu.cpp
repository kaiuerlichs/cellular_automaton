/**
 * FILE: Menu.cpp
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file include the implementation for classes and members outlined in Automaton.h
 */



// Required std includes and namespace setting
#include "Menu.h"
#include "Automaton.h"
#include "helper.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;



/**
 * @brief This is the main method of the Automaton program
 * 
 * @return int Success code
 */
int main()
{
    Menu menu;
    //menu.displayMainMenu();
    //cout << menu.convertToBinary(0,8);
    cout << menu.convertToDecimal(menu.convertToBinary(0,8), 8);
    cout << menu.convertToDecimal(menu.convertToBinary(43,8), 8);
}

/**
 * @brief This method displays the main menu
 */
void Menu::displayMainMenu(){
    int userChoice;
    do{
        std::cout<<"\n[0] Quit\n[1] Run 1D Program\n[2] Use Converters\n";
        userChoice = getUserChoice(0, 2);
        switch(userChoice) {
            case 0:
                std::cout<<"\n~~ Exiting ~~" << endl;
                userChoice = 0;
                break;
            case 1: { // {} to makevariables local to this case
                //get informations
                std::cout<<"\nPlease enter width:" << endl;
                int width = getUserChoice(1, 100);

                std::cout<<"\nPlease enter number of iterations:" << endl;
                int iterations = getUserChoice(1, 1000);

                std::cout<<"\nPlease enter rule:" << endl;
                string rule;
                cin >> rule;

                std::cout<<"\nShould automaton be wrapped [0]false [1]true:" << endl;
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
                    std::cout<<"\nPlease enter the seed (must be " << width << " long): " << endl;
                    seed = getUserChoice(0,INT32_MAX);
                } while((int)seed.length() != width);

                //run automaton
                Automaton1D automaton = Automaton1D(width, iterations, seed, rule, wrapped);
                automaton.runAutomaton();

                //saving
                std::cout<<"\nWould you like to save this output to a file?\n[0] No\n[1] Yes" << endl;
                int saveChoice = getUserChoice(0, 1);
                if(saveChoice == 1) {
                    std::cout<<"\n-- save to file --";
                }
                std::cout<<"\nWould you like to save this as a preset?\n[0] No\n[1] Yes" << endl;
                saveChoice = getUserChoice(0, 1);
                if(saveChoice == 1) {
                    std::cout<<"\n-- save as preset --";
                }
                break;
            }
            case 2: { // {} to makevariables local to this case
                std::cout<<"\nWhich way would you like to convert?\n[0] Binary->Decimal\n[1] Decimal->Binary" << endl;
                int convertChoice = getUserChoice(0, 1);
                if(convertChoice == 0) {
                    std::cout<<"\nEnter how many bits the binary number has" << endl;
                    int bits = getUserChoice(1, 64);
                    std::cout<<"\nEnter binary number you'd like to convert (maximum " << (pow(2, bits)) << ")" << endl;
                    int binary = getUserChoice(1, (pow(2, bits)));
                    cout << binary;
                    //cout << convertToDecimal(binary, bits);
                } else if (convertChoice == 1)
                {
                    std::cout<<"\nEnter how many bits you'd like to store this in" << endl;
                    int bits = getUserChoice(1, 64);
                    std::cout<<"\nEnter decimal number you'd like to convert (maximum " << (pow(2, bits)) << ")" << endl;
                    int decimal = getUserChoice(1, (pow(2, bits)));
                    cout << convertToBinary(decimal, bits);
                }
                break;
            }
            default:
                std::cout<<"\ninvalid";
                break;
        }
    } while(userChoice!=0);
}

/**
 * @brief Method prompts a user choice and returns the specified input
 * 
 * @param lowerBound The lower bound for the user input method
 * @param upperBound The upper bound for the user input method
 * @return int The user-specified input
 */
int Menu::getUserChoice(int lowerBound, int upperBound){
    string userChoice;
    int numericChoice;
    bool valid = false;

    while (!valid)
    {
        // Gets user input
        cout << "Enter a number between " << lowerBound << " and " << upperBound << ": ";
        cin >> userChoice;
        // Input validation
        try{
            numericChoice = stoi(userChoice);
        }
        catch(exception& e){
            cout<< "Your input was invalid. Try again."<< endl;
            continue;
        }
        if (numericChoice >= lowerBound && numericChoice <= upperBound){
            valid = true;
        }
        else{
            cout<< "Your input was invalid. Try again."<< endl;
        }
    }

    // Returns value
    return numericChoice;

}

/**
 * @brief Converts a decimal number to string representation of the decimal number
 * 
 * @param number The number to convert
 * @param numOfBits The number of bits
 * @return string Returns the binary as string
 */
string Menu::convertToBinary(int number, int numOfBits){
    //initialise arrays
    int remainderArray[numOfBits];
    //loop and set all values to 0
    for (int c = 0; c < numOfBits; c++) {
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
    int reverse = 0;
    for (int j = numOfBits-1; j >= 0; j--) {
        binaryArray[reverse] = '0' + remainderArray[j];
        reverse ++;
    }
    string strArray(binaryArray);
    return strArray.substr(0,numOfBits);
}

/**
 * @brief Converts a binary number into decimal
 * 
 * @param number The binary to convert
 * @param numOfBits The number of bits
 * @return int The decimal number
 */
int Menu::convertToDecimal(string number, int numOfBits){
    //initialise values
    int counter = 0;
    int decimal = 0;
    //loop through binary number right to left
    for(int i = numOfBits-1; i >= 0; i--) {
        //if 1 then add to total
        if(number[i] == '1') {
            decimal = decimal + (pow(2, counter));
        }
        counter++;
    }
    return decimal;
}

/**
 * @brief Create a random seed for the 1D array
 * 
 * @param Size The size for the random seed
 * @return string The random seed
 */
string Menu::createRandomSeed(int Size){
    // Set random seed to time value
    srand(time(0));

   // Initialise variables
    int loop = 0;
    int randomNumber;
    char seed[Size];
    int iteration;
    
    do
    {
        //gets random number from 0 to randsize
        randomNumber = (rand() % Size);
        //sets the array's data node for the random number to #
        seed[randomNumber] = '1';
        loop = (rand() % 4);
        iteration++;

    // checks if the loop should randomly end or if the array is full
    } while (loop != 1 || iteration <= Size);

    // Set all non-positive values to zero
    for (int i = 0; i < Size; i++)
    {
        if (seed[i] != '1')
        {
            seed[i] = '0';
        }
        
    }

    // Return the seed
    return seed;
}

/**
 * @brief Loads a preset for a 1D automaton
 */
void Menu::loadPreset(){
    // Check if file exists
    ifstream in;
    in.open("preset.txt");
    if(!in){
        cout << "No presets are currenly saved, or the preset.txt file was deleted." << endl;
        return;
    }

    cout << "Please select one of the presets below..." << endl;

    string str;
    int counter = 1;
    while (in >> str)
    {
        vector<string> tokens = strsplit(str.c_str(),';');
        cout << "[" << counter << "]" << " " << tokens[0] << endl;
        counter++;
    }

    int selection = getUserChoice(1,counter-1);

    in.clear();
    in.seekg (0, ios::beg);

    string preset;
    for(int i =0; i < selection; i++){
        in >> preset;
    }

    in.close();

    vector<string> params = strsplit(preset.c_str(),';');
    
    int width = stoi(params[1]);
    int numberOfIterations = stoi(params[2]);
    string seed = params[3];
    string rule = params[4];
    bool wrap;
    if(params[5] == "true"){
        wrap = true;
    }
    else{
        wrap = false;
    }

    run1DAutomaton(width, numberOfIterations, seed, rule, wrap);
}

/**
 * @brief Run a 1D automaton
 * 
 * @param width The width of the 1D automaton
 * @param numberOfIterations The number of iterations (generations) to generate
 * @param seed The start value for the automaton
 * @param rule The ruleset by which a cell's value is decided each generation
 * @param wrap Whether the ends of the automaton are connected (true) or separated (false)
 */
void Menu::run1DAutomaton(int width, int numberOfIterations, string seed, string rule, bool wrap){
    // Create automaton
    Automaton1D automaton(width,numberOfIterations,seed,rule,wrap);
    
    // Attempt to run automaton
    cout << "Displaying automaton generations below...\n" << endl;
    try{
        automaton.runAutomaton();
    }
    catch(exception& e){
        cout << "The Automaton simulation returned an error message: " << e.what() << endl;
        return;
    }
    cout << endl;

    // Ask if user wants to save the output
    cout << "Do you want to save the output to a text file? [0] yes [1] no" << endl;
    int textSave = getUserChoice(0,1);

    // If the user confirms
    if(textSave == 0){
        cout << "Please enter the name of your text file: ";
        
        // Read in file name
        string filename;
        cin >> filename;

        try{
            automaton.saveAutomaton(filename);
        }
        catch(exception& e){
            cout << "Saving the automaton returned an error message: " << e.what() << endl;
        }
    }

    // Ask if the user wants to save the preset
    cout << "Do you want to save this automaton as a preset? [0] yes [1] no" << endl;
    int presetSave = getUserChoice(0,1);

    // If the user confirms
    if(presetSave == 0){
        cout << "Please enter the name of your preset: ";

        // Read in preset name
        string presetname;
        cin >> presetname;

        try{
            automaton.saveAsPreset(presetname);
        }
        catch(exception& e){
            cout << "Saving the preset returned an error message: " << e.what() << endl;
        }
    }
    cout << endl;
}

/**
 * @brief Creates and runs a 2D Automaton
 * 
 * @param width The width of the map
 * @param height The height of the map
 * @param numberOfIterations The number of iterations (generations) to produce
 * @param seed The seed for the automaton
 */
void Menu::run2DAutomaton(int width, int height, int numberOfIterations, string seed){
    bool wrap = false;

    // Create automaton
    Automaton2D automaton(width,height,numberOfIterations,seed,wrap);
    
    // Attempt to run automaton
    cout << "Displaying automaton generations below...\n" << endl;
    try{
        automaton.runAutomaton();
    }
    catch(exception& e){
        cout << "The Automaton simulation returned an error message: " << e.what() << endl;
        return;
    }
    cout << endl;

    // Ask if user wants to save the output
    cout << "Do you want to save the output to a text file? [0] yes [1] no" << endl;
    int textSave = getUserChoice(0,1);

    // If the user confirms
    if(textSave == 0){
        cout << "Please enter the name of your text file: ";
        
        // Read in file name
        string filename;
        cin >> filename;

        try{
            automaton.saveAutomaton(filename);
        }
        catch(exception& e){
            cout << "Saving the automaton returned an error message: " << e.what() << endl;
        }
    }
    cout << endl;
}

/**
 * @brief Creates and runs a 2D Automaton in 3D (wrapped) mode (torus shape)
 * 
 * @param width The width of the map
 * @param height The height of the map
 * @param numberOfIterations The number of iterations (generations) to produce
 * @param seed The seed for the automaton
 */
void Menu::run3DAutomaton(int width, int height, int numberOfIterations, string seed){
    bool wrap = true;

    // Create automaton
    Automaton2D automaton(width,height,numberOfIterations,seed,wrap);
    
    // Attempt to run automaton
    cout << "Displaying automaton generations below...\n" << endl;
    try{
        automaton.runAutomaton();
    }
    catch(exception& e){
        cout << "The Automaton simulation returned an error message: " << e.what() << endl;
        return;
    }
    cout << endl;

    // Ask if user wants to save the output
    cout << "Do you want to save the output to a text file? [0] yes [1] no" << endl;
    int textSave = getUserChoice(0,1);

    // If the user confirms
    if(textSave == 0){
        cout << "Please enter the name of your text file: ";
        
        // Read in file name
        string filename;
        cin >> filename;

        try{
            automaton.saveAutomaton(filename);
        }
        catch(exception& e){
            cout << "Saving the automaton returned an error message: " << e.what() << endl;
        }
    }
    cout << endl;
}