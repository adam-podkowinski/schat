#pragma once

#include "networking/Client.h"
#include "networking/Server.h"
class SChat {
 public:
  SChat();
  virtual ~SChat();

  bool Run(int argc, char const *argv[]);
  bool clientRun(const char *ip, int port);
  bool serverRun(int port);

  bool serverSend(Server *server);
  bool serverListen(Server *server);

  bool clientSend(Client *client);
  bool clientListen(Client *client, int port);
};
