// This file contains functions related to UNO cards.

#include "card.h"

// Function to create a new UNO card
Card* createCard() {
    // Allocate memory for the card
    Card* c = (Card*)malloc(sizeof(Card));
    // Assign random values for color, number, and card type
    c->color = rand() % 4;
    c->number = rand() % 9;
    c->cardType = rand() % 3;
    c->nextCard = NULL; // Initialize next pointer
    return c;
}

// Function to check if a card is valid to play
int checkValidCard(Card* c, Card* topCardOnTable) {
    // Check if either card is a special type
    if (c->cardType != NORMAL_CARD || topCardOnTable->cardType != NORMAL_CARD) {
        if (c->color == topCardOnTable->color) {
            return 1; // Valid card
        }
        else if (c->cardType == topCardOnTable->cardType) {
            return 1; // Valid card
        }
        else {
            return 0; // Invalid card
        }
    }
    else {
        if (c->color == topCardOnTable->color) {
            return 1; // Valid card
        }
        else if (c->number == topCardOnTable->number) {
            return 1; // Valid card
        }
        else {
            return 0; // Invalid card
        }
    }
}

// Function to choose a card from a player's hand based on index
Card* chooseCard(Card* c, int index) {
    Card* tmp = c;
    int searchIndex = 1;
    // Traverse the linked list to find the card at the specified index
    while (tmp != NULL && searchIndex != index) {
        searchIndex++;
        tmp = tmp->nextCard;
    }
    return tmp;
}

// Function to print all cards in a linked list
void printCards(Card* c) {
    Card* tmp = c;
    int cardIndex = 1;
    // Iterate through the linked list and print each card
    do {
        printf("Card %d:\n", cardIndex);
        printOneCard(tmp);
        tmp = tmp->nextCard;
        cardIndex++;
    } while (tmp != NULL);
}

// Function to print a single card
void printOneCard(Card* c) {
    // Determine the representation of the card based on its type
    char cardRepresentation;
    if (c->cardType == NORMAL_CARD) {
        cardRepresentation = '0' + c->number;
    }
    else if (c->cardType == SKIP_CARD) {
        cardRepresentation = (char)SKIP_CARD_SYMBOL;
    }
    else if (c->cardType == REVERSE_CARD) {
        cardRepresentation = (char)REVERSE_CARD_SYMBOL;
    }
    else {
        printf("Invalid card type. Exiting the game.\n");
        exit(1);
    }

    // Print the card with ANSI color codes for color
    if (c->color == BLUE_COLOR) {
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardRepresentation, VERTICAL_LINE);
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (c->color == RED_COLOR) {
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardRepresentation, VERTICAL_LINE);
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (c->color == YELLOW_COLOR) {
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardRepresentation, VERTICAL_LINE);
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (c->color == GREEN_COLOR) {
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardRepresentation, VERTICAL_LINE);
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else {
        printf("Invalid card color. Exiting the game.\n");
        exit(1);
    }
}

// Function to print valid cards in a player's hand
int printValidCards(Card* hand, Card* topCardOnTable) {
    Card* tmp = hand;
    int searchIndex = 1;
    int numValid = 0;
    // Iterate through the linked list and print valid cards
    while (tmp != NULL) {
        if (checkValidCard(tmp, topCardOnTable)) {
            printf("%d ", searchIndex);
            numValid++;
        }
        searchIndex++;
        tmp = tmp->nextCard;
    }
    printf("\n");
    return numValid;
}

// Function to insert a card into a linked list
void insertCardToList(Card* c, Card* anotherCard) {
    Card* tmp = c;
    // Traverse the linked list to find the last card
    while (tmp->nextCard != NULL) {
        tmp = tmp->nextCard;
    }
    // Insert the new card at the end
    tmp->nextCard = anotherCard;
}

// Function to delete a card from a linked list based on index
Card* deleteCardFromList(Card* c, int index) {
    if (index == 0) {
        // If the card to be deleted is the first one
        Card* startList = c->nextCard;
        c->nextCard = NULL;
        return startList;
    }
    else {
        // Traverse the linked list to find the card at the specified index
        int i = 0;
        Card* tmp = c;
        Card* previous = c;
        while (tmp != NULL && i < index) {
            previous = tmp;
            tmp = tmp->nextCard;
            i++;
        }
        // Ensure the card is found
        if (tmp == NULL) {
            printf("An error occurred while trying to play a card. Exiting.\n");
            exit(1);
        }
        else {
            // Remove the card from the linked list
            previous->nextCard = tmp->nextCard;
        }
        return c;
    }
}

// Function to free memory occupied by a single card
void freeCardList(Card* c, Card* previous) {
    if (previous != NULL && c->nextCard != NULL) {
        previous->nextCard = c->nextCard;
    }
    free(c);
    c = NULL;
}

// Function to free memory occupied by an entire card linked list
void freeEntireList(Card* c) {
    Card* tmp = c;
    Card* tmpNext = c->nextCard;
    // Iterate through the linked list and free each card
    do {
        tmpNext = tmp->nextCard;
        free(tmp);
        tmp = tmpNext;
    } while (tmp != NULL);
    c = NULL;
}
