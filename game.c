// This file contains functions related to the game mechanics of UNO.

#include "game.h"

// Function to create a new game instance
Game* createGame() {
    // Allocate memory for the game structure
    Game* g = (Game*)malloc(sizeof(Game));

    // Initialize game attributes
    g->remainingPlayers = 0;
    g->topCard = createCard();
    g->currentPlayer = NULL;
    g->gameDirection = CLOCKWISE;

    return g;
}

// Function to change the game direction
void changeGameDirection(Game* g) {
    // Toggle game direction between clockwise and counterclockwise
    if (g->gameDirection == CLOCKWISE) {
        g->gameDirection = COUNTER_CLOCKWISE;
    } else {
        g->gameDirection = CLOCKWISE;
    }
}

// Function to move to the next turn
void nextTurn(Game* g) {
    // Move to the next player according to the game direction
    if (g->gameDirection == CLOCKWISE) {
        g->currentPlayer = g->currentPlayer->nextPlayer;
    } else {
        g->currentPlayer = g->currentPlayer->previousPlayer;
    }
}

// Function to skip the next player's turn
void skipTurn(Game* g) {
    // Skip the next player's turn based on the game direction
    if (g->gameDirection == CLOCKWISE) {
        printf("Player %s has skipped to player %s!\n", g->currentPlayer->name, g->currentPlayer->nextPlayer->name);
        g->currentPlayer = g->currentPlayer->nextPlayer->nextPlayer;
    } else {
        printf("Player %s has skipped to player %s!\n", g->currentPlayer->name, g->currentPlayer->previousPlayer->name);
        g->currentPlayer = g->currentPlayer->previousPlayer->previousPlayer;
    }
}

// Function to delete the game instance and free allocated memory
void deleteGame(Game* g) {
    // Delete all players and free memory
    deleteAllPlayers(g->currentPlayer);
    freeCardList(g->topCard, NULL);
    free(g);
    g = NULL;
}

// Main game loop function
void mainGameLoop(Game* g) {
    printf("Game begins\n");
    int anotherRound = 0;

    // Game loop
    while (g->remainingPlayers > 1) {
        printf("The last played card is:\n");
        printOneCard(g->topCard);
        printf("Player's turn:\n");
        printPlayer(g->currentPlayer);
        int numValid = printValidCards(g->currentPlayer->firstCard, g->topCard);
        if (numValid == 0) {
            printf("Player has no valid cards, drawing one and passing the turn\n");
            Card* newCard = createCard();
            insertCardToList(g->currentPlayer->firstCard, newCard);
            g->currentPlayer->remainingCards++;
            nextTurn(g);
        } else {
            int selectedCard = -1;
            int validSelection = 0;
            Player* finishedPlayer = NULL;
            do {
                printf("Select one of the above cards\n");
                fflush(stdin);
                fflush(stdout);
                scanf("%d", &selectedCard);

                if (selectedCard < 1 || selectedCard > g->currentPlayer->remainingCards) {
                    printf("The selected card is not in the range of available cards for the player, try again\n");
                    printPlayer(g->currentPlayer);
                    printValidCards(g->currentPlayer->firstCard, g->topCard);
                } else {
                    Card* chosenCard = chooseCard(g->currentPlayer->firstCard, selectedCard);
                    if (checkValidCard(chosenCard, g->topCard)) {
                        validSelection = 1;

                        freeCardList(g->topCard, NULL);
                        g->topCard = chosenCard;
                        g->currentPlayer->firstCard = deleteCardFromList(g->currentPlayer->firstCard,
                                                                         selectedCard - 1);
                        g->currentPlayer->remainingCards--;
                        if (g->currentPlayer->remainingCards == 0) {
                            printf("Player %s has finished the game, congratulations!\n", g->currentPlayer->name);
                            finishedPlayer = g->currentPlayer;
                            g->remainingPlayers--;
                            if (g->remainingPlayers <= 1) {
                                nextTurn(g);
                                break;
                            }
                            printf("%d player(s) remaining\n", g->remainingPlayers);
                        } else if (g->currentPlayer->remainingCards == 1) {
                            printf("Player %s: UNO!\n", g->currentPlayer->name);
                        }
                        if (chosenCard->cardType == SKIP_CARD) {
                            skipTurn(g);
                        } else if (chosenCard->cardType == REVERSE_CARD) {
                            changeGameDirection(g);
                            nextTurn(g);
                        } else {
                            nextTurn(g);
                        }
                    } else {
                        printf("The card you have chosen is not valid, try again\n");
                        printPlayer(g->currentPlayer);
                        printValidCards(g->currentPlayer->firstCard, g->topCard);
                    }
                }
            } while (validSelection != 1);
            if (finishedPlayer != NULL) {
                deletePlayerFromList(finishedPlayer);
                finishedPlayer = NULL;
            }
        }
    }

    printf("Game over!\n");
}
