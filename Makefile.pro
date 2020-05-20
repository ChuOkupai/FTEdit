TEMPLATE = app
CONFIG += object_parallel_to_source
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TARGET = FTEdit
QT += widgets xml

win32 {
	CONFIG += windeployqt
	RC_ICONS += ./src/assets/icons/ftedit.ico
}

macx {
	CONFIG += app_bundle
	ICON = ./src/assets/icons/ftedit.icns
}

DESTDIR = release
MOC_DIR = .build/.moc
OBJECTS_DIR = .build/.obj

DEFINES += QT_DEPRECATED_WARNINGS
RESOURCES += src/assets/icons.qrc \
src/assets/objects.qrc
RCC_DIR = .build/.qrc

INCLUDEPATH += \
$$PWD/inc \
$$PWD/inc/editor \
$$PWD/inc/evaluator \
$$PWD/inc/fms \
$$PWD/inc/gui \

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
inc/editor/ClipVisitor.hh \
inc/editor/PasteVisitor.hh \
inc/evaluator/FTEdit_Evaluator.hh \
inc/evaluator/EvalVisitor.hh\
inc/evaluator/CutVisitor.hh\
inc/evaluator/Evaluator.hh \
inc/evaluator/ResultMCS.hh \
inc/evaluator/ResultBoolean.hh \
inc/evaluator/Result.hh \
inc/fms/FileManagerSystem.hh \
inc/fms/FTEdit_FMS.hh \
inc/fms/SaveVisitor.hh \
inc/fms/XmlTreeReader.hh \
inc/gui/FTEdit_GUI.hh \
inc/gui/Dialog.hh \
inc/gui/EditDistributionDialog.hh \
inc/gui/EditVisitor.hh \
inc/gui/MainWindow.hh \
inc/gui/ManageDistributionsDialog.hh \
inc/gui/ManageEventsDialog.hh \
inc/gui/PrintResult.hh \
inc/gui/RenderVisitor.hh \
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
src/editor/ClipVisitor.cc \
src/editor/PasteVisitor.cc \
src/evaluator/EvalVisitor.cc \
src/evaluator/CutVisitor.cc \
src/evaluator/Evaluator.cc \
src/evaluator/ResultMCS.cc \
src/evaluator/ResultBoolean.cc \
src/evaluator/Result.cc \
src/fms/FileManagerSystem.cc \
src/fms/SaveVisitor.cc \
src/fms/XmlTreeReader.cc \
src/gui/Dialog.cc \
src/gui/EditDistributionDialog.cc \
src/gui/EditVisitor.cc \
src/gui/MainWindow.cc \
src/gui/ManageDistributionsDialog.cc \
src/gui/ManageEventsDialog.cc \
src/gui/PrintResult.cc \
src/gui/RenderVisitor.cc \
src/gui/WidgetLinker.cc \
src/main.cc
