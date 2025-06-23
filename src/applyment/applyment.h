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
#include <QHostAddress>

class NetworkConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConfigManager(QObject *parent = nullptr);
    
    
    bool applySettingsFromJson(const QString &filePath);

private:
    
    int netmaskToPrefix(const QString &netmask);
    bool runCommand(const QString &command);
    bool verifyMacAddress(const QString &interfaceName, const QString &expectedMac);
};

#endif // NETWORKCONFIGMANAGER_H