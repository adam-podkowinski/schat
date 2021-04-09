#include "./SChat.h"

#include <string.h>

#include <iostream>

#include "./networking/Client.h"
#include "./networking/Server.h"

SChat::SChat() {}

SChat::~SChat() {}

bool SChat::Run(int argc, const char* argv[]) {
  if (argv[1] != nullptr) {
    if (strcmp(argv[1], "client") == 0) {
      Client client;
      client.connectSocket("127.0.0.1", 6969);
      client.listen();
    } else if (strcmp(argv[1], "server") == 0) {
      Server server;
      server.host();
    }
  }

  return true;
}
