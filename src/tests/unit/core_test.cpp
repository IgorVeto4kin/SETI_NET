#include <QtTest>

#include "core/core.hpp"

class CoreTest : public QObject {
  Q_OBJECT
private slots:
  void initTestCase();
  void testPublicCoreMethod();
};

void CoreTest::initTestCase(){
  qDebug() << "Starting core tests";
}

void CoreTest::testPublicCoreMethod() {
  core::Core core;
  int result = core.publicCoreMethod();
  QVERIFY(result == 42);
}

QTEST_MAIN(CoreTest)

#include "core_test.moc"