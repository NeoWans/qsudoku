#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include <functional>
#include <memory>

class MainWindow final : public QMainWindow {
  Q_OBJECT

private:
  static constexpr int welcomeDefaultWidth = 400;
  static constexpr int welcomeDefaultHeight = 400;
  static constexpr int gameDefaultWidth = 600;
  static constexpr int gameDefaultHeight = 800;

  std::list<std::unique_ptr<QWidget>> componentList;
  void (MainWindow::*fitComponent)() = nullptr;

  unsigned sudokuOrder;

protected:
  void resizeEvent(QResizeEvent* ev) override;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void launch();

  void welcomeActivity();
  void fitWelcomeComponent();

  void gameActivity();
  void fitGameComponent();
};
#endif  // MAINWINDOW_H
