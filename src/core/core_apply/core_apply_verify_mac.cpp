#include "core_apply.hpp"
#include <cmath>     
#include <QRegularExpression>


bool NetworkConfigManager::verifyMacAddress(const QString &interfaceName, const QString &expectedMac){
    // Нормализация MAC-адресов (приведение к верхнему регистру без разделителей)
    QString cleanExpected = expectedMac.toUpper().remove(QRegularExpression("[:\\s-]"));
    
    // Получение фактического MAC-адреса
    QNetworkInterface iface = QNetworkInterface::interfaceFromName(interfaceName);
    if (!iface.isValid()) {
        qWarning() << "Интерфейс не найден:" << interfaceName;
        return false;
    }
    
    QString cleanActual = iface.hardwareAddress().toUpper().remove(QRegularExpression("[:\\s-]"));
    
    // Сравнение нормализованных MAC-адресов
    return (cleanExpected == cleanActual);
}
