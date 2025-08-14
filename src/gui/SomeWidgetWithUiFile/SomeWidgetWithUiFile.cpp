#include "SomeWidgetWithUiFile.hpp"
#include "ui_SomeWidgetWithUiFile.h"

namespace gui {

SomeWidgetWithUiFile::SomeWidgetWithUiFile(QWidget* parent) : QWidget(parent), ui(new Ui::SomeWidgetWithUiFile) {
    qDebug() << "SomeWidgetWithUiFile created";
    ui->setupUi(this);
}

SomeWidgetWithUiFile::~SomeWidgetWithUiFile() {
    delete ui;
};
        
}