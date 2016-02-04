TEMPLATE = app

QT += core dbus
QT -= gui

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += /usr/include/opencv2

HEADERS += 
SOURCES += main.cpp

CONFIG += c++11 debug_and_release

CONFIG(debug, debug|release) {
    OBJECTS_DIR = .build/debug/obj
    MOC_DIR = .build/debug/moc
    DESTDIR = .build/debug
    TARGET = cameraCalibrationd
}
else {
    OBJECTS_DIR = .build/release/obj
    MOC_DIR = .build/release/moc
    DESTDIR = .build/release
    TARGET = cameraCalibration

    config.path = portable/resources
    config.files = resources/*
    target.path = portable/
    INSTALLS += config target
}

LIBS += -L/usr/local/lib/ -L/usr/lib/ \
	-lopencv_core \
    	-lopencv_highgui \
    	-lopencv_imgproc \
    	-lopencv_calib3d \
    	-lopencv_video \
    	-lopencv_objdetect \
    	-lopencv_contrib \
    	-lopencv_legacy
