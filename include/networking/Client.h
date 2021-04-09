#pragma once
#include <iostream>

class Client {
 public:
 private:
  int sock = 0;
  struct sockaddr_in serv_addr;

 public:
  Client();
  virtual ~Client();

  std::string listen();
  bool sendMessage(const char* message);
  bool connectSocket(const char* ip, int port);
};
