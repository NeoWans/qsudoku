#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  welcomeActivity();
}

MainWindow::~MainWindow() {
  NULL;
}

void MainWindow::launch() {
  for (auto& component : componentList) component.show();
}
