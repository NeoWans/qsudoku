#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>

#include "neocc.h"

void MainWindow::gameActivity() {
  componentList.clear();
  fitComponent = &MainWindow::fitGameComponent;

  int aw = gameDefaultWidth;
  int ah = gameDefaultHeight;
  auto desktop = QApplication::desktop();
  setGeometry(
    (desktop->width() - aw) / 2, (desktop->height() - ah) / 2, aw, ah);

  constexpr int order = 3;
  sudokuOrder = order;

  for (unsigned i = 0; i < square(order); ++i)
    for (unsigned j = 0; j < square(order); ++j) {
      componentList.emplace_back(new QPushButton(this));
    }

  launch();
}

void MainWindow::fitGameComponent() {
  const auto sz = size();
  const auto gw = sz.width();
  const auto gh = sz.height();

  const auto sorder = square(sudokuOrder);

  const unsigned bw = gw / sorder;
  const unsigned bh = gh / sorder;
  
  unsigned blockCounter = 0;

  for (const auto& component : componentList) {
    component->setGeometry(
      bw * (blockCounter / sorder), bh * (blockCounter % sorder), bw, bh);
    ++blockCounter;
  }
}