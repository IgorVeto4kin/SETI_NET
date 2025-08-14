#pragma once

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

namespace gui {

class SomeWidgetWithoutUiFile : public QWidget {
public:
    SomeWidgetWithoutUiFile(QWidget* parent = nullptr);
private:    
    QLabel* label; 
};

}