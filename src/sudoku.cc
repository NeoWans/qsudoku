#include "sudoku.h"

void solve_sudoku_t::print(int* now) {
  for(int i = 0; i < 9; i ++) {
        for(int j = 0; j < 9; j ++) {
            std::cout << *now++ << " ";
        }
        std::cout << "\n";
    } 
}

int solve_sudoku_t::get_id(int row, int col, int num) {
  return (row - 1) * 9 * 9 + (col - 1) * 9 + num;
}

void solve_sudoku_t::insert(int row, int col, int num) {
  int dx = (row - 1) / 3 + 1;
  int dy = (col - 1) / 3 + 1;
  int room = (dx - 1) * 3 + dy;
  int id = get_id(row, col, num);
  int f1 = (row - 1) * 9 + num;            // task 1
  int f2 = 81 + (col - 1) * 9 + num;       // task 2
  int f3 = 81 * 2 + (room - 1) * 9 + num;  // task 3
  int f4 = 81 * 3 + (row - 1) * 9 + col;   // task 4
  solver.insert(id, f1);
  solver.insert(id, f2);
  solver.insert(id, f3);
  solver.insert(id, f4);
}

int solve_sudoku_t::pos(int i, int j) {
  return (i - 1) * 9 + j - 1;
}

int* solve_sudoku_t::solve(int* now) {
  solver.build(729, 324);
  static int tmp[81];
  for(int i = 0; i < 81; i ++)
    tmp[i] = now[i];
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j) {
      for (int v = 1; v <= 9; ++v) {
        if (tmp[pos(i, j)] && tmp[pos(i, j)] != v) continue;
        insert(i, j, v);
      }
    }
  if(solver.dance(1, tmp))
    return tmp;
  return nullptr;
}

int* solve_sudoku_t::create_sudoku_table() {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_int_distribution dist(1, 9);
  std::set<int> s;
  for (int p = 1; p <= init_cnt;) {
    int i = dist(mt);
    int j = dist(mt);
    int k = dist(mt);
    int room = (i - 1) * 3 + j;
    int f1 = (i - 1) * 9 + k;              // task 1
    if (s.find(f1) != s.end()) continue;
    int f2 = 81 + (j - 1) * 9 + k;         // task 2
    if (s.find(f2) != s.end()) continue;
    int f3 = 81 * 2 + (room - 1) * 9 + k;  // task 3
    if (s.find(f3) != s.end()) continue;
    int f4 = 81 * 3 + (i - 1) * 9 + j;     // task 4
    if (s.find(f4) != s.end()) continue;
    s.insert(f1);
    s.insert(f2);
    s.insert(f3);
    s.insert(f4);
    field[(i - 1) * 9 + j - 1] = k;
    p++;
  }
  return solve(field);
}

bool solve_sudoku_t::check_unique(int r, int c, int now[81]) {
  // 挖掉第一个位置一定有唯一解
  if (r == 1 && c == 1) return true;

  int tfield[81];

  // 临时数组
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      tfield[pos(i, j)] = now[pos(i, j)];
    }
  }
  // 假设挖掉这个数字
  tfield[pos(r, c)] = 0;

  for (int i = 1; i <= 9; i++)
    if (i != now[pos(r, c)]) {
      tfield[pos(r, c)] = i;
      if (solve(tfield) != nullptr) return false;
      tfield[pos(r, c)] = 0;
    }
  // 已尝试所有其他数字发现无解即只有唯一解
  return true;
}

int* solve_sudoku_t::generate_puzzle(int low, int high) {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_int_distribution dist(low, high);
  std::uniform_int_distribution position(1, 9);
  int n = dist(mt);
  static int tmp[81];
  for (int i = 1; i <= 9; i++)
    for (int j = 1; j <= 9; j++) tmp[pos(i, j)] = field[pos(i, j)];
  while(n) {
    int i = position(mt);
    int j = position(mt);
    if(tmp[pos(i, j)] == 0) continue;
    if(check_unique(i, j, tmp)) {
      tmp[pos(i, j)] = 0;
      n --;
    }
  }
  return tmp;
}

std::pair<int*, int*> solve_sudoku_t::create_sudoku(int level) {
  int init_cnt_low;
  int init_cnt_high;
  switch (level) {
    case 1 :
      init_cnt_low = 20;
      init_cnt_high = 24;
      break;

    case 2 :
      init_cnt_low = 25;
      init_cnt_high = 28;
      break;

    case 3 :
      init_cnt_low = 29;
      init_cnt_high = 32;
      break;
  }
  int* solution = create_sudoku_table();
  while(solution == nullptr) {
    solution = create_sudoku_table();
  };
  for(int i = 0; i < 81; i ++)
    field[i] = solution[i];
  int* puzzle = generate_puzzle(init_cnt_low, init_cnt_high);
  return std::make_pair(field, puzzle);
}