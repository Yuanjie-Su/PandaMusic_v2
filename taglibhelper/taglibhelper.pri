HEADERS += \
    $$PWD/taglibhelper.h

SOURCES += \
    $$PWD/taglibhelper.cpp

LIBS += -L$$PWD/taglib/lib/ -ltag
INCLUDEPATH += $$PWD/taglib/include
