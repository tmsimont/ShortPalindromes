// copyright 2016 Trevor Simonton
#include <iostream>
#include <list>
#include <string>
#include "base/dp.h"


DP::PDSolver::PDSolver(std::string s) {
  str = s;
  // build the DP score chart into the std::map called grid
  auto i = str.begin();
  while (i != str.end()) {  // every character has a row
    auto ii = str.end() - 1;
    while (ii >= i) {  // we have columns only up to the minor diagonal
      grid.insert({{relidx(i)+1, str.size()-relidx(ii)}, Cell(*i, *ii)});
      --ii;
    }
    ++i;
  }
}

void DP::PDSolver::calcChart() {
  // base cases
  int i = 0;
  while (i <= str.size()) {
    grid[{0, i}].score = i;
    grid[{i, 0}].score = i;
    if (i > 0) {
      setBaseCase(INSERT_FWD, &grid[{0, i}], &grid[{0, i-1}]);
      setBaseCase(INSERT_BKWD, &grid[{i, 0}], &grid[{i-1, 0}]);
    }
    ++i;
  }

  // fill out rest of chart
  i = 1;
  while (i <= str.size()) {
    int k  = 1;
    while (k <= str.size() - i + 1) {
      // get pointers to up, left, diag cells in grid
      Cell *diag = &grid[{i-1, k-1}];
      Cell *up = &grid[{i-1, k}];
      Cell *left = &grid[{i, k-1}];

      // reference for readability
      Cell &current = grid[{i, k}];

      // we can only use diag if diag is a match
      bool canUseDiag = !diag->isBase && diag->fwd == diag->bkwd;

      // cellscore is probably +1, might be reset
      int cellScore = 1;

      // assume to use cell that is up from here
      Cell *previous = up;
      int action = INSERT_BKWD;

      if (canUseDiag && diag->score < up->score) {
        previous = diag;
        action = MATCH;

        // cellscore is still 1 unless this cell is a match
        cellScore = diag->fwd != diag->bkwd;
      }

      if (left->score < previous->score) {
        previous = left;
        action = INSERT_FWD;
        cellScore = 1;
      }

      // did we reach the end of the palindrome?
      if (k == str.size() - i + 1
            && previous->fwd == previous->bkwd
            && previous->fwd == current.fwd
            && current.fwd == current.bkwd) {
          // this cell doesn't require any modification to the string
          cellScore = 0;
          action = FINISH;
      }

      // save score and chain of events
      current.score = cellScore + previous->score;
      current.action = action;
      current.previous = previous;
      current.history = previous->history;
      current.history.push(previous);
      ++k;
    }

    // maintain a pointer to the best score along the diagonal of chart
    --k;
    if (i == 1) {
      currentBest = &grid[{i, k}];
    } else if (grid[{i, k}].score < currentBest->score) {
      currentBest = &grid[{i, k}];
    }

    ++i;
  }

  // initial cell is special
  grid[{0, 0}].action = START;
}

std::string DP::PDSolver::getSolution(bool print) {
  // first we build our DP chart scores
  calcChart();

  // show the scores if asked to do so
  if (print)
    printGrid(this);

  // currentBest now points to the best scoring cell in the grid
  Cell *c = currentBest;

  // add currentBest to its own history of best moves
  c->history.push(c);

  // we now build a solution string by moving through the
  // history of best moves contained in the best scoring
  // cell in the chart.

  // use a char list that won't invalidate iterators on inserts
  std::list<char> l;
  for (const auto &c : str) {
    l.push_back(c);
  }

  // f for front, e for end
  std::list<char>::iterator f = l.begin();
  std::list<char>::iterator e = l.end();

  // adjust initial positions to prepare for "insert after" actions
  f--;  // use for insert, do not de-reference before moving forward!
  e++;

  // walk through winning chart path
  while (!c->history.empty()) {
    Cell *h = c->history.front();

    switch (h->action) {
      case INSERT_FWD:
        // insert after forward pointer
        l.insert(f, h->previous->bkwd);

        // we just handled the letter e is pointing to
        --e;

        if (print)
          std::cout << "ins "
             << h->previous->bkwd
             << " before frnt" << std::endl;

        break;

      case INSERT_BKWD:
        // insert after end pointer
        l.insert(e, h->previous->fwd);

        // put e in front of new character
        --e;

        // we just handled the letter f is pointing to
        ++f;

        if (print)
          std::cout << "ins "
             << h->previous->fwd
             << " after end" << std::endl;

        break;

      case MATCH:
        // no insert necessary, move both pointers inward
        --e;
        ++f;
        break;

      case START:
        // do nothing on initial cell
        break;

      default:
        break;
    }

    c->history.pop();
  }

  // build the solution string from the char list
  std::string solution;
  for (const auto &c : l) {
    solution.push_back(c);
  }

  return solution;
}

void DP::printGrid(PDSolver* solver) {
  // print all grid elements
  int p = 0;
  int q = 0;
  while (p <= solver->str.size()) {
    q = 0;
    while (q <= solver->str.size() - p + (p > 0)) {
      if (9 && solver->grid[{p, q}].score < 10) {
        std::cout << " ";
      }
      if (solver->grid[{p, q}].score < 100) {
        std::cout << " ";
      }
      if (&solver->grid[{p, q}] == solver->currentBest)
        std::cout << "*";
      else
        std::cout << " ";
      std::cout << solver->grid[{p, q}].score << " ";
      ++q;
    }
    std::cout << std::endl;
    ++p;
  }
}

// helper to set properties of base case cell
void DP::setBaseCase(int action, Cell *cell, Cell *prev) {
  cell->history = prev->history;
  cell->previous = prev;
  cell->history.push(cell->previous);
  prev->action = action;
  cell->isBase = true;
}
