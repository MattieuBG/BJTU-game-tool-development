#ifndef			CLIENT_HPP_
# define		CLIENT_HPP_

# include		<string>
# include		"SocketTCPClient.hpp"

class			Client
{
public:

  Client();
  ~Client();

  void			setSocketTCPClient(SocketTCPClient* socketTCPClient);

  SocketTCPClient*	getSocketTCPClient() const;

private:

  SocketTCPClient*	_socketTCPClient;
};

#endif			// CLIENT_HPP_
