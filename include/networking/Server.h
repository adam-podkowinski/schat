#pragma once
#include <netinet/in.h>

#include <iostream>

class Server {
 private:
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

 public:
  Server();
  virtual ~Server();

  bool host(int port);
  bool sendMessage(const char * message);
  std::string listen();
};
