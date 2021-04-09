#include "networking/Client.h"

#include <cstdio>
#include <cstring>
#include <string>

#define PORT 6969

Client::Client() {}

Client::~Client() {}

std::string Client::listen() {
  char readBuffer[1024] = {0};
  if (recv(sock, readBuffer, sizeof(readBuffer), 0) < 0) {
    return "ERROR listening for input (CLIENT)";
  }
  return readBuffer;
}

bool Client::sendMessage(const char *message) {
  if (send(sock, message, strlen(message), 0) < 0) {
    printf("\n Failed to send message (CLIENT) \n");
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

  std::cout << "Connected to server: " << ip << ":" << port << std::endl;

  return true;
}
