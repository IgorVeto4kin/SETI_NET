#include <QApplication>
#include <QMainWindow>
#include <QLabel>   
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  
    QMainWindow window;  // Создаём главное окно
    window.setWindowTitle("SETI NET");
    window.resize(500, 500);   


    QWidget *centralWidget = new QWidget(&window);  // Создаём контейнер
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);  // Вертикальное расположение
    layout->setSpacing(0);  // Фиксированное расстояние в пикселях (можно поставить 0)
    layout->setContentsMargins(0, 0, 0, 0);  // Убираем отступы от краёв (left, top, right, bottom)
    layout->addWidget(new QLabel("Ваш IP-адрес: 192:168:228:228", centralWidget));
    layout->addWidget(new QLabel("По моим рассчетам вы лох", centralWidget));
    
    
    





    window.setCentralWidget(centralWidget);  // Устанавливаем контейнер в окно



    window.show();  
    return app.exec();  
}