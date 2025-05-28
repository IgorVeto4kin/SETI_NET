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
    QJsonArray toJsonArray() const;
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