#include "core_logger.hpp"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

QString LogWriter::getConfigDirectory() const {
    // Start from binary location
    QDir dir(QCoreApplication::applicationDirPath());
    qDebug() << "Starting search from:" << dir.absolutePath();

    // Search upwards for marker file
    while (!dir.isRoot()) {
        qDebug() << "Checking:" << dir.absolutePath();

        // Check if marker file exists in current directory
        if (dir.exists(".project_root")) {
            QString configPath = dir.filePath("available_interfaces");
            qDebug() << "Found .project_root! Config path:" << configPath;
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
        QCoreApplication::applicationDirPath() + "/../../available_interfaces"
    );
    
    qWarning() << "Using fallback config path:" << fallbackPath;
    return fallbackPath;
}
