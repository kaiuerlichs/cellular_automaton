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
using namespace std;



/* Support functions */

/**
 * @brief A function to tokenize a string based on a delimiter and return a corresponding vector
 * 
 * @param str The string to tokenize
 * @param c The delimter character
 * @return vector<string> A vector of string tokens
 * 
 * @authors https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
 * @note Comments added by group members
 */
vector<string> strsplit(const char *str, char c = ' '){
    // A vector to hold the tokens
    vector<string> result;

    // Iterate over string and push-back when delimiter found
    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    // Return the results
    return result;
}



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
        throw invalid_argument("One or more input parameters are less than or equal to zero");
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
    return;
}



/* AUTOMATON 2D IMPLEMENTATIONS */

/**
 * @brief Construct a new Automaton 2D object
 * 
 * @param width The width of each generation
 * @param height The height of each generation
 * @param numberOfIterations The nu,ber of iteratiosn for the program (number of new generations)
 * @param seed The seed for the 2D automaton, in form "x1,y1 x2,y2 x3,y3"
 * @param wrap Whether the automaton wraps into a 3D taurus or not
 */
Automaton2D::Automaton2D(int width, int height, int numberOfIterations, string seed, bool wrap){
    // Validate input parameters
    if(width <= 0 || height <= 0 || numberOfIterations <= 0){
        throw invalid_argument("One or more input parameters are less than or equal to zero");
    }

    // Set field values
    this->width = width;
    this->height = height;
    this->numberOfIterations = numberOfIterations;
    this->seed = seed;
    this->wrap = wrap;
    
    // Initialise iter vector and Generation structs
    iter.assign(numberOfIterations+1, Generation2D(width, height));

    // Add the first generation into the vector
    vector<string> tokens = strsplit(seed.c_str(), ' ');
    for(string s : tokens){
        int x = stoi(s.substr(0,s.find(",")));
        int y = stoi(s.substr(s.find(",")+1));

        if(x < 0 || x > width || y < 0 || y > height){
            throw invalid_argument("Seed contains invalid coordinates");
        }

        iter[0].generation[x-1][y-1] = '1';
    }
}

/**
 * @brief Runs the 2D Automaton's generation algorithm
 */
void Automaton2D::runAutomaton(){
    for(int i = 1; i <= numberOfIterations; i++){
        Generation2D* previous = &iter[i-1];
        Generation2D* current = &iter[i];

        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                int neighbourCells = 0;
                
                for(int c = -1; c <= 1; c++){
                    for(int d = -1; d <= 1; d++){
                        if (c == 0 && d==0){
                            continue;
                        }

                        int x_check = x + c;
                        int y_check = y + d;

                        if (x_check < 0){
                            if(!wrap) continue;
                            x_check = width-1;
                        }
                        if(x_check >= width){
                            if(!wrap) continue;
                            x_check = 0;
                        }
                        if (y_check < 0){
                            if(!wrap) continue;
                            y_check = height-1;
                        }
                        if(y_check >= height){
                            if(!wrap) continue;
                            y_check = 0;
                        }
                        
                        if(previous->generation[x_check][y_check] == '1'){
                            neighbourCells++;
                        }
                    }
                }

                if(previous->generation[x][y] == '1'){
                    if(neighbourCells == 2 || neighbourCells == 3){
                        current->generation[x][y] = '1';
                    }
                    else{
                        current->generation[x][y] = '0';
                    }
                }
                else{
                    if(neighbourCells == 3){
                        current->generation[x][y] = '1';
                    }
                    else{
                        current->generation[x][y] = '0';
                    }
                }
            }
        }
    }

    generationDone = true;

    for(Generation2D g : iter){
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                char c = g.generation[x][y];

                if(c == '1'){
                    cout << CYAN << SQUARE << RESET;
                }
                else{
                    cout << BLACK << SQUARE << RESET;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Automaton2D::saveAutomaton(string filename){
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

    // Loop through all generations and their matrices to write them into the file
    for(Generation2D g : iter){
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                char c = g.generation[x][y];

                out << c << " ";
            }
            out << endl;
        }
        out << endl;
    }

    // Close output stream
    out.close();
}
