#pragma once
#include <netinet/in.h>
#include <iostream>

class Server {
 private:
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  static constexpr int addrlen = sizeof(address);
  char readBuffer[1024] = {0};

 public:
  Server();
  virtual ~Server();

  bool host(int port);
  std::string listen();
};
