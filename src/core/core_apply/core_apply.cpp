#include "core_apply.hpp"
#include <cmath>     
#include <QRegularExpression>

NetworkConfigManager::NetworkConfigManager(QObject *parent) 
    : QObject(parent) {}

bool NetworkConfigManager::applySettingsFromJson(const QString &filePath){
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly)) {
        qCritical() << "Ошибка открытия файла:" << configFile.errorString();
        return false;
    }
    
    QJsonParseError parseError;
    QJsonDocument configDoc = QJsonDocument::fromJson(configFile.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCritical() << "Ошибка парсинга JSON:" << parseError.errorString();
        return false;
    }
    
    QJsonObject config = configDoc.object();
    
    // Извлечение параметров из JSON
    QString interfaceName = config["interfaceName"].toString();
    QString ipv4 = config["ipv4"].toString();
    QString netmask = config["netmask"].toString();
    QString mac = config["mac"].toString();
    QString ipv6 = config["ipv6"].toString();
    
    // Шаг 2: Проверка обязательных полей
    if (interfaceName.isEmpty() || ipv4.isEmpty() || netmask.isEmpty()) {
        qCritical() << "Неполные настройки (отсутствует interfaceName, ipv4 или netmask)";
        return false;
    }
    
    // Шаг 3: Проверка MAC-адреса (важное новое требование)
    if (!verifyMacAddress(interfaceName, mac)) {
        qCritical() << "MAC-адрес не совпадает! Ожидаемый:" << mac 
                   << "Фактический:" << QNetworkInterface::interfaceFromName(interfaceName).hardwareAddress();
        return false;
    }
    
    // Шаг 4: Обработка IPv6 (заглушка с предупреждением)
    if (!ipv6.isEmpty()) {
        qWarning() << "Обнаружена IPv6-конфигурация. В текущей версии IPv6 не поддерживается. Значение:"
                  << ipv6 << "будет проигнорировано";
        // Здесь можно добавить return false; если IPv6 должен быть ошибкой
    }
    
    // Шаг 5: Преобразование маски в префикс
    int prefix = netmaskToPrefix(netmask);
    if (prefix < 0) {
        qCritical() << "Некорректная сетевая маска:" << netmask;
        return false;
    }
    
    // Шаг 6: Формирование команд для применения настроек
    QStringList commands;
    
    // Выключение интерфейса
    commands << QString("ip link set dev %1 down").arg(interfaceName);
    
    // Очистка текущих IPv4-адресов
    commands << QString("ip -4 addr flush dev %1").arg(interfaceName);
    
    // Добавление нового IPv4-адреса с маской
    commands << QString("ip addr add %1/%2 dev %3").arg(ipv4).arg(prefix).arg(interfaceName);
    
    // Включение интерфейса
    commands << QString("ip link set dev %1 up").arg(interfaceName);
    
    // Шаг 7: Выполнение команд
    for (const QString &cmd : commands) {
        if (!runCommand(cmd)) {
            qCritical() << "Ошибка выполнения команды:" << cmd;
            return false;
        }
    }
    
    qInfo() << "Сетевые настройки успешно применены для интерфейса" << interfaceName;
    return true;
}

int NetworkConfigManager::netmaskToPrefix(const QString &netmask){// Проверка валидности маски
    QHostAddress netmaskAddr(netmask);
    if (netmaskAddr.isNull() || netmaskAddr.protocol() != QAbstractSocket::IPv4Protocol) {
        return -1;
    }
    
    quint32 bits = netmaskAddr.toIPv4Address();
    int prefix = 0;
    for (int i = 0; i < 32; i++) {
        if (bits & (1 << (31 - i))) {
            prefix++;
        } else {
            break;
        }
    }
    
    quint32 fullMask = (0xFFFFFFFF << (32 - prefix)) & 0xFFFFFFFF;
    return (fullMask == bits) ? prefix : -1;
}

bool NetworkConfigManager::runCommand(const QString &command){
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    
    // Запуск команды через оболочку (для поддержки пайпов и спец. символов)
    process.start("sh", QStringList() << "-c" << command);
    
    // Ожидание завершения с таймаутом 5 секунд
    if (!process.waitForFinished(5000)) {
        qWarning() << "Таймаут выполнения команды:" << command;
        return false;
    }
    
    // Проверка кода возврата
    if (process.exitCode() != 0) {
        qWarning() << "Команда завершилась с ошибкой:" << command
                  << "\nКод ошибки:" << process.exitCode()
                  << "\nВывод:" << process.readAllStandardOutput();
        return false;
    }
    
    return true;
}

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
