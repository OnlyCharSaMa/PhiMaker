QT += quick qml \
    widgets
QT += multimedia
CONFIG += resources_big

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        PhiObj/PhigrosObj/phiabstractnote.cpp \
        PhiObj/PhigrosObj/phievent.cpp \
        PhiObj/PhigrosObj/phihitptc.cpp \
        PhiObj/PhigrosObj/phihold.cpp \
        PhiObj/PhigrosObj/phijudgeline.cpp \
        PhiObj/PhigrosObj/phinote.cpp \
        PhiObj/Widgets/phiviewer.cpp \
        PhiObj/functions/Math2d.cpp \
        PhiObj/functions/PhiObjCreate.cpp \
        Widgets/charcolumn.cpp \
        Widgets/resizewidget.cpp \
        main.cpp \
        phisoundplayer.cpp

RESOURCES += qml.qrc \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    PhiObj/PhigrosObj/phiabstractnote.h \
    PhiObj/PhigrosObj/phievent.h \
    PhiObj/PhigrosObj/phihitptc.h \
    PhiObj/PhigrosObj/phihitptcdata.h \
    PhiObj/PhigrosObj/phihold.h \
    PhiObj/PhigrosObj/phijudgeline.h \
    PhiObj/PhigrosObj/phinote.h \
    PhiObj/Widgets/phiviewer.h \
    PhiObj/classesDeclaration.h \
    PhiObj/functions.h \
    PhiObj/functions/Math2d.h \
    PhiObj/functions/PhiObjCreate.h \
    PhiObj/phievent.h \
    PhiObj/phijudgeline.h \
    PhiObj/phinote.h \
    PhiObj/phiviewer.h \
    Widgets/charcolumn.h \
    Widgets/resizewidget.h \
    phisoundplayer.h

FORMS += \
    Widgets/charcolumn.ui
