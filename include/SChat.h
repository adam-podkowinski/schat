#pragma once

class SChat {
 public:
  SChat();
  virtual ~SChat();

 bool Run(int argc, char const *argv[]);
 bool clientRun(const char * ip, int port);
 bool serverRun(int port);
};
