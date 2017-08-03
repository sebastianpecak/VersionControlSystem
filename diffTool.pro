TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Source/diffTool/helpers.cpp \
    Source/vcs/vcs.cpp \
    Source/main.cpp

HEADERS += \
    Include/diffTool/helpers.hpp

DISTFILES += \
    ../build-diffTool-Desktop_Qt_5_7_0_GCC_64bit-Debug/plik2 \
    ../build-diffTool-Desktop_Qt_5_7_0_GCC_64bit-Debug/plik1
