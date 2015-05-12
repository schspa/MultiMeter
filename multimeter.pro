#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T20:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = multimeter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    multimeterdevice.cpp \
    adcthread.cpp \
    voltagemeasurement.cpp \
    currentmeasurement.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    multimeterdevice.h \
    adcthread.h \
    multimeter_ioctrl_num.h \
    measurebase.h \
    voltagemeasurement.h \
    currentmeasurement.h \
    proportion.h \
    qcustomplot.h
