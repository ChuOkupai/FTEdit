TEMPLATE = app
CONFIG += object_parallel_to_source
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TARGET = FTEdit
QT += widgets xml

DESTDIR = bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

DEFINES += QT_DEPRECATED_WARNINGS
RESOURCES += assets/icons.qrc
RCC_DIR = src

INCLUDEPATH += \
$$PWD/inc \
$$PWD/inc/editor \
$$PWD/inc/fms \
$$PWD/inc/gui

HEADERS += \
inc/FTEdit.hh \
inc/editor/Container.hh \
inc/editor/Distribution.hh \
inc/editor/Editor.hh \
inc/editor/Event.hh \
inc/editor/FTEdit_Editor.hh \
inc/editor/Gate.hh \
inc/editor/Node.hh \
inc/editor/Properties.hh \
inc/editor/Transfert.hh \
inc/editor/Tree.hh \
inc/fms/FileManagerSystem.hh \
inc/fms/SaveVisitor.hh \
inc/gui/FTEdit_GUI.hh \
inc/gui/ChooseDistributionDialog.hh \
inc/gui/EditContainerDialog.hh \
inc/gui/EditDistributionDialog.hh \
inc/gui/MainWindow.hh \
inc/gui/ManageDistributionsDialog.hh \
inc/gui/ManageEventsDialog.hh \
inc/gui/WidgetLinker.hh \
inc/gui/Widgets.hh

SOURCES += \
src/editor/And.cc \
src/editor/Constant.cc \
src/editor/Container.cc \
src/editor/Distribution.cc \
src/editor/Editor.cc \
src/editor/Event.cc \
src/editor/Exponential.cc \
src/editor/Gate.cc \
src/editor/Inhibit.cc \
src/editor/Node.cc \
src/editor/Or.cc \
src/editor/Properties.cc \
src/editor/Transfert.cc \
src/editor/Tree.cc \
src/editor/VotingOR.cc \
src/editor/Weibull.cc \
src/editor/Xor.cc \
src/fms/FileManagerSystem.cc \
src/fms/SaveVisitor.cc \
src/gui/ChooseDistributionDialog.cc \
src/gui/EditContainerDialog.cc \
src/gui/EditDistributionDialog.cc \
src/gui/MainWindow.cc \
src/gui/ManageDistributionsDialog.cc \
src/gui/ManageEventsDialog.cc \
src/gui/WidgetLinker.cc \
src/gui/Widgets.cc \
src/main.cc
