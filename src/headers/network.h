#ifndef NETWORK_H
#define NETWORK_H

#include <winsock2.h>
// Function to create and bind a socket for the server
int setup_server_socket(int port);

// Function to connect to a server for the client
int connect_to_server(const char *host, int port);

// Function to send a message over a socket
int send_message(int sockfd, const char *msg);

// Function to receive a message from a socket
int receive_message(int sockfd, char *buffer, int size);

#endif // NETWORK_H
