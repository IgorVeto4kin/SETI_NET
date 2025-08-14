#include <QApplication>
#include <QDebug>
#include <QFile>

#include "gui/MainWindow/MainWindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  window.displayNetworkInfo();
    

  
  return app.exec();
}