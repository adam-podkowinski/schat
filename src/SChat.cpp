#include "./SChat.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

SChat::SChat() {}

SChat::~SChat() {}

bool SChat::serverListen(Server *server) {
  while (true) {
    std::tuple result = server->listen();
    if (!std::get<0>(result)) {
      std::cout << RED "Error while listening to server messages!\n\n";
      return false;
    } else {
      std::cout << CYN << std::endl
                << server->getClientIP() << ":"
                << " says: " << std::get<1>(result) << std::endl;
    }
  }

  return true;
}

bool SChat::serverSend(Server *server) {
  std::string messageToSend;
  std::cin.ignore(2, '\n');
  while (true) {
    std::cout << CYN "\nWhat to send to client: ";
    std::getline(std::cin, messageToSend);
    if (messageToSend == "close") {
      server->closeServer();
      return false;
    }
    if (!server->sendMessage(messageToSend.c_str())) {
      server->closeServer();
      return false;
    }
  }

  return true;
}

bool SChat::clientListen(Client *client, int port) {
  while (true) {
    std::tuple result = client->listen();
    if (!std::get<0>(result)) {
      std::cout << RED "Error while listening to server messages!\n\n";
      return false;
    } else {
      std::cout << CYN << std::endl
                << client->getServerIP() << ":" << port
                << " says: " << std::get<1>(result) << std::endl;
    }
  }

  return true;
}

bool SChat::clientSend(Client *client) {
  std::string messageToSend;
  std::cin.ignore(2, '\n');
  while (true) {
    std::cout << CYN "\nWhat to send to server: ";
    std::getline(std::cin, messageToSend);
    if (messageToSend == "close") {
      client->closeClient();
      return false;
    }
    if (!client->sendMessage(messageToSend.c_str())) {
      client->closeClient();
      return false;
    }
  }

  return true;
}

bool SChat::clientRun(const char *ip, int port) {
  Client client;
  if (!client.connectSocket(ip, port)) {
    std::cout << RED "Couldn't connect to server!" << std::endl;
    return false;
  }
  std::thread clientListenThread(&SChat::clientListen, this, &client, port);
  std::thread clientSendThread(&SChat::clientSend, this, &client);

  clientListenThread.join();
  clientSendThread.join();

  return true;
}
bool SChat::serverRun(int port) {
  Server server;
  if (!server.host(port)) {
    std::cout << RED "Couldn't host server." << std::endl;
    return false;
  }
  std::thread serverListenThread(&SChat::serverListen, this, &server);
  std::thread serverSendThread(&SChat::serverSend, this, &server);

  serverListenThread.join();
  serverSendThread.join();

  return true;
}

bool SChat::Run(int argc, const char *argv[]) {
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
        if (!clientRun(connectToIP.c_str(), connectToPort)) {
          sleep(2);
        }

        std::cout << "\033[2J\033[1;1H";
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
          std::cout << RED "\nGive PORT as an integer.";
          goto getPORT;
        }
        std::cout << CYN "\nRUNNING SERVER ON PORT: " << port << std::endl;
        if (!serverRun(port)) {
          sleep(3);
        }
        std::cout << "\033[2J\033[1;1H";
      }
    } else {
      std::cout << RED "\nUnrecognized option!\n" << std::endl;
      return false;
    }
  }

  return true;
}
