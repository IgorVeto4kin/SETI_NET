#include "SomeWidgetWithoutUiFile.hpp"

namespace gui {

SomeWidgetWithoutUiFile::SomeWidgetWithoutUiFile(QWidget* parent) : QWidget(parent) {
    qDebug() << "SomeWidgetWithoutUiFile created";
    label = new QLabel("SomeWidgetWithoutUiFile", this); // Added label
    label->setAlignment(Qt::AlignCenter);
    
    QVBoxLayout* layout = new QVBoxLayout(this); // Added layout
    layout->addWidget(label);

    setLayout(layout); // Added layout
}

}