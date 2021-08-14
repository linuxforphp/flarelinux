@
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core
@

HEADERS += \
    mainwindow.h \
    myqtbatchstart.h \
    processwindow.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    myqtbatchstart.cpp \
    processwindow.cpp

OTHER_FILES += \
    favicon.ico \
    favicon.rc \
    favicon.png \
    flarelinux-server_docker-start.bat \
    flarelinux-server_docker-stop.bat \
    flarelinux-server_docker-start.sh \
    flarelinux-server_docker-stop.sh

RC_FILE = favicon.rc
