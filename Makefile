CFLAGS =-g -Wall -lm 
CC = gcc

pazaak: pazaak.o token.o LC4.o
	${CC} ${CFLAGS} -o pazaak pazaak.o token.o #LC4.o 

pazaak.o: pazaak.c token.h LC4.h
	$(CC) $(CFLAGS) -c pazaak.c

token.o: token.c token.h
	$(CC) $(CFLAGS) -c token.c 

LC4.o: LC4.c LC4.h
	$(CC) $(CFLAGS) -c LC4.c

all: pazaak

clean:
	-rm -f *.o 
	-rm -f pazaak