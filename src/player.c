#include "player.h"
#include "challenge.h"
#include <stdlib.h>
#include <string.h>
#include "quiz.h"

// Function to create a new player instance
player_t *player_new(void) {
    // Allocate memory for a new player
    player_t *p = malloc(sizeof(player_t));
    // Check if memory allocation was successful
    if (!p) return NULL;
    // Initialize player's solved challenges count
    p->solved = 0;
    // Set the total number of challenges
    p->total = 5;
    // Initialize player's finished status
    p->finished = 0;
    // Create a new challenge for the player
    p->chlng = challenge_new();
    // Return the new player instance
    return p;
}

// Function to reset a player's progress
void player_reset(player_t *p) {
    // Reset the number of solved challenges
    p->solved = 0;
    // Reset the current challenge
    challenge_reset(p->chlng);
}

// Function to delete a player instance and free its resources
void player_del(player_t *p) {
    // Delete the challenge associated with the player
    challenge_del(p->chlng);
    // Free the memory allocated for the player
    free(p);
}

// Function to get a greeting message for the player
int player_get_greeting(player_t *p, char **msg) {
    // Duplicate a greeting message string
    *msg = strdup("Welcome to the Word Guessing Game!");
    // Return success if the message was successfully duplicated
    return (*msg != NULL);
}

// Function to get the current challenge's text for the player
int player_get_challenge(player_t *p, char **msg) {
    // Duplicate the current challenge's text
    *msg = strdup(p->chlng->text);
    // Return success if the text was successfully duplicated
    return (*msg != NULL);
}

// Function to process the player's guess and update the game state
int player_post_challenge(player_t *p, const char *guess, char **msg) {
    // Check if the player's guess matches the challenge word
    if (strcmp(guess, p->chlng->word) == 0) {
        // Increment the count of solved challenges
        p->solved++;
        // Check if all challenges are solved
        if (p->solved >= p->total) {
            // Mark the player as finished
            p->finished = 1;
            // Set a congratulatory message
            *msg = strdup("Congratulations, you mastered all challenges!");
        } else {
            // Reset the challenge for a new round
            challenge_reset(p->chlng);
            // Set a message indicating the correct guess and next challenge
            *msg = strdup("Correct! Next challenge:");
        }
        // Return success
        return 1;
    }
    // Set a message for incorrect guess
    *msg = strdup("Incorrect. Try again.");
    // Return success
    return 1;
}
