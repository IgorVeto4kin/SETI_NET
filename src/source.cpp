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

    QString CurrentAddress;
    const QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            CurrentAddress = address.toString();          
        }
    }

    QWidget *centralWidget = new QWidget(&window);  
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);  
    
    layout->setSpacing(10);  
    layout->setContentsMargins(20, 20, 0, 0);  
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft); 

    QPushButton *Signbutton = new QPushButton("тык", centralWidget);
    QPushButton *Exitbutton = new QPushButton("exit", centralWidget);
    Signbutton->setFixedSize(150, 30);   
    Exitbutton->setFixedSize(150, 30);   


    layout->addWidget(new QLabel("Ваш IP-адрес: " + CurrentAddress,centralWidget));
    layout->addWidget(new QLabel("Ещё информация", centralWidget));
    layout->addSpacing(20); 

    layout->addWidget(Signbutton);
    layout->addWidget(Exitbutton);
    layout->addStretch();

    QObject::connect(Signbutton, &QPushButton::clicked, []() {
        std::cout<<"он нажал кнопку"<<std::endl;  
         
    });



    window.setCentralWidget(centralWidget);  
    window.show();  
    return app.exec();  
}

