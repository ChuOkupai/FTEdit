TEMPLATE = app
CONFIG += object_parallel_to_source
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TARGET = FTEdit
QT += widgets

DESTDIR = bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
$$PWD/inc \
$$PWD/inc/editor

HEADERS += \
inc/FTEdit.hh \
inc/editor/And.hh \
inc/editor/Constant.hh \
inc/editor/Container.hh \
inc/editor/Distribution.hh \
inc/editor/Editor.hh \
inc/editor/Event.hh \
inc/editor/Exponential.hh \
inc/editor/FTEdit_Editor.hh \
inc/editor/Gate.hh \
inc/editor/Inhibit.hh \
inc/editor/Node.hh \
inc/editor/Or.hh \
inc/editor/Properties.hh \
inc/editor/Transfert.hh \
inc/editor/Tree.hh \
inc/editor/VotingOR.hh \
inc/editor/Xor.hh

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
src/editor/Xor.cc \
src/main.cc