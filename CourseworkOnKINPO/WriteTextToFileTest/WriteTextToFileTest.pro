QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_checkWritingTextToFile.cpp \
        ../ClassificationOfRecordsByRule/FileHandling.cpp

HEADERS += ../ClassificationOfRecordsByRule/FileHandling.h
