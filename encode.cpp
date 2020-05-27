#include "hufftree.h"

#include <fstream>


int main(int argc, const char** argv) {
  if (argc != 2) {
    std::cout << "Enter a single filename to compress" << std::endl;
    return 0;
  }

  std::ifstream file(argv[1]);




}
