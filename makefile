CC = gcc -Wall -Wextra -std=c99
O = obj/
C = src/
H = headers/
B = bin/

durableverse : $(C)main.c $(O)card.o $(O)structure.o $(O)interface.o $(O)board.o
	$(CC) $< -o $@ -g 

structure.o : $(S)structure.c
	$(CC) -c $< -o $@ -g

card.o : $(S)card.c $(O)structure.o $(O)interface.o $(O)board.o
	$(CC) -c $< -o $@ -g

board.o : $(S)board.c $(O)structure.o
	$(CC) -c $< -o $@ -g

interface.o : $(S)interface.c $(O)board.o $(O)structure.o $(O)card.o
	$(CC) -c $< -o $@ -g


clean : 
	rm -vf $(B)* $(O)* 

re :
	clear; make clean; make durableverse