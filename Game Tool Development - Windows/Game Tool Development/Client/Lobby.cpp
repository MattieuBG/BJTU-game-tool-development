#include		<iostream>
#include		"Lobby.hpp"
#include		"Select.hpp"
#include		"FDSet.hpp"
#include		"../Thread/Thread.hpp"
Lobby::Lobby()
{
}

Lobby::~Lobby()
{
}


bool			Lobby::connectToServer()
{
	if (this->_client.start() == false)
		return (false);
	if (this->_client.connectToServer("127.0.0.1", 8080) == false)
		return (false);
	return (true);
}

void			Lobby::run()
{
	FDSet			fdSet;
	int			bytesRecv;
	char			buf[102400];
	std::string		input;
	Thread	thread;

	if (this->connectToServer() == false)
		return;
	thread.create(this->readInput, &this->_client);
	while (true)
	{
		fdSet.zero();
		fdSet.set(&this->_client);
		Select::call(&fdSet, NULL);
		if (fdSet.isset(&this->_client))
		{
			bytesRecv = this->_client.receive(buf, 102400);
			buf[bytesRecv] = '\0';
			std::cout << buf << std::endl;
		}
		//std::cin >> input;
		//this->_client.send(input.c_str(), input.length());
	}
	this->_client.close();
}

void*		Lobby::readInput(void *arg)
{
	std::string		input;
	SocketTCPClient* client = (SocketTCPClient*)arg;
	while (true)
	{
		std::cin >> input;
		client->send(input.c_str(), input.length());
	}
}