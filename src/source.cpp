#include <QApplication>
#include <QMainWindow>
#include <QLabel>   
#include <QVBoxLayout>
#include <QPushButton>
#include <QCoreApplication>  
#include <QDebug>           
#include <QHostAddress>     
#include <QNetworkInterface> 

#include <iostream>
#include <cstdio>
#include <string>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  
    QMainWindow window;  
    window.setWindowTitle("SETI NET");
    window.resize(500, 500); 

    QWidget *centralWidget = new QWidget(&window);  
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);  
    
    layout->setSpacing(10);  
    layout->setContentsMargins(20, 20, 0, 0);  
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft); 

    QPushButton *Exitbutton = new QPushButton("exit", centralWidget);
    Exitbutton->setFixedSize(150, 30);   

    QStringList addressesInfo; 
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        for (const QNetworkAddressEntry &entry : interface.addressEntries() ) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol  ) {
                addressesInfo << QString("IP-address: %1 \n Subnet mask: %2 \n Interface: %3  \n")
                    .arg(entry.ip().toString())
                    .arg(entry.netmask().toString())
                    .arg(interface.name());
            }
        }
    }


    for (const QString &info : addressesInfo) {
        layout->addWidget(new QLabel(info, centralWidget));
    }

    layout->addSpacing(20); 

    layout->addWidget(Exitbutton);
    layout->addStretch();

    QObject::connect(Exitbutton, &QPushButton::clicked, []() {
        QCoreApplication::quit();
    });


    window.setCentralWidget(centralWidget);  
    window.show();  
    return app.exec();  
}

