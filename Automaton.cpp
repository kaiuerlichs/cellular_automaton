#include "Automaton.h"
#include <iostream>
using namespace std;

// Automaton1D
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

void Automaton1D::runAutomaton(){
    // Load first generation (seed) into vector matrix
    for(int i = 0; i < width; i++){
        iter[0][i] = seed.at(i);
    }

    // Generate remaining generations
    for(int i = 1; i <= numberOfIterations; i++){
        for(int j = 0; j < width; j++){
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

    generationDone = true;

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

void Automaton1D::saveAutomaton(){
    return;
}

int main(){
    Automaton1D a1(31, 15, "0000000000000001000000000000000", "00011110" ,false);
    a1.runAutomaton();
    return 0;
}