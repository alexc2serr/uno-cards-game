// This header file defines structures and functions related to UNO cards.

#ifndef PRACTICAUNO_CARD_H
#define PRACTICAUNO_CARD_H

// Standard libraries
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

// ANSI color codes for printing colored cards
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

// ASCII symbols for card borders
#define TOP_LEFT_CORNER 201
#define TOP_RIGHT_CORNER 187
#define BOTTOM_LEFT_CORNER 200
#define BOTTOM_RIGHT_CORNER 188
#define VERTICAL_LINE 186
#define HORIZONTAL_LINE 205
#define SKIP_CARD_SYMBOL 175
#define REVERSE_CARD_SYMBOL 47

// Card colors and types
#define BLUE_COLOR 0
#define RED_COLOR 1
#define YELLOW_COLOR 2
#define GREEN_COLOR 3
#define NORMAL_CARD 0
#define SKIP_CARD 1
#define REVERSE_CARD 2

// Structure representing a card
typedef struct Card {
    int number; // from 0 to 9
    int color; // 0 is blue, 1 is red, 2 is yellow, 3 is green
    int cardType; // 0 is normal, 1 is skip, 2 is reverse

    struct Card* nextCard; // cards are a linked list
} Card;

// Function prototypes
Card* createCard();
int checkValidCard(Card* c, Card* topCardOnTable);
Card* chooseCard(Card* c, int index);
void printCards(Card* c);
void printOneCard(Card* c);
int printValidCards(Card* hand, Card* topCardOnTable);
void insertCardToList(Card* c, Card* anotherCard);
Card* deleteCardFromList(Card* c, int index);
void freeCardList(Card* c, Card* previous);
void freeEntireList(Card* c);

#endif //PRACTICAUNO_CARD_H
