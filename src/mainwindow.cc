#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  // welcomeActivity();
  gameActivity();
}

MainWindow::~MainWindow() {
  NULL;
}

void MainWindow::launch() {
  if (fitComponent != nullptr) (this->*fitComponent)();
}

void MainWindow::resizeEvent(QResizeEvent* ev) {
  launch();
}
