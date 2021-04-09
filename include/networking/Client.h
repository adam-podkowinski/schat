#pragma once
#include <iostream>

#include <netinet/in.h>
class Client {
 public:
 private:
  int sock = 0;
  struct sockaddr_in serv_addr;
  char readBuffer[1024] = {0};

 public:
  Client();
  virtual ~Client();

  std::string listen();
  bool sendMessage(const char * message);
  bool connectSocket(const char* ip, int port);
};
