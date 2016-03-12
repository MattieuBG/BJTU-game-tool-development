#include		<iostream>
#include		<cstdlib>
#include		"Server.hpp"
#include		"FDSet.hpp"
#include		"Select.hpp"

Server::Server()
{
}

Server::~Server()
{
}

bool			Server::init()
{
	if (SocketTCP::start() == false)
	{
		std::cerr << "[ERROR] : Initialization of the server failed." << std::endl;
		return (false);
	}
	return (true);
}

bool			Server::create(const std::string& listenHost, int listenPort)
{
	if (this->_server.create(listenHost, listenPort) == false)
	{
		std::cerr << "[ERROR] : Creation of the server failed." << std::endl;
		return (false);
	}
	return (true);
}

void			Server::run(const std::string& listenHost, int listenPort)
{
	FDSet			fdSet;
	char		buf[1024];
	int			bytesRecv;
	Client*		client;

	if (this->init() == false)
		return;
	if (this->create(listenHost, listenPort) == false)
		return;
	while (true)
	{
		fdSet.zero();
		fdSet.set(&this->_server);
		for (unsigned int i = 0; i < this->_clients.size(); i++)
		{
			fdSet.set(this->_clients[i]->getSocketTCPClient());
		}
		Select::call(&fdSet, NULL);
		if (fdSet.isset(&this->_server))
		{
			client = new Client;
			client->setSocketTCPClient(this->_server.acceptClient());//VERIFIER ACCEPTCLIENT
			this->_clients.push_back(client);
		}
		for (unsigned int i = 0; i < this->_clients.size(); i++)
		{
			if (fdSet.isset(this->_clients[i]->getSocketTCPClient()))
			{
				if ((bytesRecv = this->_clients[i]->getSocketTCPClient()->receive(buf, 1024)) == 0)
				{
					this->_clients[i]->getSocketTCPClient()->close();
					delete (this->_clients[i]);
					this->_clients.erase(this->_clients.begin() + i);
				}
				buf[bytesRecv] = '\0';
				std::cout << buf << std::endl;
				for (unsigned int j = 0; j < this->_clients.size(); j++)
				{
					this->_clients[j]->getSocketTCPClient()->send(buf, bytesRecv);
				}
			}
		}
	}
}
