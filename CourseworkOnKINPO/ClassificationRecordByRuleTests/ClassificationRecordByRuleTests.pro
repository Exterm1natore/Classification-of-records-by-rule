QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_checkClassificationRecords.cpp \
    ../ClassificationOfRecordsByRule/Records.cpp \
    ../ClassificationOfRecordsByRule/ClassificationRules.cpp \
    ../ClassificationOfRecordsByRule/Result.cpp

HEADERS += ../ClassificationOfRecordsByRule/Records.h \
    ../ClassificationOfRecordsByRule/ClassificationRules.h \
    ../ClassificationOfRecordsByRule/Result.h

