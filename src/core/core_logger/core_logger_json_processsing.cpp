#include "core_logger.hpp"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

QJsonObject LogWriter::InterfaceToJSON(const NetworkInfo::InterfaceInfo &interface)  {
    QJsonObject obj;
    obj["ipv4"] = interface.ipv4;
    obj["netmask"] = interface.netmask;
    obj["interfaceName"] = interface.interfaceName;
    obj["mac"] = interface.mac;
    obj["ipv6"] = interface.ipv6;
    return obj;
}