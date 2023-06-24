#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  NULL;
}

MainWindow::~MainWindow() {
  NULL;
}

void MainWindow::launch() {
  for (auto& component : componentList) component.show();
}
