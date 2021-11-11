#compiler
CC = g++

#flags
CFLAGS = -Wall -Wextra -Werror -g

all: Menu.cpp Menu.h
	$(CC) $(CFLAGS) Menu.cpp Menu.h Generation1D.cpp Generation1D.h -o program.out

clean:
	-@rm *.o *.out 2>/dev/null || true
