#include "mainwindow.h"
#include "../core/netinfo.h"
#include "../logs/logwriter.h"
#include <QLabel>
#include <QPushButton>

#include <QCoreApplication>     

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    displayNetworkInfo();
    clearInterfaceWidgets();
}

void MainWindow::clearInterfaceWidgets() {
    
    for (QLabel* label : m_interfaceLabels) {
        layout->removeWidget(label); 
        label->deleteLater();        
    }
    m_interfaceLabels.clear();       
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
    
    QPushButton *LogWriteButton = new QPushButton("write log", centralWidget);
    LogWriteButton->setFixedSize(150, 30);
    connect(LogWriteButton, &QPushButton::clicked, this, &MainWindow::LogWriteClicked);
    
    QPushButton *ExitButton = new QPushButton("exit", centralWidget);
    ExitButton->setFixedSize(150, 30);
    connect(ExitButton, &QPushButton::clicked, this, &MainWindow::ExitClicked);

    QPushButton *RefreshButton = new QPushButton("refresh data", centralWidget);
    ExitButton->setFixedSize(150, 30);
    connect(ExitButton, &QPushButton::clicked, this, &MainWindow::ExitClicked);



    layout->addSpacing(20);
    layout->addWidget(LogWriteButton);
    layout->addWidget(RefreshButton);
    layout->addWidget(ExitButton);
    
    layout->addStretch();
    
    setCentralWidget(centralWidget);
}

void MainWindow::displayNetworkInfo()
{
    clearInterfaceWidgets();
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
    
    for (const auto &info : interfaces) {
        QString text = QString("IP-address: %1 \nSubnet mask: %2 \nInterface: %3 \n")
            .arg(info.ip)
            .arg(info.netmask)
            .arg(info.interfaceName);
        
        layout->insertWidget(0, new QLabel(text, centralWidget()));

        auto label = new QLabel(text, centralWidget());
        layout->addWidget(label);
        m_interfaceLabels.append(label); 
    }
    LogWriter logger;
    logger.writeInterfacesLog(interfaces);
    centralWidget()->updateGeometry();
}



void MainWindow::LogWriteClicked()
{
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    LogWriter logger;  
    logger.writeInterfacesLog(interfaces); 
    
   

}

void MainWindow::RefreshClicked()
{
    displayNetworkInfo();
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    LogWriter logger;  
    logger.writeInterfacesLog(interfaces);
    
   

}

void MainWindow::ExitClicked()
{
    QCoreApplication::quit();
}



