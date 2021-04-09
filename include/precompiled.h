#include <iostream>

#ifdef __unix__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>

#endif
