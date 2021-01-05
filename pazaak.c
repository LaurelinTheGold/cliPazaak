#include "display.h"
#include "game.h"

#define STDINBUFF 3

void parseAction(char *str, gameState *s)
{
    return; //TODO
}

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