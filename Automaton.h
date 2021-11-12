#ifndef AUTOMATON_H
#define AUTOMATON_H


#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define CYAN    "\033[36m"
#define SQUARE  "\u25A0 "


#include <string>
#include <vector>
using namespace std;

// Generic class Automaton
class Automaton {
    protected:
        int numberOfIterations;
        bool generationDone;
    public:
        virtual void runAutomaton() { };
        virtual void saveAutomaton() { };
        int getNumberOfIterations() { return numberOfIterations; }
        void setNumberOfIterations(int i) { numberOfIterations = i; }
};

// Derived class Automaton1D
class Automaton1D : public Automaton {
    private:
        int width;
        string seed;
        string rule;
        bool wrap;
        
        vector<vector<char>> iter;

    public:
        void runAutomaton();
        void saveAutomaton();

        Automaton1D(int width, int numberOfIterations, string seed, string rule, bool wraps);
        
};

#endif