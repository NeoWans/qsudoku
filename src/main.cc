#include "mainwindow.h"
#include <QApplication>

#include "neocc.h"

#include "getopt.h"

static int c = 0;
static std::string s;
static int n = 0;
static int m = 0;
static int r = 0;
static int R = 0;
static bool u = false;

static constexpr unsigned order = 3;
static constexpr unsigned sorder = order * order;
static constexpr unsigned ssorder = sorder * sorder;

static solve_sudoku_t sudoku;

[[noreturn]] void usage_error() {
  exit(EXIT_FAILURE);
}

bool solve_puzzle_helper() {
  using namespace std;
  auto puzzle = make_unique<int[]>(ssorder);
  int n;
  unsigned i = 0;
  while (cin >> n) {
    puzzle[i++] = n;
    if (i >= ssorder) break;
  }
  if (i < ssorder) return false;
  auto ans = sudoku.solve(puzzle.get());

  for (unsigned i = 0; i < sorder; ++i)
    for (unsigned j = 0; j < sorder; ++j) {
      cout << ans[i * sorder + j] << " \n"[j + 1 == sorder];
    }
  cout << endl;
  return true;
}

void gen_batched_puzzle() {
  using namespace std;
  for (int i = 0; i < n; ++i) {
    int* sol;
    int* puzzle;
    if (m) {
      auto res = sudoku.create_sudoku(m);
      sol = res.first;
      puzzle = res.second;
    } else {
      int* sol;
      do {
        sol = sudoku.generate_solution();
      } while (sol == nullptr);
      puzzle = sudoku.generate_puzzle(r, R);
    }
    for (unsigned i = 0; i < sorder; ++i)
      for (unsigned j = 0; j < sorder; ++j) {
        cout << puzzle[i * sorder + j] << " \n"[j + 1 == sorder];
      }
    cout << endl;
  }
}

void gen_final() {
  using namespace std;
  for (int i = 0; i < c; ++i) {
    int* sol;
    do {
      sol = sudoku.generate_solution();
    } while (sol == nullptr);
    for (unsigned i = 0; i < sorder; ++i)
      for (unsigned j = 0; j < sorder; ++j) {
        cout << sol[i * sorder + j] << " \n"[j + 1 == sorder];
      }
    cout << endl;
  }
}

void solve_puzzle() {
  using namespace std;
  ifstream _ifs;
  cinbuf_keeper_t _cin_buf;
  if (s != "-") {
    _ifs.open(s);
    _cin_buf = cin.rdbuf(_ifs.rdbuf());
  }

  ofstream _ofs("sudoku.txt");
  coutbuf_keeper_t _cout_buf = cout.rdbuf(_ofs.rdbuf());

  while (solve_puzzle_helper()) NULL;
}

signed main(int argc, char* argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  if (argc == 1 || (argc == 2 && argv[1] == std::string("gui"))) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
  }
  int opt;
  while (~(opt = getopt(argc, argv, "c:s:n:m:r:R:u"))) {
    switch (opt) {
      case 'c' :
        c = atoi(optarg);
        if (c < 1 || c > 1000000) usage_error();
        break;
      case 's' : s = optarg; break;
      case 'n' :
        n = atoi(optarg);
        if (n < 1 || n > 10000) usage_error();
        break;
      case 'm' :
        m = atoi(optarg);
        if (m < 1 || m > 3) usage_error();
        break;
      case 'r' :
        r = atoi(optarg);
        if (r < 20 || r > 55) usage_error();
        break;
      case 'R' :
        R = atoi(optarg);
        if (R < 20 || R > 55) usage_error();
        break;
      case 'u' : u = true; break;
      default : break;
    }
  }
  if (n && !(((!!m) ^ (!!r)))) usage_error();
  if ((!!r) ^ (!!R)) usage_error();
  if (r > 0 && r > R) usage_error();

  if (c) gen_final();
  else if (!s.empty()) solve_puzzle();
  else if (n) gen_batched_puzzle();
}
