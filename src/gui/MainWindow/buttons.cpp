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


void MainWindow::LogWriteClicked(){
    NetworkInfo networkInfo;
    auto interfaces = networkInfo.getNetworkInterfaces();
    LogWriter logger;  
    logger.LogWriteAllInterfaces(interfaces); 
}

void MainWindow::RefreshClicked(){
    clearInterfaceWidgets();
    displayNetworkInfo();
}

void MainWindow::ImportConfigClicked(){
    QString filePath = QFileDialog::getOpenFileName(
        this,                            // Родительское окно
        tr("Choose JSON-file"),        // Заголовок окна
        QDir::homePath(),                // Стартовая директория
        tr("JSON файлы (*.json);;Все файлы (*)") // Фильтры
    );

    if(filePath.isEmpty()) {
        qDebug() << "Canceled";
        return;
    }

    qDebug() << "Choosen file:" << filePath;
    NetworkConfigManager manager;
    manager.applySettingsFromJson(filePath);
}

void MainWindow::ExitClicked(){
    QCoreApplication::quit();
}

void MainWindow::DHCPClicked(){
    qDebug()<<"This feature will appear later";
}