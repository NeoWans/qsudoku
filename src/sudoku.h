#include "dancelink.h"

class solve_sudoku_t {
private:
  DLX solver;
  int field[81];
  int init_cnt = 11;
  int get_id(int row, int col, int num);
  void insert(int row, int col, int num);
  int pos(int i, int j);
  int* solve(int now[81]);
  int* create_sudoku_table();
  int* generate_puzzle(int low, int high);
  bool check_unique(int row, int col, int now[81]);

public:
  std::pair<int*, int*> create_sudoku(int level);
  void print(int* now);
};