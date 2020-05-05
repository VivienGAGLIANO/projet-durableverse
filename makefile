CC = gcc -Wall -Wextra -std=c99 -g
O = obj/
S = src/
H = headers/
B = bin/
L = lib/

durableverse : main.c card.o structure.o interface.o board.o stack.o $(L)ezxml/ezxml.o
	$(CC) $^ -o $(B)$@


structure.o : $(S)structure.c $(H)structure.h
	$(CC) -c $< -o $(O)$@

card.o : $(S)card.c $(H)card.h
	$(CC) -c $< -o $(O)$@

board.o : $(S)board.c $(H)board.h
	$(CC) -c $< -o $(O)$@

interface.o : $(S)interface.c $(H)interface.h
	$(CC) -c $< -o $(O)$@

stack.o : $(L)stack/stack.c $(L)stack/stack.h
	$(CC) -c $< -o $(O)$@

%.o : $(S)%.c $(H)%.h
	$(CC) -c $< -o $(O)$@


clean : 
	rm -vf $(B)* $(O)* 

re :
	clear; make clean; make durableverse