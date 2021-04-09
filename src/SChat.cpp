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

bool SChat::Run(int argc, const char* argv[]) {
  std::cout << "\033[2J\033[1;1H";

  if (argv[1] != nullptr) {
    if (strcmp(argv[1], "client") == 0) {
      Client client;
      if (!client.connectSocket("127.0.0.1", 6969)) {
        std::cout << "Couldn't connect to server!" << std::endl;
        return false;
      }
      while (true) {
        std::string message = client.listen();
        std::cout << message << std::endl;
      }
    } else if (strcmp(argv[1], "server") == 0) {
      Server server;
      if (!server.host(6969)) {
        std::cout << "Quiting because of server errors" << std::endl;
        return false;
      }
      std::string messageToSend = "";
      while (true) {
        std::cout << "What to send to client: ";
        getline(std::cin, messageToSend);
        if (!server.sendMessage(messageToSend.c_str())) {
          std::cout << "Failed to send a message" << std::endl;
        }
      }
    } else {
      std::cout << "Unrecognized option!" << std::endl;
      return false;
    }
  }

  return true;
}
