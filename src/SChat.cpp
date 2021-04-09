#include "./SChat.h"
#include "./networking/Client.h"
#include "./networking/Server.h"

#include <iostream>

SChat::SChat() {}

SChat::~SChat() {}

constexpr unsigned int str2int(const char* str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

bool SChat::Run(int argc, const char* argv[]) {
  switch (str2int(argv[1])) {
    case str2int("client"):
      std::cout << "Running as Client" << std::endl;
      //Client client;
      break;
    case str2int("server"):
      std::cout << "Running as Server" << std::endl;
      //Server server;
      break;
    default:
      std::cout << "Unrecognized argument" << std::endl;
  }

  return true;
}
