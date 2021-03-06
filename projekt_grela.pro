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
    src/Bitmap.cpp \
    src/file_io.cpp \
    src/button.cpp \
    src/guinode.cpp \
    src/sdlbutton.cpp \
    src/textfield.cpp \
    src/sdltextfield.cpp \
    src/handlers.cpp \
    src/guibitmap.cpp \
    src/guipallete.cpp \
    src/guimanager.cpp

HEADERS += \
    include/algorytmy.h \
    include/Screen.h \
    include/Bitmap.h \
    include/algorytmy.h \
    include/button.h \
    include/guinode.h \
    include/guihandler.h \
    include/guievent.h \
    include/guidrawer.h \
    include/sdlbutton.h \
    include/textfield.h \
    include/sdltextfield.h \
    include/handlers.h \
    include/guibitmap.h \
    include/guipallete.h \
    include/guimanager.h
