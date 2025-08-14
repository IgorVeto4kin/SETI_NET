#pragma once

#include <QMainWindow>

namespace gui {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

};

} // namespace gui