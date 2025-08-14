#include <QtTest>

#include "gui/MainWindow/MainWindow.hpp"

class GuiTest : public QObject {
  Q_OBJECT
private slots:
  void initTestCase();
  void testMainWindowCreation();
};

void GuiTest::initTestCase(){
  qDebug() << "Starting gui tests";
}
void GuiTest::testMainWindowCreation() {
  gui::MainWindow mainWindow;
  QVERIFY(mainWindow.centralWidget() != nullptr);
}

QTEST_MAIN(GuiTest)
#include "gui_test.moc"