// copyright 2016 Trevor Simonton
#ifndef BASE_DP_H_
#define BASE_DP_H_

#include <string>
#include <map>
#include <queue>
#include <utility>

namespace DP {

enum CellAction {
  INSERT_BKWD,
  INSERT_FWD,
  MATCH,
  START,
  FINISH,
};

struct Cell {
  Cell() = default;
  Cell(char f, char b):fwd(f), bkwd(b) {}
  Cell *previous;
  int score;
  char fwd;
  char bkwd;
  int action = INSERT_BKWD;
  bool isBase = false;
  std::queue<Cell*> history;
};

class PDSolver {
friend void printGrid(PDSolver* solver);
friend void setBaseCase(int action, Cell *cell, Cell *prev);
 public:
  explicit PDSolver(std::string s);
  std::string getSolution(bool print);
 private:
  std::string str;
  std::map<std::pair<int, int>, Cell> grid;
  int relidx(std::string::iterator i) {
    return str.size() - 1 - (str.end()-i-1);
  }
  void calcChart();
  Cell *currentBest;
};

void printGrid(PDSolver* solver);
void setBaseCase(int action, Cell *cell, Cell *prev);

};  // namespace DP

#endif  // BASE_DP_H_
