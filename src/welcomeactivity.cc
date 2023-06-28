#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>

#include "neocc.h"

void MainWindow::welcomeActivity() {
  componentList.clear();
  fitComponent = nullptr;

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

  auto btn = new QPushButton(this);
  btn->setText("Start");
  connect(btn, &QPushButton::clicked, this, &MainWindow::gameActivity);
  componentList.emplace_back(btn);

  fitComponent = &MainWindow::welcomeFitComponent;
  launch();
}

void MainWindow::welcomeFitComponent() {
  static constexpr int padding = 8;
  static constexpr int sw = 70;
  static constexpr int sh = 50;

  const auto sz = size();
  const auto gw = sz.width();
  const auto gh = sz.height();

  auto startBtn = componentList[0].get();
  startBtn->setGeometry(gw - sw - padding, gh - sh - padding, sw, sh);
}