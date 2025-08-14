#include "core_network.hpp"


NetworkInfo::NetworkInfo(QObject *parent) : QObject(parent)
{
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                InterfaceInfo info;
                info.mac = interface.hardwareAddress();
                info.ipv4 = entry.ip().toString();
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
