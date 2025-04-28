#include "netinfo.h"

NetworkInfo::NetworkInfo(QObject *parent) : QObject(parent)
{
    // Инициализация данных
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

QList<NetworkInfo::InterfaceInfo> NetworkInfo::getNetworkInterfaces() const
{
    return interfaces;
}