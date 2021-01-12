#include "game.h"
#include "card.h"
#include <stdlib.h>

//START OF TESTING BY IGNORING EXISTENCE OF HAND
//Start of testing by forcing player to move first

/** Assumptions:
When the bois are malloced, they are written with null pointers, and 
only made real when needed. The only way to delete them involves
freeing if not null then nulling them 

Only check for valid state on input actions and assume code works so won't 
go from valid to invalid by itself
*/

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void initDeck(gameState *s)
{
    int *arrPtr = s->deck;
    for (int i = 1; i <= DECKRANGE; i++)
    {
        for (int j = 0; j < DECKMULT; j++)
        {
            *arrPtr = i;
            arrPtr++;
        }
    }
    shuffle(s->deck, DECKRANGE * DECKMULT);
}

//helper bois
char *prtBool(enum fakeBool fB)
{
    return (fB == YES) ? "YES" : "NO";
}
char *prtTurn(enum turnTok t)
{
    return (t == PLAY) ? "PLAY" : "COMP";
}
void prntCard(card *c)
{
    if (c != NULL)
    {
        printf("%d ", c->value);
    }
    else
    {
        printf("0 ");
    }
}
// Prints out the game state as a long string
void printDebug(gameState *s)
{
    printf("over? %s\nturn? %s\npScore:%d cScore:%d\npWins:%d cWins%d\npStood? %s cStood? %s\n",
           prtBool(s->isOver), prtTurn(s->turn),
           s->playScore, s->compScore, s->playWins, s->compWins,
           prtBool(s->hasPlayStood), prtBool(s->hasCompStood));
    printf("Player Board: ");
    for (int i = 0; i < FIELDSIZE; i++)
    {
        prntCard(s->playBoard[i]);
    }
    printf("\nComputer Board: ");
    for (int i = 0; i < FIELDSIZE; i++)
    {
        prntCard(s->compBoard[i]);
    }
    printf("\n");
}
void delCard(card *c)
{
    if (c != NULL)
    {
        free(c);
        c = NULL;
    }
}
int boardScore(card *board[])
{
    int temp = 0;
    for (int i = 0; i < FIELDSIZE; i++)
    {
        if (board[i] != NULL)
        {
            temp += board[i]->value;
        }
    }
    return temp;
}
void recalcScore(gameState *s)
{
    s->playScore = boardScore(s->playBoard);
    s->compScore = boardScore(s->compBoard);
}

//checks win/loss conditions and gives int representing result, return 0 on none, -1 on loss, 1 on win
int checkConds(gameState *s, int action) //action: 0 is stand, 1 is end turn, 2 is played card so if 20 end
{
    return 0; //TODO
}

//adds a point checking for game conds
void addWin(gameState *s, enum turnTok tt)
{
    if (tt == PLAY)
    {
        if (s->playWins < 2)
        {
            s->playWins++;
        }
        else
        {
            s->isOver = YES;
            printf("Player has won the match!\n");
        }
    }
    else if (tt == COMP)
    {
        if (s->compWins < 2)
        {
            s->compWins++;
        }
        else
        {
            s->isOver = YES;
            printf("Computer has won the match!\n");
        }
    }
    else
    {
        //error
        printf("Error fallthrough else 3\n");
    }
}

//check for full board
void addCard(gameState *s, card *c)
{
    int i = 0;
    if (s->turn == PLAY)
    {
        while (s->playBoard[i] != NULL)
        {
            i++;
        }
        if (i < FIELDSIZE)
        {
            s->playBoard[i] = c;
        }
        else
        {
            printf("ERROR, Board Full Player!!\n");
        }
    }
    else
    {
        while (s->compBoard[i] != NULL)
        {
            i++;
        }
        if (i < FIELDSIZE)
        {
            s->compBoard[i] = c;
        }
        else
        {
            printf("ERROR, Board Full Computer!!\n");
        }
    }
    recalcScore(s);
    if (s->turn == PLAY)
    {
        if (s->playScore == WINSCORE)
        {
            s->hasPlayStood = YES;
        }
    }
    else
    {
        if (s->compBoard == WINSCORE)
        {
            s->hasCompStood = YES;
        }
    }
}

