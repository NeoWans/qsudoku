#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "getopt.h"

[[noreturn]] void usage_error() {
  exit(EXIT_FAILURE);
}

signed main(int argc, char* argv[]) {
  if (argc == 1) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
  }
  int opt;
  int c = 0;
  std::string s;
  int n = 0;
  int m = 0;
  int r = 0;
  bool u = false;
  while (~(opt = getopt(argc, argv, "c:s:n:m:r:u"))) {
    switch (opt) {
      case 'c' :
        c = atoi(optarg);
        if (c < 1 || c > 1000000) usage_error();
        break;
      case 's' : s = optarg; break;
      case 'n' :
        n= atoi(optarg);
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
      case 'u' : u = true; break;
      default : break;
    }
  }
  if ((!!m) ^ (!!n) || (!!r) ^ (!!n) || (!!u) ^ (!!n)) usage_error();
}
