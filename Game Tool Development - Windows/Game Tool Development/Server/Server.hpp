#ifndef			SERVER_HPP_
# define		SERVER_HPP_

# include		<vector>
# include		<string>
# include		"SocketTCPServer.hpp"
# include		"Client.hpp"

class			Server
{
public:

  Server();
  ~Server();

  void			run(const std::string& listenHost, int listenPort);

private:

  bool			init();
  bool			create(const std::string& listenHost, int listenPort);

  SocketTCPServer	_server;
  std::vector<Client*>	_clients;
};

#endif			// SERVER_HPP_
