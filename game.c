#include "game.h"

enum turnTok
{
    PLAY,
    COMP
};

typedef struct
{
    enum fakeBool isOver;
    enum turnTok turn;
    int8_t playScore;
    int8_t compScore;
    uint8_t playWins;
    uint8_t compWins;
    enum fakeBool hasPlayStood;
    enum fakeBool hasCompStood;
    card *playBoard[FIELDSIZE]; //make list??
    card *compBoard[FIELDSIZE];
    card *playHand[HANDSIZE];
    card *compHand[HANDSIZE];
} gameState;

void switchTurn(gameState *s)
{
}

int8_t boardScore(card *board[])
{
    int8_t temp = 0;
    for (int i = 0; i < FIELDSIZE; i++)
    {
        temp += board[i]->value;
    }
    return temp;
}
void recalcScore(gameState *s) //
{
    s->playScore = boardScore(s->playBoard);
    s->compScore = boardScore(s->compBoard);
}

void playDeck(gameState *s); //need deck?

//procs after a round ends
void newRound(gameState *s)
{
    // s->turn = //TODO
    s->playScore = 0;
    s->compScore = 0;
    s->hasPlayStood = NO;
    s->hasCompStood = NO;
    //clear playBoard and compBoard TODO
}

void initGame(gameState *s)
{
    s->isOver = NO;
    // s->turn = ; //TODO
    s->playScore = 0;
    s->compScore = 0;
    s->playWins = 0;
    s->compWins = 0;
    s->hasPlayStood = NO;
    s->hasCompStood = NO;
    //TODO the rest
}
void freeGame(gameState *s) //TODO also free either list elements or array entries
{
    free(s->playBoard);
    free(s->compBoard);
    free(s->playHand);
    free(s->compHand);
}

//plays hand card based on the turn of the game
//(0 indexed, translation done by pazaak.c)
void playHand(uint8_t handIdx, gameState *s);
void endTurn(gameState *s);
void stand(gameState *s);
void quitGame(gameState *s);