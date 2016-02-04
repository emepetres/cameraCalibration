TEMPLATE = app
QT += core gui opengl dbus
HEADERS += 
SOURCES += main.cpp
FORMS +=
RESOURCES +=
INCLUDEPATH += /usr/include/opencv2
LIBS += -L/usr/local/lib/ -L/usr/lib/ \
		-lopencv_core \
    	-lopencv_highgui \
    	-lopencv_imgproc \
    	-lopencv_calib3d \
    	-lopencv_video \
    	-lopencv_objdetect \
    	-lopencv_contrib \
    	-lopencv_legacy
#CONFIG += qt
QMAKE_CXXFLAGS += -std=gnu++0x
CONFIG += debug_and_release
CONFIG(debug, debug|release) {
    OBJECTS_DIR = .build/debug/obj
    MOC_DIR = .build/debug/moc
    DESTDIR = .build/debug
    TARGET = calibd
}
else {
    OBJECTS_DIR = .build/release/obj
    MOC_DIR = .build/release/moc
    DESTDIR = .build/release
    TARGET = calib
}
