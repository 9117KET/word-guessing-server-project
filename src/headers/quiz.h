#ifndef QUIZ_H
#define QUIZ_H

#include <stdbool.h>

// Challenge structure holding the challenge text and the missing word
typedef struct {
    char *text;      // Text with a missing word
    char *word;      // The missing word
} chlng_t;

// Player structure holding the player's progress and current challenge
typedef struct {
    int solved;          // Correctly solved challenges
    int total;           // Total number of challenges
    bool finished;       // True if game is over
    chlng_t *chlng;      // Current challenge
} player_t;

// Challenge functions
chlng_t* chlng_new(void);                         // Allocate a new challenge
void chlng_reset(chlng_t *c);                     // Reset challenge state
void chlng_del(chlng_t *c);                       // Delete a challenge and free resources
void chlng_fetch_text(chlng_t *c);                // Fetch text from a source (e.g., fortune)
void chlng_hide_word(chlng_t *c);                 // Hide a word in the text

// Player functions
player_t* player_new(void);                       // Allocate a new player
void player_reset(player_t *p);                   // Reset player state
void player_del(player_t *p);                     // Delete a player and free resources
int player_fetch_chlng(player_t *p);              // Assign a new challenge to the player
int player_get_greeting(player_t *p, char **msg); // Retrieve greeting message
int player_get_challenge(player_t *p, char **msg); // Retrieve the challenge message
int player_post_challenge(player_t *p, const char *answer, char **msg); // Post an answer and retrieve response

#endif // QUIZ_H
