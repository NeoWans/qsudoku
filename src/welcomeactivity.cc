#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

void MainWindow::welcomeActivity() {
  componentList.clear();

  setWindowFlags(
    windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
  // TODO
  // setAttribute(Qt::WA_TranslucentBackground);

  int aw = welcomeWidth;
  int ah = welcomeHeight;
  auto desktop = QApplication::desktop();
  setGeometry(
    (desktop->width() - aw) / 2, (desktop->height() - ah) / 2, aw, ah);
  setFixedSize(aw, ah);

  launch();
}