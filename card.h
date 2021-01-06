#ifndef CARD_H_
#define CARD_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"

typedef struct
{
    int8_t value;
} card;

int8_t getValue(card *c);

#endif