#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void ExitClicked();
    void LogWriteClicked();
    void RefreshClicked();

private:
    QVBoxLayout * m_layout;  
    QList<QLabel*> m_interfaceLabels;
    void setupUi();
    void displayNetworkInfo();
    void clearInterfaceWidgets();
    
};

#endif // MAINWINDOW_H