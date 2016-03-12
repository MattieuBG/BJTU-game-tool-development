#ifndef			LOBBY_HPP_
# define		LOBBY_HPP_

# include		<vector>
# include		<string>
#include "../Socket/SocketTCPClient.hpp"

class			Lobby
{
public:

  Lobby();
  ~Lobby();

  void			run();

private:

  bool			connectToServer();
  static void*			readInput(void *arg);

  SocketTCPClient		_client;
  std::vector<std::string>	_listPlayer;
  std::vector<int>		_status;
};

#endif			// LOBBY_HPP_
