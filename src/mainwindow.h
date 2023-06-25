#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>

class MainWindow final : public QMainWindow {
  Q_OBJECT

private:
  static constexpr int welcomeDefaultWidth = 400;
  static constexpr int welcomeDefaultHeight = 400;
  static constexpr int gameDefaultWidth = 400;
  static constexpr int gameDefaultHeight = 400;

  int welcomeWidth = welcomeDefaultWidth;
  int welcomeHeight = welcomeDefaultHeight;
  int gameWidth = gameDefaultWidth;
  int gameHeight = gameDefaultHeight;

  std::list<QWidget> componentList;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void launch();

  void welcomeActivity();
  void gameActivity();
};
#endif  // MAINWINDOW_H
