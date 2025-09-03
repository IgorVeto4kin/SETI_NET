#include "MainWindow.hpp"
#include "../../core/core_apply/core_apply.hpp"
#include "../../core/core_logger/core_logger.hpp"
#include "../../core/core_network/core_network.hpp"

#include <QLabel>
#include <QPushButton>
#include <QCoreApplication>    
#include <QMainWindow>
#include <QFileDialog> 
#include <QTabWidget>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setupUi();
    displayNetworkInfo();
    clearInterfaceWidgets();
}

void MainWindow::clearInterfaceWidgets(){
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

void MainWindow::setupUi() {
    setWindowTitle("SETI NET");
    resize(500, 500);

    // Create the central widget and its layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create the tab widget
    QTabWidget *tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    // --- Tab 1: Buttons ---
    QWidget *tab1 = new QWidget();
    QVBoxLayout *tab1Layout = new QVBoxLayout(tab1);
    tab1Layout->setContentsMargins(20, 20, 20, 20);
    tab1Layout->setSpacing(15);

    // Create container for buttons with left alignment
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignLeft);

    // Create buttons with uniform style and size
    QPushButton *refreshButton = new QPushButton("Refresh Data", tab1);
    QPushButton *importConfigButton = new QPushButton("Import Config", tab1);
    QPushButton *logButton = new QPushButton("Write Log", tab1);
    QPushButton *DHCPButton = new QPushButton("DHCP", tab1);
    QPushButton *exitButton = new QPushButton("Exit", tab1);

    const QSize buttonSize(160, 35);

    DHCPButton->setFixedSize(buttonSize);
    refreshButton->setFixedSize(buttonSize);
    importConfigButton->setFixedSize(buttonSize);
    logButton->setFixedSize(buttonSize);
    exitButton->setFixedSize(buttonSize);

    // Button style with improved readability
    QString buttonStyle = "QPushButton {"
                         "  background-color: rgb(2, 132, 255);"
                         "  color: white;"
                         "  border: 1px solid #d0d0d0;"
                         "  border-radius: 4px;"
                         "  padding: 5px;"
                         "  font-size: 14px;"
                         "}"
                         "QPushButton:hover {"
                         "  background-color: rgb(12, 93, 214);"
                         "}";

    refreshButton->setStyleSheet(buttonStyle);
    DHCPButton->setStyleSheet(buttonStyle);
    importConfigButton->setStyleSheet(buttonStyle);
    logButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Connect signals to slots
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::RefreshClicked);
    connect(logButton, &QPushButton::clicked, this, &MainWindow::LogWriteClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::ExitClicked);
    connect(importConfigButton, &QPushButton::clicked, this, &MainWindow::ImportConfigClicked);
    connect(DHCPButton, &QPushButton::clicked, this, &MainWindow::DHCPClicked);

    // Add buttons to button layout

    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(DHCPButton);
    buttonLayout->addWidget(logButton);
    buttonLayout->addWidget(importConfigButton);
    buttonLayout->addWidget(exitButton);

    // Add button layout and stretch to tab1 layout
    tab1Layout->addLayout(buttonLayout);
    tab1Layout->addStretch();

    // Add tab1 to tabWidget
    tabWidget->addTab(tab1, "Control bottons");

    // --- Tab 2: Two LineEdits with Labels and Button ---
    QWidget *tab2 = new QWidget();
    QVBoxLayout *tab2Layout = new QVBoxLayout(tab2);
    tab2Layout->setContentsMargins(20, 20, 20, 20);
    tab2Layout->setSpacing(15);

    // First input: Label and LineEdit for IP Address
    QHBoxLayout *ipLayout = new QHBoxLayout();
    QLabel *ipLabel = new QLabel("IP Address:", tab2);
    ipLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    QLineEdit *ipLineEdit = new QLineEdit(tab2);
    ipLineEdit->setPlaceholderText("192.168.1.1");
    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(ipLineEdit);
    ipLayout->addStretch(); // Add stretch to push label and line edit to the left

    // Second input: Label and LineEdit for Port
    QHBoxLayout *subnetLayout = new QHBoxLayout();
    QLabel *subnetLabel = new QLabel("Subnet Mask:", tab2);
    subnetLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    QLineEdit *subnetLineEdit = new QLineEdit(tab2);
    subnetLineEdit->setPlaceholderText("255.255.255.0");
    subnetLayout->addWidget(subnetLabel);
    subnetLayout->addWidget(subnetLineEdit);
    subnetLayout->addStretch(); // Add stretch to push label and line edit to the left
    //-----------------------------------------------
    QHBoxLayout *intnameLayout = new QHBoxLayout();
    QLabel *intnameLabel = new QLabel("Interface Name(optional):", tab2);
    intnameLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    QLineEdit *intnameLineEdit = new QLineEdit(tab2);
    intnameLineEdit->setPlaceholderText("eth");
    intnameLayout->addWidget(intnameLabel);
    intnameLayout->addWidget(intnameLineEdit);
    intnameLayout->addStretch();


    // Apply button
    QPushButton *readButton = new QPushButton("Apply", tab2);
    readButton->setStyleSheet(buttonStyle);
    readButton->setFixedSize(buttonSize);
    //save input button
    QPushButton *SaveconfButton = new QPushButton("Save Input config", tab2);
    SaveconfButton->setStyleSheet(buttonStyle);
    SaveconfButton->setFixedSize(buttonSize);

    // Add layouts and button to tab2 layout
     tab2Layout->addLayout(intnameLayout);
    tab2Layout->addLayout(ipLayout);
    tab2Layout->addLayout(subnetLayout);
    tab2Layout->addWidget(readButton);
    tab2Layout->addWidget(SaveconfButton);
    tab2Layout->addStretch();

    // Add tab2 to tabWidget
    tabWidget->addTab(tab2, "Manual Config");
}   

void MainWindow::addPropertyRow(QGridLayout* layout, int row, 
    const QString& header, const QString& value,
    const QString& headerStyle, const QString& valueStyle){ // Вспомогательная функция для добавления строк свойств
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

void MainWindow::displayNetworkInfo(){
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
        
        addPropertyRow(gridLayout, row++, "IPv4 Address:", info.ipv4, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "Subnet Mask:", info.netmask, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "MAC-Address:", info.mac, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "Interface name:", info.interfaceName, headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "DHCP Status:", "Not implemented yet", headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "DNS :", "Not implemented yet", headerStyle, valueStyle);
        addPropertyRow(gridLayout, row++, "Default gateway:", "Not implemented yet", headerStyle, valueStyle);

        mainLayout->insertWidget(mainLayout->count() - 1, interfaceGroup);
        m_interfaceGroups.append(interfaceGroup);  // Сохраняем указатель
    }
    
}



