#pragma once
#include <QMainWindow>
#include "Editor.hh"

#define MIN(A, B) ((A) < (B) ? (A) : (B))

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
	// File
	void newFile();
	void open();
	void save();
	void saveAs();
	// Edit
	void cut();
	void copy();
	void paste();
	// Add
	void addAnd();
	void addInhibit();
	void addKN();
	void addOr();
	void addXor();
	void addTransfert();
	void addEvent();
	// Help
	void about();

private:
	Editor *editor;
	bool modified;

	QMenu *fileMenu;
		QAction *newAct;
		QAction *openAct;
		QAction *saveAct;
		QAction *saveAsAct;
		QAction *exitAct;
	QMenu *editMenu;
		QAction *cutAct;
		QAction *copyAct;
		QAction *pasteAct;
		QMenu *addNodeMenu;
			QMenu *addGateMenu;
				QAction *addAndAct;
				QAction *addInhibitAct;
				QAction *addOrAct;
				QAction *addKNAct;
				QAction *addXorAct;
				QAction *addTransfertAct;
			QAction *addEventAct;
	QMenu *helpMenu;
		QAction *aboutAct;
		QAction *aboutQtAct;
	
	void createActions();
	void createMenus();
	// Renvoie vrai si le projet peut être écrasé
	bool maybeSave();
	// réinitialise l'interface (en cas de chargement ou de nouveau fichier)
	void reset();
};
