#ifndef GAME_H
#define GAME_H

#include "quiz.h"

// Function to initialize a new game with a player
void game_init(player_t *player);

// Function to handle the gameplay loop, interacting with the player
void game_loop(player_t *player);

#endif // GAME_H
