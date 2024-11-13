#ifndef SERVER_H
#define SERVER_H

#include "quiz.h"

// Server function to start listening for client connections
void run_server(int port, int mode);

// Function to handle a client connection in blocking mode
void handle_client_blocking(int client_socket);

// Function to handle a client connection in forking mode
void handle_client_forking(int client_socket);

// Function to handle a client connection in threading mode
void handle_client_threading(int client_socket);

#endif // SERVER_H
