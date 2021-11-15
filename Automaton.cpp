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
#include "helper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

/* AUTOMATON IMPLEMENTATIONS */

/**
 * @brief Displays a text file version of an Automaton
 * 
 * @param filename The file to display
 */
void Automaton::displaySaveFile(string filename){
    // Check if file exists
    ifstream in;
    in.open(filename);
    if(!in){
        throw invalid_argument("File does not exist");
    }

    char c;
    while (in.get(c)) {
        if(c == '1'){
                cout << colour << SQUARE << RESET;
            }
        else if(c == '0'){
            cout << BLACK << SQUARE << RESET;
        }
        else if(c == '\n'){
            cout << endl;
        }
    }
    in.close();
}

// Set default colour to CYAN
string Automaton::colour = "\033[36m";



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
                cout << colour << SQUARE << RESET;
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
    string filename("preset.txt");

    // Open new file output stream
    ofstream file_out;
    file_out.open(filename, std::ios_base::app);

    // Check if stream creation was successful
    if (file_out.is_open()){
        // Write preset to file
        file_out << presetName<<";"<<width<<";"<<numberOfIterations<<";"<<seed<<";"<<rule<<";"<<wrap << endl;
    }
    // Throw exception otherwise
    else{
        throw runtime_error("Preset could not be saved");
    }
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

    if(!seed.empty()){
        // Add the first generation into the vector
        vector<string> tokens = strsplit(seed.c_str(), ' ');
        for(string s : tokens){
            try{
                int x = stoi(s.substr(0,s.find(",")));
                int y = stoi(s.substr(s.find(",")+1));

                if(x < 0 || x > width || y < 0 || y > height){
                    throw invalid_argument("Seed contains invalid coordinates");
                }

                iter[0].generation[x-1][y-1] = '1';
            }
            catch(exception& e){
                throw invalid_argument("Seed contains invalid characters");
            }
        }
    }
}

/**
 * @brief Runs the 2D Automaton's generation algorithm
 */
void Automaton2D::runAutomaton(){
    // Iterate through all generations
    for(int i = 1; i <= numberOfIterations; i++){
        // Create generation pointers
        Generation2D* previous = &iter[i-1];
        Generation2D* current = &iter[i];

        // Iterate over each cell in the new generation
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                // Create a counter of alive neighbour cells 
                int neighbourCells = 0;
                
                // Iterate over all surrounding cells
                for(int c = -1; c <= 1; c++){
                    for(int d = -1; d <= 1; d++){
                        // Skip the cell itself
                        if (c == 0 && d==0){
                            continue;
                        }

                        // Get coordinates to check
                        int x_check = x + c;
                        int y_check = y + d;

                        // Border checking (wrap or no-wrap)
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
                        
                        // Check if selected cell is alive
                        if(previous->generation[x_check][y_check] == '1'){
                            neighbourCells++;
                        }
                    }
                }

                // Set new state for current cell
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

    // Set generation as done
    generationDone = true;

    // Pretty-print each generation
    for(Generation2D g : iter){
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                char c = g.generation[x][y];

                if(c == '1'){
                    cout << colour << SQUARE << RESET;
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

/**
 * @brief Saves the output to a specified filename
 * 
 * @param filename The filename to store the output in 
 */
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