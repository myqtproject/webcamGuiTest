#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T22:02:38
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webcamGuiTest
TEMPLATE = app


SOURCES += main.cpp\
        webcam.cpp

HEADERS  += webcam.h

FORMS    += webcam.ui

INCLUDEPATH += -I/usr/include/opencv

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

OTHER_FILES += \
    haarcascade_frontalface_alt.xml \
    ../../../../usr/share/opencv/haarcascades/haarcascade_eye.xml
