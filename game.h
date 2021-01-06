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
    int playScore;
    int compScore;
    int playWins;
    int compWins;
    enum fakeBool hasPlayStood;
    enum fakeBool hasCompStood;
    enum fakeBool playBoardFull;
    enum fakeBool compBoardFUll;
    card *playBoard[FIELDSIZE];
    card *compBoard[FIELDSIZE];
    // card *playHand[HANDSIZE];
    // card *compHand[HANDSIZE];
    //DECK
} gameState;

void initGame(gameState *s);
void freeGame(gameState *s);

//plays hand card based on the turn of the game
//(0 indexed, translation done by pazaak.c)
// void playHand(int handIdx, gameState *s);

void endTurn(gameState *s);
void stand(gameState *s);
void quitGame(gameState *s);

#endif