// This file defines functions related to players in the UNO game.

// Including the header file for player-related structures and function prototypes
#include "player.h"

// Function to create a new player with the given name
Player* createPlayer(char* name) {
    // Allocate memory for the player structure
    Player* p = (Player *)malloc(sizeof(Player));
    // Allocate memory for the player's name and copy the provided name
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy(p->name, name);
    // Initialize remaining cards and circular references
    p->remainingCards = 7;
    p->previousPlayer = p;
    p->nextPlayer = p;
    // Generate the player's hand
    generatePlayerHand(p);
    return p;
}

// Function to generate a player's hand with randomly generated cards
void generatePlayerHand(Player* p) {
    // Create the first card for the player
    p->firstCard = createCard();
    // Add additional cards to the hand
    for (int i = 0; i < p->remainingCards - 1; i++) {
        Card* newCard = createCard();
        insertCardToList(p->firstCard, newCard);
    }
}

// Function to print information about all players in a circular list
void printPlayers(Player* p) {
    // Traverse the circular list of players and print each player's information
    Player* tmp = p;
    do {
        printPlayer(tmp);
        tmp = tmp->nextPlayer;
    } while (tmp != NULL && tmp != p);
}

// Function to print information about a single player
void printPlayer(Player * p){
    printf("Player's name: %s\n", p->name);
    printf("Number of remaining cards: %d\n", p->remainingCards);
    // Print the player's hand of cards
    printCards(p->firstCard);
}

// Function to insert a player into a circular list of players
void insertPlayerCircularList(Player* p, Player* anotherPlayer) {
    // Find the end of the circular list
    Player* tmp = p;
    do {
        tmp = tmp->nextPlayer;
    } while (tmp != NULL && tmp->nextPlayer != p);
    // Insert the new player into the list
    tmp->nextPlayer = anotherPlayer;
    anotherPlayer->nextPlayer = p;
    p->previousPlayer = anotherPlayer;
    anotherPlayer->previousPlayer = tmp;
}

// Function to delete a player from a circular list of players
void deletePlayerFromList(Player* p) {
    // Adjust references to remove the player from the list
    Player* tmpPrev = p->previousPlayer;
    Player* tmpNext = p->nextPlayer;
    tmpPrev->nextPlayer = tmpNext;
    tmpNext->previousPlayer = tmpPrev;
    // Free memory allocated for the player
    free(p);
    p = NULL;
}

// Function to delete all players from a circular list
void deleteAllPlayers(Player* p) {
    // Traverse the circular list and delete each player
    Player* tmp = p;
    do {
        Player* tmpNext = tmp->nextPlayer;
        // Free memory allocated for the player's name and card list
        free(tmp->name);
        freeEntireList(tmp->firstCard);
        // Free memory allocated for the player structure
        free(tmp);
        // Move to the next player in the list
        tmp = tmpNext;
    } while (tmp != NULL && tmp != p);
}
