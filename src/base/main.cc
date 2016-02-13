// copyright 2016 Trevor Simonton
#include <iostream>
#include "base/dp.h"

int main(int argc, char **argv) {
  bool print = argc == 3;
  if (argc >= 2) {
    DP::PDSolver solver(argv[1]);
    std::cout << solver.getSolution(print) << std::endl;
  } else {
    DP::PDSolver solver("race");
    std::cout << solver.getSolution(print) << std::endl;
  }
}


