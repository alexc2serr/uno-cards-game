// This program implements a basic menu-driven UNO game interface using ASCII characters for visual appeal.
      /*
░█▄█░█▀█░▀█▀░█▀█
░█░█░█▀█░░█░░█░█
░▀░▀░▀░▀░▀▀▀░▀░▀*/


// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Custom header file for game functionalities
#include "game.h"

// Menu options
#define MENU_ADD_PLAYER 1
#define MENU_SHOW_PLAYERS 2
#define MENU_START_GAME 3
#define MENU_SHOW_GAME_RULES 4
#define MENU_QUIT_GAME 5
#define MENU_INVALID_SELECTION -1
#define BAR_WIDTH 50

// Function to print game rules
void printGameRules() {
    printf("=======================================\n");
    printf("          Game Rules\n");
    printf("=======================================\n");
    printf("1. Players take turns clockwise.\n");
    printf("2. On your turn, you can play a card of the same color or number as the top card of the discard pile.\n");
    printf("3. Special cards have additional effects, such as skip or reverse.\n");
    printf("4. You can only select one of your cards if it is valid. If you have no valid cards, you will automatically draw one.\n");
    printf("5. You must say 'UNO' when you have only one card left in your hand.\n");
    printf("=======================================\n\n");
}

// Function to display the loading bar
void displayLoadingBar(int progress) {
    printf("[");
    for (int i = 0; i < BAR_WIDTH; ++i) {
        if (i < progress * BAR_WIDTH / 100)
            printf("=");
        else
            printf(" ");
    }
    printf("] %d%%\r", progress);
    fflush(stdout);
}

// Main function
int main() {
    setbuf(stdout, NULL); // Flush stdout buffer
    Game* g = createGame(); // Create game instance
    int progress = 0;
    while (progress <= 100) {
        displayLoadingBar(progress);
        usleep(100000); // Sleep for 100 milliseconds (0.1 seconds)
        progress += 2; // Increment the progress
    }
    printf("\nLoading complete!\n");
    // Welcome message
    printf("Welcome to the UNO. First game, Read the rules and have fun!!!\n");

    // Menu selection loop
    int menuSelection = MENU_INVALID_SELECTION;
    while (menuSelection != MENU_QUIT_GAME) {
        // Print menu options
        printf("=======================================\n");
        printf("              Menu\n");
        printf("=======================================\n");
        printf("1. Add a player\n");
        printf("2. Show list of players\n");
        printf("3. Start the game\n");
        printf("4. Show game rules\n");
        printf("5. Quit the game\n");
        printf("=======================================\n");
        printf("Enter your option:\n");

        fflush(stdin); // Flush stdin buffer
        fflush(stdout); // Flush stdout buffer
        scanf("%d", &menuSelection); // Read menu selection

        // Handle menu options
        if (menuSelection == MENU_ADD_PLAYER) {
            // Add a player
            printf("Enter your name:\n");
            char *name = malloc(100 * sizeof(char)); // Allocate memory for player name
            fflush(stdin);
            fflush(stdout);
            fgets(name, 100, stdin);
            name[strcspn(name, "\n")] = 0;

            // Create player instance and add to the game
            if (g->currentPlayer == NULL) {
                g->currentPlayer = createPlayer(name);
            }
            else {
                Player* player = createPlayer(name);
                insertPlayerCircularList(g->currentPlayer, player);
            }
            g->remainingPlayers++;
        }
        else if (menuSelection == MENU_SHOW_PLAYERS) {
            // Show list of players
            if (g->currentPlayer == NULL) {
                printf("There are currently no players waiting for the game\n");
            }
            else {
                printPlayers(g->currentPlayer);
            }
        }
        else if (menuSelection == MENU_START_GAME) {
            // Start the game
            if (g->remainingPlayers >= 2) {
                mainGameLoop(g);
                deleteGame(g);
                g = createGame();
            }
            else {
                printf("There are not enough players to start the game. Minimum of 2 players required\n");
            }
        }
        else if (menuSelection == MENU_SHOW_GAME_RULES) {
            // Show game rules
            printGameRules();
        }
        else if (menuSelection == MENU_QUIT_GAME) {
            // Quit the game
            printf("See you soon!");
        }
        else {
            // Invalid selection
            printf("Invalid selection. Please select one of the following options:\n");
        }
    }
    return 0;
}
