#ifndef GAME_H_
#define GAME_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"

#include "card.h"

#define FIELDSIZE 9
#define HANDSIZE 4

enum turnTok
{
    PLAY,
    COMP
};

enum fakeBool
{
    YES,
    NO
};

typedef struct
{
    enum fakeBool isOver;
    enum turnTok turn;
    int8_t playScore;
    int8_t compScore;
    uint8_t playWins;
    uint8_t compWins;
    enum fakeBool playStood;
    enum fakeBool compStood;
    card *playBoard[FIELDSIZE]; //make list??
    card *compBoard[FIELDSIZE];
    card *playHand[HANDSIZE];
    card *compHand[HANDSIZE];
} gameState;

//these should be private in .c not header
void switchTurn(gameState *s);  //
void recalcScore(gameState *s); //
void playDeck(gameState *s);    //need deck?
void newGame(gameState *s);

void initGame(gameState *s);
void freeGame(gameState *s);

void playHand(uint8_t handIdx, gameState *s); //plays (1 indexed) hand card based on the turn of the game
void endTurn(gameState *s);
void stand(gameState *s);
void quit(gameState *s);

#endif