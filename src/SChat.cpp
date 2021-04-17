#include "./SChat.h"

#include <string.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "./networking/Client.h"
#include "./networking/Server.h"

SChat::SChat() {}

SChat::~SChat() {}

bool SChat::clientRun(const char* ip, int port) {
  Client client;
  if (!client.connectSocket(ip, port)) {
    std::cout << RED "Couldn't connect to server!" << std::endl;
    return false;
  }
  while (true) {
    std::tuple result = client.listen();
    if (!std::get<0>(result)) {
      std::cout << RED "Error while listening to server messages!\n\n";
      return false;
    } else {
      std::cout << CYN "127.0.0.1:6969 says: " << std::get<1>(result)
                << std::endl;
    }
  }

  return true;
}
bool SChat::serverRun(int port) {
  Server server;
  if (!server.host(port)) {
    std::cout << RED "Couldn't host server." << std::endl;
    return false;
  }
  std::string messageToSend;
  while (true) {
    std::cout << CYN "What to send to client: ";
    getline(std::cin, messageToSend);
    if (messageToSend == "close") {
      server.closeServer();
      return false;
    }
    if (!server.sendMessage(messageToSend.c_str())) {
      server.closeServer();
      return false;
    }
  }
}

bool SChat::Run(int argc, const char* argv[]) {
  std::cout << "\033[2J\033[1;1H";

  if (argv[1] != nullptr) {
    /* CLIENT */
    if (strcmp(argv[1], "client") == 0) {
      while (true) {
        std::string connectToIP;
        unsigned int connectToPort = 6969;

      getIPandPORT:
        try {
          std::cout << CYN "Connect to IP: ";
          std::cin >> connectToIP;
          std::cout << CYN "Connect to PORT: ";
          std::cin >> connectToPort;
        } catch (...) {
          std::cout << RED "\nGive string IP and int PORT\n";
          goto getIPandPORT;
        }

        std::cout << CYN "\nCONNECTING TO IP " << connectToIP << " AND PORT "
                  << connectToPort << " ...\n";
        clientRun(connectToIP.c_str(), connectToPort);
      }

      /* SERVER */
    } else if (strcmp(argv[1], "server") == 0) {
      while (true) {
        unsigned int port = 6969;
      getPORT:
        try {
          std::cout << CYN "Host on which port: ";
          std::cin >> port;
        } catch (...) {
          std::cout << RED "\nGive PORT as int.";
          goto getPORT;
        }
        std::cout << CYN "\nRUNNING SERVER ON PORT: " << port << std::endl;
        serverRun(port);
        std::cout << std::endl;
      }
    } else {
      std::cout << RED "\nUnrecognized option!\n" << std::endl;
      return false;
    }
  }

  return true;
}
