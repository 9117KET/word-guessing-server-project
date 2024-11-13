#include "game.h"
#include "challenge.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

void handle_client(int client_fd) {
    // Initialize a new player
    player_t *player = player_new();
    char *msg;

    // Get the greeting message for the player and send it to the client
    int rc = player_get_greeting(player, &msg);
    if (rc > 0) {
        send(client_fd, msg, strlen(msg), 0); // Send the greeting message to the client
        free(msg); // Free the message after sending
    }

    // Main game loop, continues until the player has finished all challenges
    while (!player->finished) {
        // Get the next challenge for the player and send it to the client
        rc = player_get_challenge(player, &msg);
        if (rc > 0) {
            send(client_fd, msg, strlen(msg), 0); // Send the challenge message to the client
            free(msg); // Free the message after sending
        }

        // Receive a guess from the client
        char guess[256];
        if (recv(client_fd, guess, sizeof(guess), 0) <= 0) break; // Break the loop if no guess is received

        // Process the player's guess and send the result back to the client
        rc = player_post_challenge(player, guess, &msg);
        if (rc > 0) {
            send(client_fd, msg, strlen(msg), 0); // Send the result message to the client
            free(msg); // Free the message after sending
        }
        // If the guess is "q", break the loop to end the game
        if (strcmp(guess, "q") == 0) break;
    }

    // Clean up the player object once the game is over
    player_del(player);
}
