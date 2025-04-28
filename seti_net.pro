QT += widgets core gui network
TARGET = seti-net
TEMPLATE = app

# Исходные файлы
SOURCES += \
    src/main.cpp \
    src/core/netinfo.cpp \
    src/gui/mainwindow.cpp

# Заголовочные файлы
HEADERS += \
    src/core/netinfo.h \
    src/gui/mainwindow.h

# Настройки компиляции
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS

# Пути для включения файлов
INCLUDEPATH += src