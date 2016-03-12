#include <iostream>
#include "SocketTCPClient.hpp"
#include "./Select/FDSet/FDSet.hpp"
#include "./Select/Select.hpp"

int main(int ac, char **av) {
  SocketTCPClient client;

  if (ac != 3)
    {
      std::cout << "./client host port" << std::endl;
      return (0);
    }
  client.start();
  client.connectToServer(av[1], atoi(av[2]));


  FDSet fdSet;
  char buff[1024];
  std::string entry;
  int nbRead;

  while (true)
    {
      fdSet.zero();
      fdSet.set(&client);
      fdSet.set(0);
      Select::call(&fdSet, NULL);
      if (fdSet.isset(&client))
	{
	  if ((nbRead = client.receive(buff, 1024)) == 0)
	    {
	      client.close();
	      std::cout << "Server left" << std::endl;
	      return 0;
	    }
	  std::cout << "msg : " << buff << std::endl;
	  memset(buff, 0, 1024);
	}
      while (fdSet.isset(0))
	{
	  std::cin >> entry;
	  client.send(entry.c_str(), entry.length());
	}
      
    }
}
