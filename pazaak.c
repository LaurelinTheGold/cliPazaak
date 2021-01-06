#include "display.h"
#include "game.h"

#define STDINBUFF 3

//gets the char from a string and splitting off newline
char getCharFromString(char *str)
{
    return 'a'; //TODO
}

//gets action by getting char from input str and doing the action
void parseAction(char *str, gameState *s)
{
    switch (getCharFromString(str))
    {
    case 'q':
        quitGame(s);
        break;
    case 's':
        stand(s);
        break;
    case 'e':
        endTurn(s);
        break;
    // case '1':
    //     playHand(0, s);
    //     break;
    // case '2':
    //     playHand(1, s);
    //     break;
    // case '3':
    //     playHand(2, s);
    //     break;
    // case '4':
    //     playHand(3, s);
    //     break;
    default:
        printf("Invalid Character, Try Again!\n");
    }
    return;
}

//inits the bois, then loop reads actions off stdin until the game ends or player quits
//then frees everyone and exits
int main(int argc, char *argv[])
{
    gameState *state = (gameState *)malloc(sizeof(gameState *));
    initGame(state);
    char input[STDINBUFF];
    while (state->isOver != YES)
    {
        printf("Controls: q quit, s stand, e end turn, 1 2 3 4 play hand\n");
        fgets(input, STDINBUFF, stdin);
        parseAction(input, state);
    }
    freeGame(state);
    free(state);
    return 0; //TODO
}