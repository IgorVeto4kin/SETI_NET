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

void MainWindow::clearInterfaceWidgets()
{
    for (auto group : m_interfaceGroups) {
        // Удаляем все дочерние виджеты
        QLayout* layout = group->layout();
        if (layout) {
            QLayoutItem* item;
            while (item = layout->takeAt(0)) {
                if (item->widget()) {
                    delete item->widget();
                }
                delete item;
            }
        }
        
        // Удаляем саму группу
        centralWidget()->layout()->removeWidget(group);
        delete group;
    }
    m_interfaceGroups.clear();
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
                         "  background-color:rgb(2, 132, 255);"
                         "  border: 1px solid #d0d0d0;"
                         "  border-radius: 4px;"
                         "  padding: 5px;"
                         "}"
                         "QPushButton:hover {"
                         "  background-color:rgb(12, 93, 214);"
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


// Вспомогательная функция для добавления строк свойств
void MainWindow::addPropertyRow(QGridLayout* layout, int row, 
    const QString& header, const QString& value,
    const QString& headerStyle, const QString& valueStyle)
{
QLabel* headerLabel = new QLabel(header);
headerLabel->setStyleSheet(headerStyle);
headerLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

QLabel* valueLabel = new QLabel(value);
valueLabel->setStyleSheet(valueStyle);
valueLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);  // Разрешаем копирование
valueLabel->setCursor(Qt::IBeamCursor);  // Курсор в виде I-образной палочки
valueLabel->setWordWrap(true);  // Разрешаем перенос слов

layout->addWidget(headerLabel, row, 0);
layout->addWidget(valueLabel, row, 1);
}






void MainWindow::displayNetworkInfo()
{
    clearInterfaceWidgets();
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
    
    // Стили для текста
    const QString headerStyle = "QLabel { color: #606060; font-size: 9pt; }";
    const QString valueStyle = "QLabel { color: #000000; font-size: 10pt; font-weight: 500; }";
    
    for (const auto &info : interfaces) {
        // Создаем группу для каждого интерфейса
        QGroupBox* interfaceGroup = new QGroupBox(info.interfaceName, centralWidget());
        QGridLayout* gridLayout = new QGridLayout(interfaceGroup);
        gridLayout->setSpacing(5);  // Расстояние между строками
        gridLayout->setColumnMinimumWidth(0, 120);  // Фиксированная ширина для заголовков
        
        int row = 0;
        
        // Добавляем свойства в сетку
        //addPropertyRow(gridLayout, row++, "Link speed:", info.speed, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "IPv4 Address:", info.ipv4, headerStyle, valueStyle);
        /*
        if (!info.ipv6.isEmpty()) {
            addPropertyRow(gridLayout, row++, "IPv6 Address:", info.ipv6, headerStyle, valueStyle);
        }
        */
        addPropertyRow(gridLayout, row++, "Subnet Mask:", info.netmask, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "MAC-Address:", info.mac, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "Interface name:", info.interfaceName, headerStyle, valueStyle);
        //addPropertyRow(gridLayout, row++, "Default Route:", info.gateway, headerStyle, valueStyle);
        /*
        if (!info.dnsServers.isEmpty()) {
            addPropertyRow(gridLayout, row++, "DNS:", info.dnsServers.join("\n"), headerStyle, valueStyle);
        }
        */
        // Добавляем группу в основной layout
        mainLayout->insertWidget(mainLayout->count() - 1, interfaceGroup);
        m_interfaceGroups.append(interfaceGroup);  // Сохраняем указатель
    }
    /*
    LogWriter logger;
    logger.writeInterfacesLog(interfaces);
    centralWidget()->updateGeometry();
    */
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



