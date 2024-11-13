#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client.h"

// Function to print the usage instructions for the program
void print_usage(const char *prog_name) {
    printf("Usage:\n");
    printf("%s -s <port>  # Start server\n", prog_name);
    printf("%s -c <address> <port>  # Start client\n", prog_name);
}

// Main function: Entry point of the program
int main(int argc, char *argv[]) {
    // Check if the number of arguments is less than required
    if (argc < 3) {
        print_usage(argv[0]);  // Call function to print usage instructions
        return EXIT_FAILURE;   // Exit program with a failure status
    }

    // Check if the first argument is "-s" and the correct number of arguments is provided
    if (strcmp(argv[1], "-s") == 0 && argc == 3) {
        int port = atoi(argv[2]);  // Convert the port argument from string to integer
        start_server(port);        // Call function to start the server
    } 
    // Check if the first argument is "-c" and the correct number of arguments is provided
    else if (strcmp(argv[1], "-c") == 0 && argc == 4) {
        const char *address = argv[2];  // Store the address argument
        int port = atoi(argv[3]);       // Convert the port argument from string to integer
        start_client(address, port);    // Call function to start the client
    } 
    // If none of the above conditions are met, print usage instructions
    else {
        print_usage(argv[0]);  // Call function to print usage instructions
        return EXIT_FAILURE;   // Exit program with a failure status
    }

    return EXIT_SUCCESS;  // Exit program with a success status
}
