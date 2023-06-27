#include "dancelink.h"

class solve_sudo_t {
private:
  DLX solver;
  int field[10][10];
  int init_cnt = 11;
  int get_id(int row, int col, int num);
  void insert(int row, int col, int num);
  int* solve(int now[][10]);
  int* create_sudo_table();
  int* generate_puzzle(int low, int high);
  int* get_ans(int now[][10]);
  bool check_unique(int row, int col, int now[][10]);
  bool compare(int* a, int* b);

public:
  std::pair<int*, int*> create_sudo(int level);
};