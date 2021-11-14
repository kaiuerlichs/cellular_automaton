/**
 * FILE: Automaton.cpp
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file include the implementation for classes and members outlined in Automaton.h
 */



// Required std includes and namespace setting
#include "Automaton.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;



/* AUTOMATON 1D IMPLEMENTATIONS */

/**
 * @brief Construct a new Automaton1D object
 * 
 * @param width The width of the 1D automaton
 * @param numberOfIterations The number of iterations (generations) to generate
 * @param seed The start value for the automaton
 * @param rule The ruleset by which a cell's value is decided each generation
 * @param wrap Whether the ends of the automaton are connected (true) or separated (false)
 */
Automaton1D::Automaton1D(int width, int numberOfIterations, string seed, string rule, bool wrap) {
    // Validate input parameters
    if(seed.length() <= 0 || width <= 0 || numberOfIterations <= 0 || rule.length() <= 0){
        throw invalid_argument("Any of the input parameters is less than 0");
    }
    if((int) seed.length() != width){
        throw invalid_argument("Seed width does not match Automaton width");
    }
    if((int) rule.length() != 8){
        throw invalid_argument("The rule is not an 8-bit binary number");
    }

    // Set fields to parameter values
    this->seed = seed;
    this->rule = rule;
    this->width = width;
    this->wrap = wrap;
    this->generationDone = false;
    this->numberOfIterations = numberOfIterations;

    // Initialise vector to correct size
    iter.assign(numberOfIterations+1, vector<char> (width, '-'));
}

/**
 * @brief Runs the 1D Automaton's generation based on the parameters specified at object creation
 */
void Automaton1D::runAutomaton(){
    // Load first generation (seed) into vector matrix
    for(int i = 0; i < width; i++){
        iter[0][i] = seed.at(i);
    }

    // Generate remaining generations
    for(int i = 1; i <= numberOfIterations; i++){
        for(int j = 0; j < width; j++){
            // Check state of left, center and right cell in previous generation
            char lstate;
            char cstate;
            char rstate;

            if(j == 0){
                if(wrap == false){
                    lstate = '0';
                }
                else{
                    lstate = iter[i-1][width-1];
                }
            } else {
                lstate = iter[i-1][j-1];
            }

            cstate = iter[i-1][j];

            if(j == width-1){
                rstate = '0';
            } else {
                rstate = iter[i-1][j+1];
            }

            // For each bit of the ruleset, check if it is the correct setting and apply the rule
            if(lstate == '1' && cstate == '1' && rstate == '1'){
                iter[i][j] = rule.at(0);
            }
            if(lstate == '1' && cstate == '1' && rstate == '0'){
                iter[i][j] = rule.at(1);
            }
            if(lstate == '1' && cstate == '0' && rstate == '1'){
                iter[i][j] = rule.at(2);
            }
            if(lstate == '1' && cstate == '0' && rstate == '0'){
                iter[i][j] = rule.at(3);
            }
            if(lstate == '0' && cstate == '1' && rstate == '1'){
                iter[i][j] = rule.at(4);
            }
            if(lstate == '0' && cstate == '1' && rstate == '0'){
                iter[i][j] = rule.at(5);
            }
            if(lstate == '0' && cstate == '0' && rstate == '1'){
                iter[i][j] = rule.at(6);
            }
            if(lstate == '0' && cstate == '0' && rstate == '0'){
                iter[i][j] = rule.at(7);
            }
        }
    }

    // Set the generation value to true
    generationDone = true;

    // Pretty-print the automaton to the console
    for(vector<char> v : iter){
        for (char c : v){
            if(c == '1'){
                cout << CYAN << SQUARE << RESET;
            }
            else{
                cout << BLACK << SQUARE << RESET;
            }
        }
        cout << "\n";
    }
}

/**
 * @brief Saves the 1D Automaton's output to a file
 * 
 * @param filename The file to save the automaton to
 */
void Automaton1D::saveAutomaton(string filename){
    // Check if automaton was created
    if(!generationDone){
        throw logic_error("Automaton must run before saving it");
    }

    // Check if file already exists
    ifstream in;
    in.open(filename);
    if(in){
        throw invalid_argument("File already exists");
    }
    
    // Attempt to create new file to write into
    in.close();
    ofstream out;
    out.open(filename);
    // Throw exception if file creation was not possible
    if(!out){
        throw runtime_error("File creation failed");
    }

    // Write to file
    for(vector<char> v : iter){
        for (char c : v){
            out << c << " ";
        }
        out << endl;
    }

    // Close output stream
    out.close();
}

/**
 * @brief Saves the Automaton's generation settings as a preset, so the user can run the same automaton again
 * 
 * @param presetName The name to store the preset under
 */
void Automaton1D::saveAsPreset(string presetName){
    string filename("Preset.txt");
    ofstream file_out;
     if (file_out.is_open())
    {
        file_out.open(filename, std::ios_base::app);
        file_out << presetName<<";"<<width<<";"<<numberOfIterations<<";"<<seed<<";"<<rule<<";"<<wrap << endl;
        cout << "saved" << endl;
    }
    else{
        cout<< "file failed to open"<<endl;
    }
    return;
}





/* AUTOMATON 2D IMPLEMENTATIONS */

Automaton2D::Automaton2D(int width, int height, int numberOfIterations, string seed, bool wrap){
    
}