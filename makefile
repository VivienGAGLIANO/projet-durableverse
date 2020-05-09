CC = gcc -Wall -Wextra -std=c99 -g
O = obj/
S = src/
H = headers/
B = bin/
L = lib/

durableverse : main.c $(O)card.o $(O)structure.o $(O)interface.o $(O)board.o $(O)stack.o $(L)ezxml/ezxml.o
	[ -d bin ] || mkdir bin
	$(CC) $^ -o $(B)$@

run: durableverse
	bin/durableverse

debug: durableverse
	gdb bin/durableverse

structure.o : $(O)structure.o

card.o : $(O)card.o

board.o : $(O)board.o

interface.o : $(O)interface.o

stack.o : $(O)stack.o

$(O)stack.o : $(L)stack/stack.c $(L)stack/stack.h obj
	$(CC) -c $< -o $@

$(O)interface.o : $(S)interface.c $(H)interface.h $(H)colors_logo.h obj
	$(CC) -c $< -o $@

$(O)%.o : $(S)%.c $(H)%.h obj
	$(CC) -c $< -o $@

obj:
	[ -d obj ] || mkdir obj

clean : 
	rm -vf $(B)* $(O)* 

re :
	clear; make clean; make durableverse