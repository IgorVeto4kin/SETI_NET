#ifndef LOGWRITER_H
#define LOGWRITER_H

#include "../core/netinfo.h"  
#include <QString>


class LogWriter {
public:
    LogWriter();
    void writeInterfacesLog(const QList<NetworkInfo::InterfaceInfo>& interfaces);
    
private:
    QString m_logPath = "/configs/network_interfaces.json";
    bool ensureConfigDirExists() const;
    QJsonArray interfacesToJson(const QList<NetworkInfo::InterfaceInfo>& interfaces) const;
};

#endif // LOGWRITER_H