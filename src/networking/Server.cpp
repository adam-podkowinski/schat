#include "networking/Server.h"

#include <unistd.h>

#include <cstring>

#define PORT 6969

Server::Server() { std::cout << "Hello from server 🖥️ " << std::endl; }

Server::~Server() {}

bool Server::host(int port) {
  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    return false;
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    return false;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    return false;
  }
  if (::listen(server_fd, 3) < 0) {
    perror("listen");
    return false;
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    return false;
  }

  return true;
}

bool Server::sendMessage(const char *message) {
  if (send(new_socket, message, strlen(message), 0) < 0) {
    printf("\n Failed to send message (SERVER) \n");
    return false;
  }
  return true;
}

std::string Server::listen() {
  char readBuffer[1024] = {0};
  if (read(new_socket, readBuffer, 1024) < 0) {
    return "ERROR listening for input (SERVER)";
  }
  return readBuffer;
}
