# Network Programming Lab 2

To clone this repo use the command : 

`git clone --recursive https://github.com/Psychotiik/Reseau-TP2`


#Compilation

Cmake is required to compile our project
using C++ 17
 
#Running

type the command below in the directory out/build/Debug-to run our program

~tp2.exe mode addr_server port_server

mode must be "server" or "client"
exemple: tp2.exe server "127.0.0.1" 4242

#Use
#Client mode
When data is received, client mode will display all modifications it has detected and then all word's objects
Multiclient is possible
Use ctrl + C to stop

#Server mode
Server mode manage GameObjects. User might type commands:
help : display information to use server program
init : Initialize GameObjects with default samples (three players and two ennemies)
creation_test : Create a new GameObject
deletion_test : Delete the 1st object in memory
send : send all modifications to all clients
exit : quit program

The Server will display when detecting a new connection and feedbacks at each executed command

#Project Comment
#Recommended behavior as testing our program
1) Create a server instance
2) Create to clients
3) Init gameObjects
4) Send data
5) creation_test
6) Send data
7) Connect another client
8) deletion_test
9) Send data
10) exit server (clients will be disconnected)

