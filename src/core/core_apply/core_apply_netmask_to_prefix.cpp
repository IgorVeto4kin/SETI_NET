#include "core_apply.hpp"
#include <cmath>     
#include <QRegularExpression>


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
