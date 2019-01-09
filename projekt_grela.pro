TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf

INCLUDEPATH = usr/include

SOURCES += \
        main.cpp \
    src/to3bit.cpp \
    src/getpallete.cpp \
    src/dittering.cpp \
    src/compression.cpp \
    src/Screen.cpp \
    src/Bitmap.cpp

HEADERS += \
    include/algorytmy.h \
    include/Screen.h \
    include/Bitmap.h
