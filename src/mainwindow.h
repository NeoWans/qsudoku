#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>

class MainWindow final : public QMainWindow {
  Q_OBJECT

private:
  std::list<QWidget> componentList;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void launch();

  void welcomeActivity();
  void gameActivity();
};
#endif  // MAINWINDOW_H
