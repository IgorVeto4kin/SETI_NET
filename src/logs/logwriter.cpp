#include "logwriter.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>   
LogWriter::LogWriter() {}

QJsonArray LogWriter::toJsonArray(const QList<NetworkInfo::InterfaceInfo>& interfaces) const {
    QJsonArray result;
    for (const auto& info : interfaces) {
        QJsonObject obj;
        obj["ip"] = info.ipv4;
        obj["netmask"] = info.netmask;
        obj["interface"] = info.interfaceName;
        result.append(obj);
    }
    return result;
}

void LogWriter::writeInterfacesLog(const QList<NetworkInfo::InterfaceInfo>& interfaces) {
    
    const QString configDir = QCoreApplication::applicationDirPath() + "/../../config";
    const QString logPath = configDir + "/network_interfaces.json";
    
    QDir dir(configDir);
    

  
    QFile logFile(logPath);
    


    QJsonObject root;
    root["interfaces"] = interfacesToJson(interfaces);
    
    
    if(logFile.write(QJsonDocument(root).toJson())) {
        qDebug() << "[LogWriter] Successfully wrote log to:" << logPath;
    } else {
        qWarning() << "[LogWriter] Write operation failed for:" << logPath;
    }
    logFile.close();
}

QJsonArray LogWriter::interfacesToJson(const QList<NetworkInfo::InterfaceInfo>& interfaces) const {
    QJsonArray jsonArray;
    for (const auto& info : interfaces) {
        QJsonObject obj;
        obj["ip"] = info.ipv4;
        obj["netmask"] = info.netmask;
        obj["interface"] = info.interfaceName;
        jsonArray.append(obj);
    }
    return jsonArray;
}

