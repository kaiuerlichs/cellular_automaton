/**
 * FILE: Automaton.h
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file defines the Automaton superclass and related subclasses as well as their members and some related constants
 */



// Beginning of header guard
#ifndef AUTOMATON_H
#define AUTOMATON_H



// Define colour and symbol constants for output formatting
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define CYAN    "\033[36m"
#define SQUARE  "\u25A0 "

// Required includes and namespace
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Struct to store generation data for a 2D Automaton
 */
struct Generation2D {
    vector<vector<char>> generation;
    int width;
    int height;
    Generation2D(int pWidth, int pHeight) : width(pWidth), height(pHeight) {
        generation.assign(height, vector<char> (width, '0'));
    };
};

/**
 * @brief The Automaton class represents a generic automaton with some pre-defined methods and fields
 */
class Automaton {
    protected:
        int numberOfIterations;
        bool generationDone;
    public:
        virtual void runAutomaton() { };
        virtual void saveAutomaton(string filename) { (void) filename; };
        int getNumberOfIterations() { return numberOfIterations; }
        void setNumberOfIterations(int i) { numberOfIterations = i; }
};

/**
 * @brief The Automaton1D class represents a 1 dimensional automaton with type-specific field and methods
 */
class Automaton1D : public Automaton {
    private:
        // Type-specific fields
        int width;
        string seed;
        string rule;
        bool wrap;
        
        // 2D vector matrix to save automaton iterations
        vector<vector<char>> iter;
    public:
        // Method declarations
        void runAutomaton();
        void saveAutomaton(string filename);
        void saveAsPreset(string presetName);

        // Constructor
        Automaton1D(int width, int numberOfIterations, string seed, string rule, bool wrap);
        
};

/**
 * @brief The Automaton2D class implements a 2D Automaton and its members and functions, based of the Conway Game Of Life ruleset
 */
class Automaton2D : public Automaton {
    private:
        // Type specific fields
        int width;
        int height;
        int numberOfIterations;
        string seed;
        bool wrap;

        vector<Generation2D> iter;
    public:
        // Method declarations
        void runAutomaton();
        void saveAutomaton(string filename);

        // Constructor
        Automaton2D(int width, int height, int numberOfIterations, string seed, bool wrap);
};



// End of header guard
#endif