#compiler
CC = g++

#flags
CFLAGS = -Wall -Wextra -Werror -g

all: Menu.cpp Menu.h
	-@$(CC) $(CFLAGS) Menu.cpp Menu.h Automaton.cpp Automaton.h helper.cpp helper.h -o AutomatonSimulation.out

clean:
	-@rm *.o *.out 2>/dev/null || true
