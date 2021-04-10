#pragma once

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

  inline void closeServer() {
#if defined(_WIN32) || defined(WIN32)
    WSACleanup();
#endif
    closeSocket(new_socket);
    closeSocket(server_fd);
  }

  inline void closeSocket(int &socketToClose) {
#if defined(_WIN32) || defined(WIN32)
    closesocket(socketToClose);
#else
    ::close(socketToClose);
#endif
  }
};
