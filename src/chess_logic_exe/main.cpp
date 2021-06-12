#include "boardstate.h"

#include <iostream>

int main(int argc, char *argv[]) {
  chess::BoardState b;
  std::string buffer = "";
  while (buffer != "a1a1") {
    std::cout << b << std::endl;
    std::cin >> buffer;
    chess::Move mv(buffer);
    if (b.isLegal(mv)) {
      b.playMove(mv);
    }
  }
}
