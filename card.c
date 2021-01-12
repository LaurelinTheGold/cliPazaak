#include "card.h"

int getValue(card *c)
{
    return c->value;
}

card *makeCard(int val)
{
    card *cardPtr = (card *)malloc(sizeof(card));
    if (cardPtr != NULL)
    {
        cardPtr->value = val;
        return cardPtr;
    }
    else
    {
        printf("ERROR MALLOC CARD FAIL!\n");
    }
}