#include "game.h"

/*
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
    card *playBoard[FIELDSIZE];
    card *compBoard[FIELDSIZE];
    card *playHand[HANDSIZE];
    card *compHand[HANDSIZE];
} gameState;
*/

static inline char *prtBool(enum fakeBool fB)
{
    return (fB == YES) ? "YES" : "NO";
}

void freeCardPtrArr(card *arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
}

void prtCardArr (card* arr[], int len, char** dest)
{
    for (int i = 0; i < len; i++)
    {
        char cardStr[10];
        sprintf(cardStr, "%d ", arr[i]->value);
        strcat(*dest, cardStr);
    }
}

void printDebug(gameState *s)
{
    char dest1[1000];
    char dest2[1000];
    char dest3[1000];
    char dest4[1000];
    prtCardArr(s->playBoard, FIELDSIZE, &dest1); 
    prtCardArr(s->compBoard, FIELDSIZE, &dest2);
    prtCardArr(s->playHand, HANDSIZE, &dest3);
    prtCardArr(s->compHand, HANDSIZE, &dest4);
    printf(
        "over? %s turn? %s pScore:%d cScore:%d pWins:%d cWins%d\n"
        "pStood? %s cStood? %s\npBoard: %s\n cBoard: %s\n"
        "pHand: %s\n cHand: %s\n",
        prtBool(s->isOver), (s->turn == PLAY) ? "PLAY" : "COMP",
        s->playScore, s->compScore, s->playWins, s->compWins,
        prtBool(s->hasPlayStood), prtBool(s->hasCompStood),
        dest1, dest2, dest3, dest4);
}

void switchTurn(gameState *s)
{
    s->turn = (s->turn == PLAY) ? COMP : PLAY;
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

void playDeck(gameState *s); //need deck? TODO

//procs after a round ends
void newRound(gameState *s)
{
    // s->turn = //TODO
    s->playScore = 0;
    s->compScore = 0;
    s->hasPlayStood = NO;
    s->hasCompStood = NO;
    freeCardPtrArr(s->playBoard, FIELDSIZE);
    freeCardPtrArr(s->compBoard, FIELDSIZE);
}

void fillNull(card *arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }
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
    fillNull(s->playBoard, FIELDSIZE);
    fillNull(s->compBoard, FIELDSIZE);
}


void freeGame(gameState *s) //TODO also free either list elements or array entries
{
    freeCardPtrArr(s->playBoard, FIELDSIZE);
    freeCardPtrArr(s->compBoard, FIELDSIZE);
    freeCardPtrArr(s->playHand, HANDSIZE);
    freeCardPtrArr(s->compHand, HANDSIZE);
}

//plays hand card based on the turn of the game
//(0 indexed, translation done by pazaak.c)
void playHand(uint8_t handIdx, gameState *s);
void endTurn(gameState *s);
void stand(gameState *s);
void quitGame(gameState *s);