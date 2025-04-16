#include <QApplication>
#include <QMainWindow>
#include <QLabel>   
#include <QVBoxLayout>
#include <QPushButton>



#include <iostream>
#include <cstdio>
#include <string>
struct ipv4{};

struct ipv6{};


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

    QPushButton *button = new QPushButton("тык", centralWidget);
    button->setFixedSize(150, 30);  

    
    layout->addWidget(new QLabel("Ваш IP-адрес: 192:168:228:228", centralWidget));
    layout->addWidget(new QLabel("Ещё информация", centralWidget));
    layout->addSpacing(20); 

    layout->addWidget(button);
    layout->addStretch();

    QObject::connect(button, &QPushButton::clicked, []() {
        std::cout<<"он нажал кнопку"<<std::endl;    
    });



    window.setCentralWidget(centralWidget);  
    window.show();  
    return app.exec();  
}

