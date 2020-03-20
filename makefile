CC = gcc -Wall -Wextra -std=c99
O = obj/
C = src/
H = headers/
B = bin/

durableverse : $(C)main.c $(O)card.o $(O)structure.o $(O)interface.o $(O)board.o
	$(CC) $< -o $@ -g 

card.o : $(S)card.c $(H)card.h $(O)structure.o $(O)interface.o $(O)board.o
	$(CC) -c $< -o $@ -g

structure.o : $(S)structure.c $(H)structure.h
	$(CC) -c $< -o $@ -g

interface.o : $(S)interface.c $(H)interface.h $(O)board.o $(O)structure.o $(O)card.o
	$(CC) -c $< -o $@ -g


clean : 
	rm -vf $(B)* $(O)* 

re :
	clear; make clean; make durableverse