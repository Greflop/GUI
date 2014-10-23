# Makefile with basic concepts
 
# Define compiler and options
CC=gcc
CFLAGS= -Wall -Wextra -std=c99 `pkg-config --cflags --libs gtk+-2.0`
 
# avoid calling make without target
# ONLY FOR THIS EXERCICE
all:
	@echo "*** NO DEFAULT RULES ***"
	@false
 
clean::
	rm -f *~ *.o
 
# END (do not delete)
