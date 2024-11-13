#include "challenge.h"
#include <stdlib.h>
#include <string.h>

// Function to create a new challenge instance
challenge_t *challenge_new(void) {
    // Allocate memory for a new challenge object
    challenge_t *c = malloc(sizeof(challenge_t));
    // Check if memory allocation was successful
    if (!c) return NULL;
    // Initialize the text of the challenge
    c->text = strdup("This is a sample phrase with a missing ----.");
    // Initialize the word that completes the challenge
    c->word = strdup("word");
    // Return the newly created challenge object
    return c;
}

// Function to reset an existing challenge to a new state
void challenge_reset(challenge_t *c) {
    // Free the existing text and word to prevent memory leaks
    free(c->text);
    free(c->word);
    // Set new text for the challenge
    c->text = strdup("Another phrase with a missing ----.");
    // Set new word for the challenge
    c->word = strdup("test");
}

// Function to delete a challenge and free its resources
void challenge_del(challenge_t *c) {
    // Free the text and word of the challenge
    free(c->text);
    free(c->word);
    // Finally, free the challenge object itself
    free(c);
}
