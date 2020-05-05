TEMPLATE = app
CONFIG += object_parallel_to_source
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TARGET = FTEdit
QT += widgets xml

DESTDIR = bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
$$PWD/inc \
$$PWD/inc/editor \
$$PWD/inc/fms \
$$PWD/inc/gui \
$$PWD/inc/evaluator

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
inc/editor/VisitorNode.hh \
inc/editor/VisitorDistribution.hh \
inc/evaluator/FTEdit_Evaluator.hh \
inc/evaluator/EvalVisitor.hh\
inc/evaluator/CutVisitor.hh\
inc/evaluator/Evaluator.hh \
inc/evaluator/ResultMCS.hh \
inc/evaluator/ResultBoolean.hh \
inc/evaluator/Result.hh \
inc/fms/FileManagerSystem.hh \
inc/fms/SaveVisitor.hh \
inc/gui/FTEdit_GUI.hh \
inc/gui/EditContainerDialog.hh \
inc/gui/MainWindow.hh \
inc/gui/WidgetLinker.hh

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
src/evaluator/EvalVisitor.cc \
src/evaluator/CutVisitor.cc \
src/evaluator/Evaluator.cc \
src/evaluator/ResultMCS.cc \
src/evaluator/ResultBoolean.cc \
src/evaluator/Result.cc \
src/fms/FileManagerSystem.cc \
src/fms/SaveVisitor.cc \
src/gui/EditContainerDialog.cc \
src/gui/MainWindow.cc \
src/gui/WidgetLinker.cc \
src/main.cc
