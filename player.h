// This file contains functions related to players in the UNO game.

#ifndef PRACTICAUNO_PLAYER_H
#define PRACTICAUNO_PLAYER_H

#include "card.h"
#include <string.h>

// Define the structure for a player
typedef struct Player {
    char* name; // Player's name
    Card* firstCard; // Pointer to the first card in the player's hand
    int remainingCards; // Number of remaining cards in the player's hand

    // Circular list pointers
    struct Player* nextPlayer;
    struct Player* previousPlayer;
} Player;

// Function to create a new player
Player* createPlayer(char* name);

// Function to print all players in a circular list
void printPlayers(Player* p);

// Function to print a single player's details
void printPlayer(Player* p);

// Function to insert a player into a circular list
void insertPlayerCircularList(Player* p, Player* otherPlayer);

// Function to generate a player's hand
void generatePlayerHand(Player* p);

// Function to delete a player from a circular list
void deletePlayerFromList(Player* p);

// Function to delete all players from a circular list
void deleteAllPlayers(Player* p);

#endif //PRACTICAUNO_PLAYER_H
