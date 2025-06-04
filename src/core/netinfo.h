#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QObject>
#include <QList>
#include <QNetworkInterface>
#include <QJsonArray>
#include <QJsonObject>

class NetworkInfo : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInfo(QObject *parent = nullptr);
   
    struct InterfaceInfo {
        QString ipv4;
        QString netmask;
        QString interfaceName;
        QString mac;
        QString ipv6;
    };
    
    QList<InterfaceInfo> getNetworkInterfaces() const;



    private:
    QList<InterfaceInfo> interfaces;
};



#endif // NETWORKINFO_H