#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QMainWindow>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    QList<QGroupBox*> m_interfaceGroups;  // Вместо QList<QLabel*>

private slots:
    void ExitClicked();
    void LogWriteClicked();
    void RefreshClicked();
    void ImportConfigClicked();

private:
    QVBoxLayout * m_layout;  

    void addPropertyRow(QGridLayout* layout, int row, 
        const QString& header, const QString& value,
        const QString& headerStyle, const QString& valueStyle);

    void setupUi();
    
    void clearInterfaceWidgets();
 public:   
    void displayNetworkInfo();
    
    
};

#endif // MAINWINDOW_H