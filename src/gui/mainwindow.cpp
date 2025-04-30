#include "mainwindow.h"
#include "../core/netinfo.h"
#include <QLabel>
#include <QPushButton>

#include <QCoreApplication>     

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    displayNetworkInfo();
}

void MainWindow::setupUi()
{
    setWindowTitle("SETI NET");
    resize(500, 500);
    
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    QPushButton *exitButton = new QPushButton("exit", centralWidget);
    exitButton->setFixedSize(150, 30);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    
    layout->addSpacing(20);
    layout->addWidget(exitButton);
    layout->addStretch();
    
    setCentralWidget(centralWidget);
}

void MainWindow::displayNetworkInfo()
{
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
    
    for (const auto &info : interfaces) {
        QString text = QString("IP-address: %1 \nSubnet mask: %2 \nInterface: %3 \n")
            .arg(info.ip)
            .arg(info.netmask)
            .arg(info.interfaceName);
        
        layout->insertWidget(0, new QLabel(text, centralWidget()));
    }
}

void MainWindow::onExitClicked()
{
    QCoreApplication::quit();
}