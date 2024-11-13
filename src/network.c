#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h> // For inet_pton and other functions
#pragma comment(lib, "Ws2_32.lib") // Link with Ws2_32.lib
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

// Function to create a server socket bound to the specified port
int create_server_socket(int port) {
    #ifdef _WIN32
    WSADATA wsaData;
    // Initialize Winsock
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        // Handle error if Winsock initialization fails
        return -1;
    }
    #endif

    // Create a socket for the IPv4 address family and TCP protocol
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set up the socket address structure
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // Convert port number to network byte order
    addr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces

    // Bind the socket to the address and port specified
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        #ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
        #else
        close(sockfd);
        #endif
        return -1;
    }

    // Listen for incoming connections, with a maximum of 10 pending connections
    if (listen(sockfd, 10) < 0) {
        #ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
        #else
        close(sockfd);
        #endif
        return -1;
    }

    #ifdef _WIN32
    // Reminder to clean up Winsock when done using the sockets
    #endif

    return sockfd; // Return the socket descriptor
}

// Function to accept a client connection on the given server socket
int accept_client(int server_fd) {
    return accept(server_fd, NULL, NULL);
}

// Function to connect to a server at the specified address and port
int connect_to_server(const char *address, int port) {
    // Create a socket for the IPv4 address family and TCP protocol
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set up the socket address structure for the server
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // Convert port number to network byte order
    inet_pton(AF_INET, address, &addr.sin_addr); // Convert IP address from text to binary form

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) return -1;
    return sockfd; // Return the socket descriptor if successful
}
