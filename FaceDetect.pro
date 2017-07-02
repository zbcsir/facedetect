#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T15:27:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += serialport

TARGET = FaceDetect
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qprogressindicator.cpp \
    detect.cpp \
    threaddetect.cpp \
    mycustomslider.cpp \
    datalog.cpp \
    log.cpp \
    dataglobal.cpp \
    threaddetectobj.cpp \
    customwaitbar.cpp \
    form.cpp \
    btnqss.cpp \
    adjustlig.cpp

HEADERS  += mainwindow.h \
    qprogressindicator.h\
    detect.h \
    threaddetect.h \
    mycustomslider.h \
    datalog.h \
    log.h \
    data.h \
    dataglobal.h \
    threaddetectobj.h \
    customwaitbar.h \
    form.h \
    btnqss.h \
    adjustlig.h

FORMS    += mainwindow.ui \
    form.ui

INCLUDEPATH += C:\Qt\cvfiles\include\opencv\
            += C:\Qt\cvfiles\include\opencv2\
            += C:\Qt\cvfiles\include

LIBS  += C:\Qt\cvfiles\lib\libopencv_*.a
LIBS  += C:\Qt\cvfiles\gdi32.dll

DISTFILES += \
    app.rc

RC_FILE = app.rc

