#ifndef NETWORKCONFIGMANAGER_H
#define NETWORKCONFIGMANAGER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

struct InterfaceInfo {
    QString interfaceName;
    QString ipv4;
    QString netmask;
    QString mac;
    QString ipv6;
};

class NetworkConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConfigManager(QObject *parent = nullptr);
    bool applyNetworkSettings(const InterfaceInfo &info);
    InterfaceInfo parseJsonConfig(const QString &filePath);

private:
    bool validateInterface(const QString &interfaceName);
    int netmaskToPrefix(const QString &netmask);
    bool runCommand(const QString &command);
};

#endif // NETWORKCONFIGMANAGER_H
