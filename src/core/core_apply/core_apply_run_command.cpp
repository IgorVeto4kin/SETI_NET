#include "core_apply.hpp"
#include <cmath>     
#include <QRegularExpression>

bool NetworkConfigManager::runCommand(const QString &command){
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    
    // Запуск команды через оболочку (для поддержки пайпов и спец. символов)
    process.start("sh", QStringList() << "-c" << command);
    
    // Ожидание завершения с таймаутом 5 секунд
    if (!process.waitForFinished(5000)) {
        qWarning() << "Таймаут выполнения команды:" << command;
        return false;
    }
    
    // Проверка кода возврата
    if (process.exitCode() != 0) {
        qWarning() << "Команда завершилась с ошибкой:" << command
                  << "\nКод ошибки:" << process.exitCode()
                  << "\nВывод:" << process.readAllStandardOutput();
        return false;
    }
    
    return true;
}