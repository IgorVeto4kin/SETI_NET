#include "networkconfigmanager.h"

NetworkConfigManager::NetworkConfigManager(QObject *parent) : QObject(parent) {}

// Парсинг JSON-файла
InterfaceInfo NetworkConfigManager::parseJsonConfig(const QString &filePath) {
    InterfaceInfo info;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open JSON file";
        return info;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    info.interfaceName = obj["interfaceName"].toString();
    info.ipv4 = obj["ipv4"].toString();
    info.netmask = obj["netmask"].toString();
    info.mac = obj["mac"].toString();
    info.ipv6 = obj["ipv6"].toString();

    return info;
}

// Проверка существования интерфейса
bool NetworkConfigManager::validateInterface(const QString &interfaceName) {
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        if (interface.name() == interfaceName) return true;
    }
    qWarning() << "Interface" << interfaceName << "not found";
    return false;
}

// Конвертация маски в префикс (CIDR)
int NetworkConfigManager::netmaskToPrefix(const QString &netmask) {
    quint32 mask = QHostAddress(netmask).toIPv4Address();
    if (mask == 0) return -1;
    return 32 - ffs(~mask);
}

// Выполнение системной команды
bool NetworkConfigManager::runCommand(const QString &command) {
    QProcess process;
    process.start("sh", QStringList() << "-c" << command);
    if (!process.waitForFinished(5000)) {
        qWarning() << "Command timeout:" << command;
        return false;
    }
    if (process.exitCode() != 0) {
        qWarning() << "Command error:" << process.readAllStandardError();
        return false;
    }
    return true;
}

// Основная функция применения настроек
bool NetworkConfigManager::applyNetworkSettings(const InterfaceInfo &info) {
    if (!validateInterface(info.interfaceName)) return false;

    int prefix = netmaskToPrefix(info.netmask);
    if (prefix < 0) {
        qWarning() << "Invalid netmask format";
        return false;
    }

    QString ipWithPrefix = info.ipv4 + "/" + QString::number(prefix);
    QStringList commands;

    // Выключение интерфейса
    commands << "ip link set dev " + info.interfaceName + " down";

    // Смена MAC-адреса (если указан)
    if (!info.mac.isEmpty() && QNetworkInterface::interfaceFromName(info.interfaceName).hardwareAddress() != info.mac) {
        commands << "ip link set dev " + info.interfaceName + " address " + info.mac;
    }

    // Очистка IPv4-адресов и добавление нового
    commands << "ip -4 addr flush dev " + info.interfaceName;
    commands << "ip addr add " + ipWithPrefix + " dev " + info.interfaceName;

    // Включение интерфейса
    commands << "ip link set dev " + info.interfaceName + " up";

    // Выполнение команд
    foreach (const QString &command, commands) {
        if (!runCommand(command)) {
            qCritical() << "Failed on command:" << command;
            return false;
        }
    }

    qDebug() << "Network settings applied successfully";
    return true;
}