// Server.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Server.hpp"

int main()
{
	Server server;
	server.run("127.0.0.1", 8080);
    return 0;
}

