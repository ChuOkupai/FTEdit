TEMPLATE = app
CONFIG += object_parallel_to_source
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
inc/editor/Container.hh \
inc/editor/Gate.hh \
inc/editor/Distribution.hh \
inc/editor/Or.hh \
inc/editor/Transfert.hh \
inc/editor/Properties.hh \
inc/editor/Editor.hh \
inc/editor/Node.hh \
inc/editor/Exponential.hh \
inc/editor/Tree.hh \
inc/editor/And.hh \
inc/editor/Xor.hh \
inc/editor/VotingOR.hh \
inc/editor/Constant.hh \
inc/editor/Event.hh \
inc/editor/Inhibit.hh

SOURCES += \
src/editor/Inhibit.cc \
src/editor/Gate.cc \
src/editor/Constant.cc \
src/editor/Tree.cc \
src/editor/Or.cc \
src/editor/Xor.cc \
src/editor/Transfert.cc \
src/editor/Properties.cc \
src/editor/Distribution.cc \
src/editor/Container.cc \
src/editor/Node.cc \
src/editor/VotingOR.cc \
src/editor/And.cc \
src/editor/Exponential.cc \
src/editor/Editor.cc \
src/editor/Event.cc \
src/main.cc