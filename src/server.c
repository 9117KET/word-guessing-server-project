#include "server.h"
#include "network.h"
#include "game.h"

// Conditional compilation for different operating systems
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>  // For Windows API functions
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

// Function to start the server on a specified port
void start_server(int port) {
    // Create a server socket
    int server_fd = create_server_socket(port);
    // Check if socket creation failed
    if (server_fd < 0) {
        perror("Failed to create server socket");
        return;
    }

    // Server loop to handle multiple clients
    while (1) {
        // Accept a client connection
        int client_fd = accept_client(server_fd);
        // Continue in the loop if client acceptance failed
        if (client_fd < 0) continue;

        // Windows-specific process creation
        #ifdef _WIN32
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        // Initialize the STARTUPINFO structure
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        // Initialize the PROCESS_INFORMATION structure
        ZeroMemory(&pi, sizeof(pi));

        // Create a new process to handle the client
        HANDLE hProcess = CreateProcess(NULL,   // No module name (use command line)
            "handle_client",        // Command line
            NULL,                   // Process handle not inheritable
            NULL,                   // Thread handle not inheritable
            FALSE,                  // Set handle inheritance to FALSE
            0,                      // No creation flags
            NULL,                   // Use parent's environment block
            NULL,                   // Use parent's starting directory 
            &si,                    // Pointer to STARTUPINFO structure
            &pi );                 // Pointer to PROCESS_INFORMATION structure
        // Check if process creation failed
        if (hProcess == NULL) {
            // Handle error
            closesocket(client_fd);
            continue;
        }
        // Close process and thread handles
        CloseHandle(hProcess);  
        #else
        // Unix/Linux-specific fork to create a new process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process to handle the client
            close(server_fd);  // Close the server socket in the child process
            handle_client(client_fd);  // Handle client operations
            close(client_fd);  // Close client socket
            exit(0);  // Exit child process
        } else {
            // Parent process
            close(client_fd);  // Close client socket
            // Clean up all zombie processes
            while (waitpid(-1, NULL, WNOHANG) > 0);  
        }
        #endif
    }
}
