#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QResizeEvent>
#include <QKeyEvent>

#include <vector>
#include <functional>
#include <memory>

#include "sudoku.h"

class MainWindow final : public QMainWindow {
  Q_OBJECT

private:
  static constexpr int welcomeDefaultWidth = 400;
  static constexpr int welcomeDefaultHeight = 400;

  static constexpr int gameDefaultWidth = 1000;
  static constexpr int gameDefaultHeight = 800;

  int gameButtonSelected = -1;

  std::vector<std::unique_ptr<QWidget>> componentList;
  void (MainWindow::*fitComponent)() = nullptr;

  std::unique_ptr<solve_sudoku_t> driverSudoku;
  // std::atomic<bool> driverSudokuDone;

  unsigned sudokuOrder;
  unsigned sudokuDifficulty;

  std::vector<int> game;
  std::vector<int> answer;

  int gameFill(unsigned i);

protected:
  void keyPressEvent(QKeyEvent* ev) override;
  void resizeEvent(QResizeEvent* ev) override;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void launch();

  void welcomeActivity();
  void welcomeFitComponent();

  void gameActivity();
  void gameFitComponent();
};

template <typename T>
std::string toStr(const T& i) {
  std::ostringstream oss;
  oss << i;
  return oss.str();
}

#endif  // _MAINWINDOW_H_
