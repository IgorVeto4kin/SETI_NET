#include "logwriter.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

LogWriter::LogWriter() {}

QString LogWriter::getConfigDirectory() const {
    // Start from binary location
    QDir dir(QCoreApplication::applicationDirPath());
    qDebug() << "Starting search from:" << dir.absolutePath();

    // Search upwards for marker file
    while (!dir.isRoot()) {
        qDebug() << "Checking:" << dir.absolutePath();

        // Check if marker file exists in current directory
        if (dir.exists(".project_root")) {
            QString configPath = dir.filePath("config");
            qDebug() << "✅ Found .project_root! Config path:" << configPath;
            return configPath;
        }

        // Try to move up to parent directory
        if (!dir.cdUp()) {
            qDebug() << " Can't move up from:" << dir.absolutePath();
            break;
        }
    }

    // Fallback if marker not found (development environment)
    QString fallbackPath = QDir::cleanPath(
        QCoreApplication::applicationDirPath() + "/../../config"
    );
    
    qWarning() << "⚠️ Using fallback config path:" << fallbackPath;
    return fallbackPath;
}


QJsonObject LogWriter::InterfaceToJSON(const NetworkInfo::InterfaceInfo &interface)  {
    QJsonObject obj;
    obj["ipv4"] = interface.ipv4;
    obj["netmask"] = interface.netmask;
    obj["interfaceName"] = interface.interfaceName;
    obj["mac"] = interface.mac;
    obj["ipv6"] = interface.ipv6;
    return obj;
}


void LogWriter::LogWriteAllInterfaces(const QList<NetworkInfo::InterfaceInfo>& interfaces) {
    const QString configDir = getConfigDirectory();
    for (const auto &info : interfaces){
    
        
       
        QJsonObject jsonData = InterfaceToJSON(info);
        // 2. Ensure directory exists
        QDir().mkpath(configDir);
        
        //Sanitize filename
        QString safeFilename = info.interfaceName;
        // Replace any non-alphanumeric characters except _- with underscores
        safeFilename.replace(QRegularExpression("[^\\w\\-]"), "_");
        // Remove any leading/trailing underscores
        safeFilename.replace(QRegularExpression("^_+|_+$"), "");
        
        // 4. Create full file path
        QString filePath = configDir + "/" + safeFilename + ".json";
        
        // 5. Write JSON to file
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "Failed to open" << filePath << "for writing:" << file.errorString();
            
        }
        
        file.write(QJsonDocument(jsonData).toJson());
        file.close();
        
        qInfo() << "Saved JSON to:" << filePath;
    
    

    }
}
