// This file contains definitions related to the game structure and mechanics.

#ifndef PRACTICAUNO_GAME_H
#define PRACTICAUNO_GAME_H

#include "player.h"

// Constants defining game direction
#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

// Structure defining the game
typedef struct Game {
    Player* currentPlayer; // Pointer to the current player
    int gameDirection;     // 0 for clockwise, 1 for counterclockwise
    int remainingPlayers;  // Number of players remaining in the game
    Card* topCard;         // Pointer to the top card on the table
} Game;

// Function prototypes
Game* createGame();                 // Create a new game instance
void changeGameDirection(Game* g);  // Change the game direction
void nextTurn(Game* g);             // Move to the next turn
void skipTurn(Game* g);             // Skip the next player's turn
void mainGameLoop(Game* g);         // Main game loop
void deleteGame(Game* g);           // Delete the game instance

#endif //PRACTICAUNO_GAME_H
