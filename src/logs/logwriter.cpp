#include "logwriter.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>

LogWriter::LogWriter() {
    ensureConfigDirExists();
}

bool LogWriter::ensureConfigDirExists() const {
    QDir dir("/configs");
    if (!dir.exists()) {
        return dir.mkpath(".");
    }
    return true;
}

void LogWriter::writeInterfacesLog(const QJsonArray& interfacesData) {
    QFile logFile(m_logPath);
    if (!logFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open log file:" << m_logPath;
        return;
    }

    QJsonObject root;
    root["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["interfaces"] = interfacesData;

    logFile.write(QJsonDocument(root).toJson());
    logFile.close();
}

