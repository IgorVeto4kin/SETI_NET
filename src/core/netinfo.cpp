#include "netinfo.h"


NetworkInfo::NetworkInfo(QObject *parent) : QObject(parent)
{
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                InterfaceInfo info;
                info.ip = entry.ip().toString();
                info.netmask = entry.netmask().toString();
                info.interfaceName = interface.name();
                interfaces.append(info);
            }
        }
    }
}
QJsonArray NetworkInfo::toJsonArray() const {
    QJsonArray result;
    for (const auto& info : interfaces) {
        QJsonObject obj;
        obj["ip"] = info.ip;
        obj["netmask"] = info.netmask;
        obj["interface"] = info.interfaceName;
        result.append(obj);
    }
    return result;
}

QList<NetworkInfo::InterfaceInfo> NetworkInfo::getNetworkInterfaces() const
{
    return interfaces;
}