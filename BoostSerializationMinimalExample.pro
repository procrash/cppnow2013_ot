QT += core
QT -= gui

CONFIG += c++11

TARGET = BoostSerializationMinimalExample 
DESTDIR = ./Bin
OBJECTS_DIR = ./Build

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += /usr/local/Cellar/boost/1.63.0/include
LIBS += "-L/usr/local/Cellar/boost/1.63.0/lib" -lboost_system -lboost_filesystem -lboost_serialization -lboost_program_options -lboost_thread-mt

