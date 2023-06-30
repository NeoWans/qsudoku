#include "mainwindow.h"

#include <QPushButton>

#include "neocc.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  driverSudoku.reset(new solve_sudoku_t);
  // welcomeActivity();
  gameActivity();
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

int MainWindow::gameFill(unsigned i) {
  if (gameButtonSelected == -1) return 1;

  if (!(i >= 1 && i < 10)) i = 0;

  game[i] = i;
  auto btn =
    dynamic_cast<QPushButton*>(componentList[gameButtonSelected].get());
  if (i) btn->setText(toStr(i).c_str());
  else btn->setText("");

  return 0;
}

void MainWindow::keyPressEvent(QKeyEvent* ev) {
  auto key = ev->key();

  if (gameButtonSelected == -1) return;

  int index = gameButtonSelected;
  int sorder = square(sudokuOrder);
  int ssorder = square(sorder);

  switch (key) {
    case Qt::Key_1 : gameFill(1); break;
    case Qt::Key_2 : gameFill(2); break;
    case Qt::Key_3 : gameFill(3); break;
    case Qt::Key_4 : gameFill(4); break;
    case Qt::Key_5 : gameFill(5); break;
    case Qt::Key_6 : gameFill(6); break;
    case Qt::Key_7 : gameFill(7); break;
    case Qt::Key_8 : gameFill(8); break;
    case Qt::Key_9 : gameFill(9); break;
    case Qt::Key_Backspace : gameFill(0); break;
    case Qt::Key_A :
      for (int i = index - 1; i >= 0; --i) {
        if (game[i] == 0) {
          index = i;
          break;
        }
      }
      break;
    case Qt::Key_D :
      for (int i = index + 1; i < ssorder; ++i) {
        if (game[i] == 0) {
          index = i;
          break;
        }
      }
      break;
    case Qt::Key_W :
      for (int i = index - sorder; i >= 0; --i) {
        if (game[i] == 0) {
          index = i;
          break;
        }
      }
      break;
    case Qt::Key_S :
      for (int i = index + sorder; i < ssorder; ++i) {
        if (game[i] == 0) {
          index = i;
          break;
        }
      }
      break;
    default : break;
  }
  if (index != gameButtonSelected) {
    auto btn = dynamic_cast<QPushButton*>(componentList[index].get());
    btn->click();
  }
}
