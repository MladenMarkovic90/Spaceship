TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


LIBS += libfreeglut -lopengl32 -lglu32 -luser32


SOURCES += \
    main.c

include(deployment.pri)

HEADERS += \
    ucitavanje_slike.h \
    on_time.h \
    on_display.h \
    keyboard.h \
    definicije.h

