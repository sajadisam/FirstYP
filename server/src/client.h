#ifndef _Client_
#define _Client_

#include <SDL2/SDL_net.h>
typedef struct client Client;

Client *client_create(TCPsocket socket);
TCPsocket client_get_socket(Client *client);
IPaddress *client_get_ip(Client *client);
int client_get_id(Client *client);

#endif // !_Client_
