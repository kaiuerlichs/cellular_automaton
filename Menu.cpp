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
    menu.displayMainMenu();
}

/**
 * @brief This method displays the main menu
 */
void Menu::displayMainMenu(){
    int userChoice;
    do{
        cout << CYAN << "~~ Automaton Simulation ~~" << RESET << endl;

        cout << "\n[0] Quit" << endl; 
        cout << "[1] Create 1D Automaton" << endl;
        cout << "[2] Create Conway's Game of Life (2D plane)" << endl;
        cout << "[3] Create Conway's Game of Life (3D torus)" << endl;
        cout << "[4] Load 1D Automaton from preset" << endl;
        cout << "[5] Display automaton output file" << endl;
        cout << "[6] Binary - decimal conversion\n" << endl;

        userChoice = getUserChoice(0, 6);
        switch(userChoice) {
            // Quit
            case 0:
                cout<<"\n~~ Exiting ~~" << endl;
                userChoice = 0;
                break;

            // Create 1D Automaton
            case 1: { 
                // Get width from user
                cout<<"\nPlease enter width..." << endl;
                int width = getUserChoice(1, 100);

                // Get iteration count from user
                cout<<"\nPlease enter number of iterations..." << endl;
                int iterations = getUserChoice(1, 1000);

                // Random or user rule?
                string rule;
                cout<<"\nAutomaton rule: [0] User-specified [1] Random" << endl;
                int randomRule = getUserChoice(0, 1);
                if(randomRule == 0){
                    // Get rule from user
                    cout<<"\nPlease enter the rule (8-bit binary or decimal between 0 and 255 inclusive)..." << endl;
                    cin >> rule;

                    // Validate rule input
                    try{
                        int ruleNum = stoi(rule);
                        if (ruleNum >= 0 && ruleNum < 256){
                            rule = convertToBinary(ruleNum, 8);
                        }
                        else{
                            if((int) rule.length() != 8){
                                    throw invalid_argument("Rule is not 8 bit");
                                }
                            for(int i = 0; i < (int) rule.length(); i++){
                                if(!(rule.at(i) == '1' || rule.at(i) == '0')){
                                    throw invalid_argument("Rule is not binary");
                                }
                            }
                        }
                    }
                    catch(invalid_argument& e1){
                        cout << "\nThe rule entered is not valid." << endl;
                        break;
                    }
                }
                else{
                    rule = createRandomSeed(8);
                    cout << "Random rule generated: " << rule << endl;
                }

                // Random or user seed?
                string seed;
                cout<<"\nAutomaton seed: [0] User-specified [1] Random" << endl;
                int randomSeed = getUserChoice(0, 1);
                if(randomSeed == 0){
                    // Get seed from user
                    cout<<"\nPlease enter the seed (" << width << "-bit binary)..." << endl;
                    cin >> seed;

                    // Validate seed input
                    try{
                        if((int) seed.length() != width){
                                throw invalid_argument("Seed is invalid bit length");
                            }
                        for(int i = 0; i < (int) seed.length(); i++){
                            if(!(seed.at(i) == '1' || seed.at(i) == '0')){
                                throw invalid_argument("Seed is not binary");
                            }
                        }
                    }
                    catch(invalid_argument& e1){
                        cout << "\nThe seed entered is not valid." << endl;
                        break;
                    }
                }
                else{
                    seed = createRandomSeed(width);
                    cout << "Random seed generated: " << seed << endl;
                }

                // Get wrap state
                bool wrap;
                cout<<"\nWrap automaton bounds [0] No [1] Yes" << endl;
                int wrapInput = getUserChoice(0, 1);
                
                if(wrapInput == 0){
                    wrap = false;
                }
                else{
                    wrap = true;
                }

                // Run automaton
                run1DAutomaton(width,iterations,seed,rule,wrap);
                break;
            }

            // Create 2D Automaton
            case 2: { 
                // Get width from user
                cout<<"\nPlease enter width..." << endl;
                int width = getUserChoice(1, 100);

                // Get height from user
                cout<<"\nPlease enter height..." << endl;
                int height = getUserChoice(1, 100);

                // Get iteration count from user
                cout<<"\nPlease enter number of iterations..." << endl;
                int iterations = getUserChoice(1, 1000);

                string seed;
                cout<<"\nPlease enter the seed in coordinate form..." << endl;
                cout<<"\nExample seed: 3,3 3,4 3,5" << endl;

                cin.ignore(1000, '\n');
                getline(cin,seed);

                run2DAutomaton(width,height,iterations,seed);
                break;
            }

            // Create 3D Automaton
            case 3: {
                // Get width from user
                cout<<"\nPlease enter width..." << endl;
                int width = getUserChoice(1, 100);

                // Get height from user
                cout<<"\nPlease enter height..." << endl;
                int height = getUserChoice(1, 100);

                // Get iteration count from user
                cout<<"\nPlease enter number of iterations..." << endl;
                int iterations = getUserChoice(1, 1000);

                string seed;
                cout<<"\nPlease enter the seed in coordinate form..." << endl;
                cout<<"\nExample seed: 3,3 3,4 3,5" << endl;

                cin.ignore(1000, '\n');
                getline(cin,seed);

                run3DAutomaton(width,height,iterations,seed);
                break;
            }

            // Load 1D Automaton from preset
            case 4: {
                loadPreset();
                break;
            }

            // Display automaton output file
            case 5: {
                break;
            }

            // Binary - decimal conversion
            case 6: {
                break;
            }

            // Default case (failsafe only)
            default:
                cout<<"\nThe input received is invalid" << endl;
                break;
        }
        cout << endl;
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
    string strseed(seed);
    return strseed.substr(0,Size);
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
    // prints the names of the presets
    string str;
    int counter = 1;
    while (in >> str)
    {
        vector<string> tokens = strsplit(str.c_str(),';');
        cout << "[" << counter << "]" << " " << tokens[0] << endl;
        counter++;
    }


    int selection = getUserChoice(1,counter-1);

    // clears and begins the file loop
    in.clear();
    in.seekg (0, ios::beg);

    // gets user input for name of preset
    string preset;
    for(int i =0; i < selection; i++){
        in >> preset;
    }

    in.close();
    //splits the line from file
    vector<string> params = strsplit(preset.c_str(),';');
    // sets variables to file values
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
    //passes variables to function for running
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
    cout << "\nDo you want to save this automaton as a preset? [0] yes [1] no" << endl;
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
    
    // Attempt to run automaton
    cout << "Displaying automaton generations below...\n" << endl;
    try{
        Automaton2D automaton(width,height,numberOfIterations,seed,wrap);
        automaton.runAutomaton();

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
    }
    catch(exception& e){
        cout << "The Automaton simulation returned an error message: " << e.what() << endl;
        return;
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