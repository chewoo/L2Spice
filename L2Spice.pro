QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        capacitor.cpp \
        capacitordialog.cpp \
        circuit.cpp \
        component.cpp \
        current_control_current_source.cpp \
        current_control_current_source_dialog.cpp \
        current_control_voltage_source.cpp \
        current_control_voltage_source_dialog.cpp \
        current_source.cpp \
        currentsourcedialog.cpp \
        diado_dialog.cpp \
        diode.cpp \
        ground.cpp \
        imageItem.cpp \
        inductor.cpp \
        inductordialog.cpp \
        linenodeitem.cpp \
        linenodeitemdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        matrix.cpp \
        node.cpp \
        oscilloscope.cpp \
        othercomponentsdialog.cpp \
        qcustomplot.cpp \
        resistor.cpp \
        resistordialog.cpp \
        rlccomponent.cpp \
        unit_transformer.cpp \
        voltage_control_current_source.cpp \
        voltage_control_current_source_dialog.cpp \
        voltage_control_voltage_source.cpp \
        voltage_control_voltage_source_dialog.cpp \
        voltage_source.cpp \
        voltagesourcedialog.cpp \
        workspace.cpp

HEADERS += \
        Constant.h \
        capacitor.h \
        capacitordialog.h \
        circuit.h \
        component.h \
        current_control_current_source.h \
        current_control_current_source_dialog.h \
        current_control_voltage_source.h \
        current_control_voltage_source_dialog.h \
        current_source.h \
        currentsourcedialog.h \
        diado_dialog.h \
        diode.h \
        ground.h \
        imageItem.h \
        inductor.h \
        inductordialog.h \
        linenodeitem.h \
        linenodeitemdialog.h \
        mainwindow.h \
        matrix.h \
        node.h \
        oscilloscope.h \
        othercomponentsdialog.h \
        qcustomplot.h \
        resistor.h \
        resistordialog.h \
        rlccomponent.h \
        unit_transformer.h \
        voltage_control_current_source.h \
        voltage_control_current_source_dialog.h \
        voltage_control_voltage_source.h \
        voltage_control_voltage_source_dialog.h \
        voltage_source.h \
        voltagesourcedialog.h \
        workspace.h

FORMS += \
        capacitordialog.ui \
        current_control_current_source_dialog.ui \
        current_control_voltage_source_dialog.ui \
        currentsourcedialog.ui \
        diado_dialog.ui \
        inductordialog.ui \
        linenodeitemdialog.ui \
        mainwindow.ui \
        oscilloscope.ui \
        othercomponentsdialog.ui \
        resistordialog.ui \
        voltage_control_current_source_dialog.ui \
        voltage_control_voltage_source_dialog.ui \
        voltagesourcedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
