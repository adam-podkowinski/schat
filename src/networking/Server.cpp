#include "networking/Server.h"

#include <cstring>

Server::Server() {}

Server::~Server() {}

std::string getLocalIP() {
  int sock = socket(PF_INET, SOCK_DGRAM, 0);
  sockaddr_in loopback;

  if (sock == -1) {
    std::cerr << "Could not socket\n";
    return "error";
  }

  std::memset(&loopback, 0, sizeof(loopback));
  loopback.sin_family = AF_INET;
  loopback.sin_addr.s_addr = 1337;  // can be any IP address
  loopback.sin_port = htons(9);     // using debug port

  if (connect(sock, reinterpret_cast<sockaddr *>(&loopback),
              sizeof(loopback)) == -1) {
    close(sock);
    std::cerr << "Could not connect\n";
    return "error";
  }

  socklen_t addrlen = sizeof(loopback);
  if (getsockname(sock, reinterpret_cast<sockaddr *>(&loopback), &addrlen) ==
      -1) {
    close(sock);
    std::cerr << "Could not getsockname\n";
    return "error";
  }

  close(sock);

  char buf[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
    std::cerr << "Could not inet_ntop\n";
    return "error";
  } else {
    return buf;
  }
}

bool Server::host(int port) {
  // Creating socket file descriptor
  std::cout << NC "Creating socket...\n";
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    return false;
  }

  std::cout << GRN "Socket created successfully.\n";

  std::cout << NC "Setting socket setsockopt...\n";
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    return false;
  }
  std::cout << GRN "setsockopt successfull.\n";

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  std::cout << NC "Binding socket...\n";
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror(RED "bind failed");
    return false;
  }
  std::cout << GRN "Binding socket successful.\n";

  // TODO: print non-loopback localhost address

  // Getting local ip address
  std::string localIP = getLocalIP();

  std::cout << CYN "Listening for connection to this IP ( " << localIP << ":"
            << port << " )...\n";

  if (::listen(server_fd, 3) < 0) {
    perror(RED "listen");
    return false;
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror(RED "accept");
    return false;
  }
  std::cout << GRN "Client " << inet_ntoa(address.sin_addr) << " connected.\n";

  return true;
}

bool Server::sendMessage(const char *message) {
  if (send(new_socket, message, strlen(message), 0) < 0) {
    printf(RED "\n Failed to send message (SERVER) \n");
    return false;
  }
  return true;
}

std::string Server::listen() {
  char readBuffer[1024] = {0};
  if (recv(new_socket, readBuffer, 1024, 0) <= 0) {
    return RED "ERROR listening for input (SERVER)";
  }
  return readBuffer;
}
