#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include "neocc.h"

void MainWindow::welcomeActivity() {
  componentList.clear();
  fitComponent = &MainWindow::fitWelcomeComponent;

  setWindowFlags(
    windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
  // TODO
  // setAttribute(Qt::WA_TranslucentBackground);

  int aw = welcomeDefaultWidth;
  int ah = welcomeDefaultHeight;
  auto desktop = QApplication::desktop();
  setGeometry(
    (desktop->width() - aw) / 2, (desktop->height() - ah) / 2, aw, ah);
  setFixedSize(aw, ah);

  launch();
}

void MainWindow::fitWelcomeComponent() {

}