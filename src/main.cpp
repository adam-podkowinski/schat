#include "SChat.h"
#include <signal.h>

int main(int argc, char const *argv[])
{
  signal(SIGPIPE, SIG_IGN);
#if defined(_WIN32) || defined(WIN32)

  WSADATA wsaData;
  WSAStartup(0x0202, &wsaData);

#endif

  SChat schat;

  if (!schat.Run(argc, argv))
  {
    std::cout << "Good bye";
  }

  std::cout << "Exiting" << std::endl;

  return 0;
}
