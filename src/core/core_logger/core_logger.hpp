#ifndef LOGWRITER_H
#define LOGWRITER_H

#include "../core_network/core_network.hpp"  
#include <QString>


class LogWriter {
public:
    LogWriter();
    void LogWriteAllInterfaces(const QList<NetworkInfo::InterfaceInfo>& interfaces);
    //void LogWriteCertainInterface(const NetworkInfo::InterfaceInfo &interface) const;
    QJsonObject InterfaceToJSON(const NetworkInfo::InterfaceInfo &interface) ;
    QString getConfigDirectory() const;
    
private:
    //QJsonArray toJsonArray(const QList<NetworkInfo::InterfaceInfo>& interfaces) const;
    QString m_logPath = "/configs/network_interfaces.json";
    bool ensureConfigDirExists() const;
    QJsonArray interfacesToJson(const QList<NetworkInfo::InterfaceInfo>& interfaces) const;
};

#endif // LOGWRITER_H
       //
       //

