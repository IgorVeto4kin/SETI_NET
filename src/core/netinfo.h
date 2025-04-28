#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QObject>
#include <QList>
#include <QNetworkInterface>

class NetworkInfo : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInfo(QObject *parent = nullptr);
    
    struct InterfaceInfo {
        QString ip;
        QString netmask;
        QString interfaceName;
    };
    
    QList<InterfaceInfo> getNetworkInterfaces() const;

private:
    QList<InterfaceInfo> interfaces;
};

#endif // NETWORKINFO_H