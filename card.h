#ifndef CARD_H_
#define CARD_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"

typedef struct
{
    int value;
} card;

int getValue(card *c);

#endif