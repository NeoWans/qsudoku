#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QDialog>
#include <QLabel>

#include "neocc.h"

#include "sudoku.h"

template <typename T>
std::string toStr(const T& i) {
  std::ostringstream oss;
  oss << i;
  return oss.str();
}

template <typename T>
bool arrayEqual(const T& v, const T& w) {
  if (v.size() != w.size()) return false;
  size_t sz = v.size();
  for (size_t i = 0; i < sz; ++i)
    if (v[i] != w[i]) return false;
  return true;
}

void MainWindow::gameActivity() {
  componentList.clear();
  fitComponent = nullptr;

  setWindowFlags(Qt::Window);
  show();
  setMinimumSize(0, 0);
  setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

  int aw = gameDefaultWidth;
  int ah = gameDefaultHeight;
  auto desktop = QApplication::desktop();
  setGeometry(
    (desktop->width() - aw) / 2, (desktop->height() - ah) / 2, aw, ah);

  sudokuOrder = 3;
  const auto order = sudokuOrder;
  sudokuDifficulty = 1;

  // driverSudokuDone.store(false);

  // std::thread sworker([this]() {
  //   const auto order = this->sudokuOrder;
  auto res = this->driverSudoku->create_sudoku(this->sudokuDifficulty);
  const size_t sz = square(square(order));
  this->answer.resize(sz);
  this->game.resize(sz);
  for (size_t i = 0; i < sz; ++i) {
    this->answer[i] = res.first[i];
    this->game[i] = res.second[i];
  }
  //   driverSudokuDone.store(true);
  // });
  // sworker.detach();

  // while (!driverSudokuDone.load()) { }

  answer.resize(square(square(order)));
  game.resize(square(square(order)));

  for (unsigned i = 0; i < square(order); ++i)
    for (unsigned j = 0; j < square(order); ++j) {
      auto btn = new QPushButton(this);
      unsigned index = i * square(order) + j;
      if (game[index] != 0) {
        btn->setDisabled(true);
        btn->setText(toStr(game[index]).c_str());
        btn->setStyleSheet("font-weight: bold;");
      }
      std::cerr << answer[index] << " \n"[j + 1 == square(order)];
      connect(btn, &QPushButton::clicked, this, [this, index]() {
        if (this->gameButtonSelected != -1) {
          this->componentList[this->gameButtonSelected]->setStyleSheet(nullptr);
        }
        this->gameButtonSelected = index;
        this->componentList[index]->setStyleSheet(
          "background-color: lightGray;");

        // std::cerr << index << std::endl;
      });
      componentList.emplace_back(btn);
    }

  for (unsigned i = 0; i < square(order); ++i) {
    auto btn = new QPushButton(this);

    unsigned num = i + 1;

    btn->setText(toStr(num).c_str());

    connect(btn, &QPushButton::clicked, this, [this, num]() {
      if (this->gameButtonSelected == -1) return;

      auto i = this->gameButtonSelected;
      auto btn = dynamic_cast<QPushButton*>(this->componentList[i].get());

      game[i] = num;

      btn->setText(toStr(num).c_str());

      if (arrayEqual(this->game, this->answer)) {
        std::cerr << "Game over" << std::endl;
      }
    });
    componentList.emplace_back(btn);
  }

  fitComponent = &MainWindow::gameFitComponent;
  launch();
}

void MainWindow::gameFitComponent() {
  const auto sz = size();
  const auto gw = sz.width();
  const auto gh = sz.height();

  const auto order = sudokuOrder;
  const auto sorder = square(sudokuOrder);

  const unsigned bw = gw / (sorder + order);
  const unsigned bh = gh / sorder;

  unsigned componentCounter = 0;

  for (auto& component : componentList) {
    if (componentCounter < square(sorder)) {
      auto i = componentCounter;
      component->setGeometry(bw * (i % sorder), bh * (i / sorder), bw, bh);
    } else {
      auto i = componentCounter - square(sorder);
      component->setGeometry(
        bw * (i % order + sorder), bh * (i / order + order), bw, bh);
    }
    ++componentCounter;
  }
}