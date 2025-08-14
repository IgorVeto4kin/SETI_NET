/********************************************************************************
** Form generated from reading UI file 'SomeWidgetWithUiFile.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOMEWIDGETWITHUIFILE_H
#define UI_SOMEWIDGETWITHUIFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SomeWidgetWithUiFile
{
public:
    QLabel *label;

    void setupUi(QWidget *SomeWidgetWithUiFile)
    {
        if (SomeWidgetWithUiFile->objectName().isEmpty())
            SomeWidgetWithUiFile->setObjectName(QString::fromUtf8("SomeWidgetWithUiFile"));
        SomeWidgetWithUiFile->resize(400, 300);
        label = new QLabel(SomeWidgetWithUiFile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 380, 280));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(SomeWidgetWithUiFile);

        QMetaObject::connectSlotsByName(SomeWidgetWithUiFile);
    } // setupUi

    void retranslateUi(QWidget *SomeWidgetWithUiFile)
    {
        SomeWidgetWithUiFile->setWindowTitle(QCoreApplication::translate("SomeWidgetWithUiFile", "Form", nullptr));
        label->setText(QCoreApplication::translate("SomeWidgetWithUiFile", "SomeWidgetWithUiFile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SomeWidgetWithUiFile: public Ui_SomeWidgetWithUiFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOMEWIDGETWITHUIFILE_H
