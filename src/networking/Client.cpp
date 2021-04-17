#include "networking/Client.h"

#include <cstring>

#define PORT 6969

Client::Client() {}

Client::~Client() {}

std::string Client::getServerIP() {
  struct sockaddr_in *pV4Addr = (struct sockaddr_in *)&serv_addr;
  struct in_addr ipAddr = pV4Addr->sin_addr;
  char str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
  return str;
}

std::tuple<bool, std::string> Client::listen() {
  char readBuffer[1024] = {0};
  if (recv(sock, readBuffer, sizeof(readBuffer), 0) <= 0) {
    return std::make_tuple(false, RED "ERROR listening for input (CLIENT)");
  }
  return std::make_tuple(true, readBuffer);
}

bool Client::sendMessage(const char *message) {
  if (send(sock, message, strlen(message), 0) < 0) {
    std::cout << "\n Failed to send message (CLIENT) \n";
    return false;
  }
  return true;
}

bool Client::connectSocket(const char *ip, int port) {
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error (CLIENT) \n");
    return false;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported (CLIENT) \n");
    return false;
  }
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed (CLIENT) \n");
    return false;
  }

  std::cout << GRN "Connected to server: " << ip << ":" << port << std::endl
            << std::endl;

  return true;
}
