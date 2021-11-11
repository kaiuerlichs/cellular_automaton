#ifndef AUTOMATON_H
#define AUTOMATON_H

class Automaton {
    public:
        void runGeneration();
        void saveGeneration();
};

class Automaton1D : public Automaton {
    private:
        
    public:
        void runGeneration();
        void saveGeneration();
        Automaton1D(int width, int number_of_iterations, int seed, int rule);
};

class Automaton2D : public Automaton {
    private:

    public:
        void runGeneration();
        void saveGeneration();
        Automaton2D(int width, int number_of_iterations, int seed, int rule);
};

#endif