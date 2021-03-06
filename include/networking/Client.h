#pragma once
#include <iostream>
#include <tuple>

class Client {
 public:
 private:
  int sock = 0;
  struct sockaddr_in serv_addr;

 public:
  Client();
  virtual ~Client();

  std::tuple<bool, std::string> listen();
  bool sendMessage(const char* message);
  bool connectSocket(const char* ip, int port);
  std::string getServerIP();

  inline void closeClient() {
#if defined(_WIN32) || defined(WIN32)
    closesocket(thisSocket);
    WSACleanup();
#else
    ::close(sock);
#endif
  }

  inline void closeSocket() {
#if defined(_WIN32) || defined(WIN32)
    closesocket(thisSocket);
    WSACleanup();
#else
    ::close(sock);
#endif
  }
};
