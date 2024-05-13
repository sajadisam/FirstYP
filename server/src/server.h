#ifndef _Server_
#define _Server_

#include "client.h"

typedef struct Server Server;

Server *server_create();
void server_add_client(Server *server);
void handle_client_disconnection(Server *server, Client *client);
void handle_client_message(Server *server, Client *client, char msg[1024],
                           int len);
void server_loop(Server *server);
TCPsocket server_get_socket(Server *server);
SDLNet_SocketSet server_get_socket_set(Server *server);
int server_get_client_size(Server *server);
Client *server_get_client(Server *server, int index);

#endif // !_Server_
