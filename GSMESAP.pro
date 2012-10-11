#-------------------------------------------------
#
# Project created by QtCreator 2012-09-28T15:00:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GSMESAP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectionsettings.cpp \
    viewer.cpp \
    mysqlrelationaldelegate.cpp \
    inserirdados.cpp \
    dialoginserirdados.cpp \
    dialoginserirprofessor.cpp \
    dialogexcluirregistro.cpp \
    exportatabela.cpp \
    dialogdocumentos.cpp

HEADERS  += mainwindow.h \
    connectionsettings.h \
    viewer.h \
    gsmesap_enums.h \
    mysqlrelationaldelegate.h \
    inserirdados.h \
    dialoginserirdados.h \
    dialoginserirprofessor.h \
    dialogexcluirregistro.h \
    exportatabela.h \
    dialogdocumentos.h

FORMS    += mainwindow.ui \
    connectionsettings.ui \
    dialoginserirdados.ui \
    dialoginserirprofessor.ui \
    dialogexcluirregistro.ui \
    dialogdocumentos.ui

OTHER_FILES += \
    COPYING.txt