// plays card from deck, should check if total is 20 and if so, auto stand
void playDeck(gameState *s) //need deck? TODO
{
    //add card from deck to current turn players board
    //get score, if 20, auto stand
    //done
    addCard(s, getDeckCard(s));
}

//frees cardptr array by freeing each nonnull entry and then nulling
void freeCardPtrArr(card *arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] != NULL)
        {
            free(arr[i]);
        }
        arr[i] = NULL;
    }
}

//implict assumes turn has 2 states only TODO, case on stood
void switchTurn(gameState *s)
{
    s->turn = (s->turn == PLAY) ? COMP : PLAY;
}

//procs after a round ends
void newRound(gameState *s)
{
    // s->turn = //TODO
    s->turn = PLAY;
    s->playScore = 0;
    s->compScore = 0;
    s->hasPlayStood = NO;
    s->hasCompStood = NO;
    freeCardPtrArr(s->playBoard, FIELDSIZE);
    freeCardPtrArr(s->compBoard, FIELDSIZE);
    //do nothing with the hand between rounds
}

//Only called at init otherwise could cause memory leaks
void fillNull(card *arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }
}

//plays hand card based on the turn of the game
//(0 indexed, translation done by pazaak.c)
// void playHand(int handIdx, gameState *s);

void initGame(gameState *s)
{
    s->isOver = NO;
    // s->turn = ; //TODO
    s->turn = PLAY;
    s->playScore = 0;
    s->compScore = 0;
    s->playWins = 0;
    s->compWins = 0;
    s->hasPlayStood = NO;
    s->hasCompStood = NO;
    fillNull(s->playBoard, FIELDSIZE);
    fillNull(s->compBoard, FIELDSIZE);
    //TODO hand draft functionality
}

void freeGame(gameState *s) //TODO also free either list elements or array entries
{
    freeCardPtrArr(s->playBoard, FIELDSIZE);
    freeCardPtrArr(s->compBoard, FIELDSIZE);
    // freeCardPtrArr(s->playHand, HANDSIZE);
    // freeCardPtrArr(s->compHand, HANDSIZE);
}

//main will take care of freeing from here
void quitGame(gameState *s)
{
    s->isOver = YES;
}

void endTurn(gameState *s)
{
    if ((s->turn == PLAY && s->hasPlayStood == YES) || (s->turn == COMP && s->hasCompStood == YES))
    {
        printf("Should be unreachable Error! 0\n");
    }
    recalcScore(s);
    switch (checkConds(s, 1))
    {
    case -1: //loss, add win to other player, start new game, happens when over 20
        addWin(s, ((s->turn == PLAY) ? COMP : PLAY));
        newRound(s);
        break;
    case 0: //nothing, switch turns
        switchTurn(s);
        break;
    case 1: //win, happens with opponent already stood, add win to me, start new game.
        addWin(s, (s->turn == COMP) ? COMP : PLAY);
        newRound(s);
        break;
    }
}

//change to stand?, Recalc Score, check winconds
void stand(gameState *s)
{
    if ((s->turn == PLAY && s->hasPlayStood == YES) || (s->turn == COMP && s->hasCompStood == YES))
    {
        printf("Should be unreachable Error! 1\n");
    }
    if (s->turn == PLAY)
    {
        s->hasPlayStood = YES;
    }
    else
    {
        s->hasCompStood = YES;
    }
    recalcScore(s);
    switch (checkConds(s, 0))
    {
    case -1: //loss, add win to other player, start new game, happens when over 20
        addWin(s, (s->turn == PLAY) ? COMP : PLAY);
        newRound(s);
        break;
    case 0: //nothing, switch turns
        switchTurn(s);
        break;
    case 1: //win, happens with opponent already stood, add win to me, start new game.
        addWin(s, (s->turn == COMP) ? COMP : PLAY);
        newRound(s);
        break;
    }
}
