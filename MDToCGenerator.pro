QT += core
QT -= gui

CONFIG += c++11

TARGET = generateToC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tocGenerator.cpp

HEADERS += \
    tocGenerator.hpp

DEFINES += QT_DEPRECATED_WARNINGS
