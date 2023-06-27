#include "sudoku.h"

int solve_sudo_t::get_id(int row, int col, int num) {
  return (row - 1) * 9 * 9 + (col - 1) * 9 + num;
}

void solve_sudo_t::insert(int row, int col, int num) {
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

int* solve_sudo_t::solve(int now[][10]) {
  solver.build(729, 324);
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j) {
      for (int v = 1; v <= 9; ++v) {
        if (now[i][j] && now[i][j] != v) continue;
        insert(i, j, v);
      }
    }
  solver.dance(1, now);
  return get_ans(now);
}

int* solve_sudo_t::get_ans(int now[][10]) {
  static int res[81];
  for (int i = 1; i <= 9; i++)
    for (int j = 1; j <= 9; j++) {
      res[(i - 1) * 9 + j - 1] = now[i][j];
    }
  return res;
}

int* solve_sudo_t::create_sudo_table() {
  std::mt19937 mt;
  std::uniform_int_distribution dist(1, 9);
  std::set<int> s;
  for (int p = 1; p <= init_cnt;) {
    int i = dist(mt);
    int j = dist(mt);
    int k = dist(mt);
    int room = (i - 1) * 3 + j;
    int f1 = (i - 1) * 9 + k;              // task 1
    if (s.find(f1) == s.end()) continue;
    int f2 = 81 + (j - 1) * 9 + k;         // task 2
    if (s.find(f2) == s.end()) continue;
    int f3 = 81 * 2 + (room - 1) * 9 + k;  // task 3
    if (s.find(f3) == s.end()) continue;
    int f4 = 81 * 3 + (i - 1) * 9 + j;     // task 4
    if (s.find(f4) == s.end()) continue;
    s.insert(f1);
    s.insert(f2);
    s.insert(f3);
    s.insert(f4);
    field[i][j] = k;
    p++;
  }
  solve(field);
  return get_ans(field);
}

bool solve_sudo_t::compare(int a[81], int b[81]) {
  for (int i = 0; i < 81; i++)
    if (a[i] != b[i]) return false;
  return true;
}

bool solve_sudo_t::check_unique(int r, int c, int now[][10]) {
  // 挖掉第一个位置一定有唯一解
  if (r == 1 && c == 1) return true;

  int tfield[10][10];

  // 临时数组
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      tfield[i][j] = now[i][j];
    }
  }
  int* fans = get_ans(field);
  // 假设挖掉这个数字
  tfield[r][c] = 0;

  for (int i = 1; i <= 9; i++)
    if (i != now[r][c]) {
      tfield[r][c] = i;
      if (!compare(fans, solve(tfield))) return false;
    }
  // 已尝试所有其他数字发现无解即只有唯一解
  return true;
}

int* solve_sudo_t::generate_puzzle(int low, int high) {
  std::mt19937 mt;
  std::uniform_int_distribution dist(low, high);
  int n = dist(mt);
  int now[10][10];
  for (int i = 1; i <= 9; i++)
    for (int j = 1; j <= 9; j++) now[i][j] = field[i][j];
  for (int i = 1; i <= 9; i++)
    for (int j = 1; j <= 9; j++) {
      if (n == 0) break;
      if (check_unique(i, j, now)) {
        now[i][j] = 0;
        n--;
      }
    }
}

std::pair<int*, int*> solve_sudo_t::create_sudo(int level) {
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
  int* solution = create_sudo_table();
  int* puzzle = generate_puzzle(init_cnt_low, init_cnt_high);
  return std::make_pair(solution, puzzle);
}