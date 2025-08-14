#pragma once

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
  class SomeWidgetWithUiFile;
}
QT_END_NAMESPACE

namespace gui {

class SomeWidgetWithUiFile : public QWidget {
  Q_OBJECT
public:
  SomeWidgetWithUiFile(QWidget* parent = nullptr);
  ~SomeWidgetWithUiFile();
  
private:
  Ui::SomeWidgetWithUiFile *ui;
};

}