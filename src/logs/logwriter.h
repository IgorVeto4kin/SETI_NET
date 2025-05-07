#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

class LogWriter {
public:
    LogWriter();
    void writeInterfacesLog(const QJsonArray& interfacesData);
    
private:
    QString m_logPath = "/configs/network_interfaces.json";  // Можно сделать настраиваемым
    bool ensureConfigDirExists() const;
};

#endif // LOGWRITER_H