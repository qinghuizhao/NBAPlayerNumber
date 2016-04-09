#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T16:25:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = NBAPlayerNumber
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH  +=/usr/include\
                             /usr/include/opencv\
                            /usr/include/opencv2

CV_LIB = /usr/local/lib
#LIBS += -L$${CV_LIB} -lopencv_ml -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_legacy
#LIBS+= -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal
 LIBS = -L$${CV_LIB} -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
SOURCES += \
    main.cpp

