#include		"Client.hpp"

Client::Client()
{
}

Client::~Client()
{
}


void			Client::setSocketTCPClient(SocketTCPClient* socketTCPClient)
{
  this->_socketTCPClient = socketTCPClient;
}

SocketTCPClient*	Client::getSocketTCPClient() const
{
  return (this->_socketTCPClient);
}