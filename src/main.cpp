#include "SChat.h"

int main(int argc, char const *argv[]) {
  SChat schat;

  if (!schat.Run(argc, argv)) {
    std::cout << "Good bye";
  }

  std::cout << "Exiting" << std::endl;

  return 0;
}
