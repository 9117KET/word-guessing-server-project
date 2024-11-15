# Game Server Project

This project implements a simple game server with client-server architecture. The server handles multiple clients, each playing a word guessing game.

## Structure

- `src/`: Contains all C source files.
- `src/headers/`: Contains all header files.
- `Makefile`: Used to build the project.

## Building the Project

To build the project, you need GCC installed on your system. Navigate to the project directory and run:

```bash
make
```

This will compile the source files and link them to create the executable named `game_server`.

## Running the Project

After building the project, you can start the server by running:

```bash
./game_server -s <port>
```

To start a client, run:

```bash
./game_server -c <address> <port>
```

Replace `<port>` with the port number on which the server listens, and `<address>` with the server's IP address or hostname.

## Cleaning the Build

To clean up the build files, you can run:

```bash
make clean
```

This command will remove all object files and the executable, leaving only the source and header files.

This project is a networked word guessing game where clients connect to a server to guess missing words in dynamically generated phrases. Each client receives a challenge from the server and guesses the missing word. The game supports multiple clients, handled either in a blocking, forking, or threading mode, allowing each client to interact independently.

Contributions to the project are welcome. Please ensure that any pull requests or patches maintain compatibility with the existing codebase.

#   w o r d - g u e s s i n g - s e r v e r - p r o j e c t  
 