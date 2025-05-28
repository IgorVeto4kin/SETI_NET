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
        layout()->removeWidget(label); 
        label->deleteLater();        
    }
    m_interfaceLabels.clear();       
}

void MainWindow::setupUi()
{
    setWindowTitle("SETI NET");
    resize(500, 500);
    
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Устанавливаем единые отступы по всем сторонам
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);  // Увеличиваем расстояние между элементами
    
    // Создаем контейнер для кнопок с выравниванием по центру
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignLeft);
    
    // Создаем кнопки с единым стилем
    QPushButton *refreshButton = new QPushButton("Refresh Data");
    QPushButton *logButton = new QPushButton("Write Log");
    QPushButton *exitButton = new QPushButton("Exit");
    
    // Устанавливаем ОДИНАКОВЫЙ размер для всех кнопок
    const QSize buttonSize(160, 35);
    refreshButton->setFixedSize(buttonSize);
    logButton->setFixedSize(buttonSize);
    exitButton->setFixedSize(buttonSize);
    
    // Настраиваем стиль для профессионального вида
    QString buttonStyle = "QPushButton {"
                         "  background-color: #f0f0f0;"
                         "  border: 1px solid #d0d0d0;"
                         "  border-radius: 4px;"
                         "  padding: 5px;"
                         "}"
                         "QPushButton:hover {"
                         "  background-color: #e0e0e0;"
                         "}";
    
    refreshButton->setStyleSheet(buttonStyle);
    logButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);
    
    // Правильное подключение сигналов
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::RefreshClicked);
    connect(logButton, &QPushButton::clicked, this, &MainWindow::LogWriteClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::ExitClicked);
    
    // Добавляем кнопки в горизонтальный layout
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(logButton);
    buttonLayout->addWidget(exitButton);
    
    // Добавляем кнопочный layout в основной
    mainLayout->addLayout(buttonLayout);
    
    // Добавляем растягивающийся разделитель
    mainLayout->addStretch();
    
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



