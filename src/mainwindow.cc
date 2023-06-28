#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  driverSudoku.reset(new solve_sudoku_t);
  welcomeActivity();
  // gameActivity();
}

MainWindow::~MainWindow() {
  NULL;
}

void MainWindow::launch() {
  if (fitComponent != nullptr) (this->*fitComponent)();
  for (auto& component : componentList)
    if (component->isHidden()) component->show();
  update();
}

void MainWindow::resizeEvent(QResizeEvent* ev) {
  launch();
}
