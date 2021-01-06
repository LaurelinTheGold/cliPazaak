#include "game.h"
#include "card.h"

//START OF TESTING BY IGNORING EXISTENCE OF HAND
//Start of testing by forcing player to move first

/*
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
*/

//for debugging
static inline char *prtBool(enum fakeBool fB)
{
    return (fB == YES) ? "YES" : (fB == NO) ? "NO" : "ERROR fakeBool!!\n";
}
//traverses array start to end
//writes each val to a temp string before joining with main string
void prtCardArr(card *arr[], int len, char *dest[])
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] != NULL)
        {
            char cardStr[10];
            sprintf(cardStr, "%d ", arr[i]->value);
            strcat(*dest, cardStr);
        }
    }
}
// Prints out the game state as a long string
void printDebug(gameState *s)
{
    char dest1[1000];
    char dest2[1000];
    char dest3[1000];
    char dest4[1000];
    prtCardArr(s->playBoard, FIELDSIZE, &dest1);
    prtCardArr(s->compBoard, FIELDSIZE, &dest2);
    // prtCardArr(s->playHand, HANDSIZE, &dest3);
    // prtCardArr(s->compHand, HANDSIZE, &dest4);
    printf(
        "over? %s turn? %s pScore:%d cScore:%d pWins:%d cWins%d\n"
        "pStood? %s cStood? %s\npBoard: %s\n cBoard: %s\n"
        "pHand: %s\n cHand: %s\n",
        prtBool(s->isOver), (s->turn == PLAY) ? "PLAY" : "COMP",
        s->playScore, s->compScore, s->playWins, s->compWins,
        prtBool(s->hasPlayStood), prtBool(s->hasCompStood),
        // dest1, dest2, dest3, dest4);
        dest1, dest2);
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
//Recalculates Score. Do i want one person for both??
void recalcScore(gameState *s)
{
    s->playScore = boardScore(s->playBoard);
    s->compScore = boardScore(s->compBoard);
}

void playDeck(gameState *s); //need deck? TODO

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

//plays hand card based on the turn of the game
//(0 indexed, translation done by pazaak.c)
// void playHand(int handIdx, gameState *s);

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
