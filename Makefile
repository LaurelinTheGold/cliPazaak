CFLAGS =-g -Wall -lm 
CC = gcc

pazaak: pazaak.o game.o card.o
	${CC} ${CFLAGS} -o pazaak pazaak.o game.o card.o 

pazaak.o: pazaak.c game.h card.h
	$(CC) $(CFLAGS) -c pazaak.c

game.o: game.c game.h card.h
	$(CC) $(CFLAGS) -c game.c 

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

all: pazaak

clean:
	-rm -f *.o 
	-rm -f pazaak