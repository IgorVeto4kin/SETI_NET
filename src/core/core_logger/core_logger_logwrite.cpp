#include "core_logger.hpp"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

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
