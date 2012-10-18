# -------------------------------------------------
# Project created by QtCreator 2009-11-16T10:30:54
# -------------------------------------------------
TARGET = vobrowse
TEMPLATE = app

INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/include/speech_tools

SOURCES += main.cpp \
    mainwindow.cpp \
    fmpanel.cpp \
    controlpanel.cpp \
    fmlistview.cpp \
    bookmarklistview.cpp \
    historylistview.cpp \
    findtask.cpp \
    VoiceBase.cpp \
    ControlThread.cpp \
    utils.cpp \
    importinbuf.cpp \
    Speech.cpp \
    notepad.cpp
HEADERS += mainwindow.h \
    fmpanel.h \
    controlpanel.h \
    fmlistview.h \
    bookmarklistview.h \
    historylistview.h \
    findtask.h \
    VoiceBase.h \
    ControlThread.h \
    utils.h \
    importinbuf.h \
    jdktrie.h \
    Speech.h \
    notepad.h
RESOURCES += vobrowse.qrc
win32:
    {
    RC_FILE = vobrowse.rc
    SOURCES += drivelistview.cpp
    HEADERS += drivelistview.h
    }
OTHER_FILES += readme.txt \
    meeting2.xml

QMAKE_CXXFLAGS += -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" ` pkg-config --cflags pocketsphinx sphinxbase `
QMAKE_CFLAGS   += -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" ` pkg-config --cflags pocketsphinx sphinxbase `
LIBS           += ` pkg-config --libs pocketsphinx sphinxbase`

unix:!macx:!symbian: LIBS += -lFestival

unix:!macx:!symbian: LIBS += -lestools

unix:!macx:!symbian: LIBS += -lestbase

unix:!macx:!symbian: LIBS += -leststring
