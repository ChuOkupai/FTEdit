TEMPLATE = app
CONFIG += object_parallel_to_source \
release \
windeployqt \
app_bundle
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TARGET = FTEdit
QT += widgets xml
win32:RC_ICONS += ./assets/icons/ftedit.ico
ICON = ./assets/icons/ftedit.icns

DESTDIR = ../release
MOC_DIR = .build/.moc
OBJECTS_DIR = .build/.obj

DEFINES += QT_DEPRECATED_WARNINGS
RESOURCES += assets/icons.qrc \
assets/objects.qrc
RCC_DIR = .build/.qrc

INCLUDEPATH += \
$$PWD/../inc \
$$PWD/../inc/editor \
$$PWD/../inc/evaluator \
$$PWD/../inc/fms \
$$PWD/../inc/gui \

HEADERS += \
../inc/FTEdit.hh \
../inc/editor/Container.hh \
../inc/editor/Distribution.hh \
../inc/editor/Editor.hh \
../inc/editor/Event.hh \
../inc/editor/FTEdit_Editor.hh \
../inc/editor/Gate.hh \
../inc/editor/Node.hh \
../inc/editor/Properties.hh \
../inc/editor/Transfert.hh \
../inc/editor/Tree.hh \
../inc/editor/VisitorNode.hh \
../inc/editor/VisitorDistribution.hh \
../inc/editor/CopyVisitor.hh \
../inc/editor/ClipVisitor.hh \
../inc/editor/PasteVisitor.hh \
../inc/evaluator/FTEdit_Evaluator.hh \
../inc/evaluator/EvalVisitor.hh\
../inc/evaluator/CutVisitor.hh\
../inc/evaluator/Evaluator.hh \
../inc/evaluator/ResultMCS.hh \
../inc/evaluator/ResultBoolean.hh \
../inc/evaluator/Result.hh \
../inc/fms/FileManagerSystem.hh \
../inc/fms/FTEdit_FMS.hh \
../inc/fms/SaveVisitor.hh \
../inc/fms/XmlTreeReader.hh \
../inc/gui/FTEdit_GUI.hh \
../inc/gui/Dialog.hh \
../inc/gui/EditDistributionDialog.hh \
../inc/gui/EditVisitor.hh \
../inc/gui/MainWindow.hh \
../inc/gui/ManageDistributionsDialog.hh \
../inc/gui/ManageEventsDialog.hh \
../inc/gui/PrintResult.hh \
../inc/gui/RenderVisitor.hh \
../inc/gui/WidgetLinker.hh

SOURCES += \
editor/And.cc \
editor/Constant.cc \
editor/Container.cc \
editor/Distribution.cc \
editor/Editor.cc \
editor/Event.cc \
editor/Exponential.cc \
editor/Gate.cc \
editor/Inhibit.cc \
editor/Node.cc \
editor/Or.cc \
editor/Properties.cc \
editor/Transfert.cc \
editor/Tree.cc \
editor/VotingOR.cc \
editor/Weibull.cc \
editor/Xor.cc \
editor/CopyVisitor.cc \
editor/ClipVisitor.cc \
editor/PasteVisitor.cc \
evaluator/EvalVisitor.cc \
evaluator/CutVisitor.cc \
evaluator/Evaluator.cc \
evaluator/ResultMCS.cc \
evaluator/ResultBoolean.cc \
evaluator/Result.cc \
fms/FileManagerSystem.cc \
fms/SaveVisitor.cc \
fms/XmlTreeReader.cc \
gui/Dialog.cc \
gui/EditDistributionDialog.cc \
gui/EditVisitor.cc \
gui/MainWindow.cc \
gui/ManageDistributionsDialog.cc \
gui/ManageEventsDialog.cc \
gui/PrintResult.cc \
gui/RenderVisitor.cc \
gui/WidgetLinker.cc \
main.cc
