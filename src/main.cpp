#include "gui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //call mainwindow
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    //window.displayNetworkInfo();
    return app.exec();
}


