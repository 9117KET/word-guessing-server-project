#include "client.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_client(const char *address, int port) {
    // Establish connection to the server using the provided address and port
    int client_fd = connect_to_server(address, port);
    if (client_fd < 0) {
        perror("Failed to connect to server"); // Print error if connection fails
        return; // Exit the function if connection is not successful
    }

    char buffer[256]; // Buffer to store messages
    while (1) { // Infinite loop to keep the client running
        // Receive data from server
        if (recv(client_fd, buffer, sizeof(buffer), 0) <= 0) {
            printf("Server disconnected.\n"); // Notify user if server disconnects or error occurs
            break; // Exit loop if no data is received (server disconnected)
        }
        printf("Server: %s\n", buffer); // Display received message from server

        // Get input from user
        printf("Your guess: ");
        fgets(buffer, sizeof(buffer), stdin); // Read user input into buffer
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character from input
        send(client_fd, buffer, strlen(buffer), 0); // Send user input back to server
    }
    close(client_fd); // Close the connection to the server
}
