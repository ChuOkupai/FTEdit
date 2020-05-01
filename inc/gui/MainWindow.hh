#pragma once
#include <QMainWindow>
#include <QtWidgets>
#include "Editor.hh"

#define RES_MIN_X	460
#define RES_MIN_Y	320
#define ZOOM_MIN	20.0
#define ZOOM_MAX	400.0
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
	void closeEvent(QCloseEvent* e) override;

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
	// View
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void toggleExplorer();
	void toggleErrorList();
	// Show
	void showDistributions();
	void showEvents();
	// Analysis
	void evaluate();
	// Help
	void about();

private:
	Editor			*editor;
	bool			modified;
	double			zoomLevel;
	//QList<Result>	results;
	//Node			*current;

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
	QMenu *viewMenu;
		QAction *zoomInAct;
		QAction *zoomOutAct;
		QAction *zoomResetAct;
		QAction *distributionsAct;
		QAction *eventsAct;
		QAction *toggleExplorerAct;
		QAction *toggleErrorListAct;
	QMenu *analysisMenu;
		QAction *evaluateAct;
	QMenu *helpMenu;
		QAction *aboutAct;
		QAction *aboutQtAct;

	QTreeWidget		*explorer;
	QGraphicsView	*graphicsView;
	QListWidget		*errorList;
	QSplitter		*vSplitter; // vertical split: graphicsView <-> errorList
	QSplitter		*hSplitter; // horizontal split: explorer <-> vSplitter

	void createActions();
	void createMenus();
	// Renvoie vrai si le projet peut être écrasé
	bool maybeSave();
	// réinitialise l'interface (en cas de chargement ou de nouveau fichier)*
	void reset();
	// Redimensionne le layout
	void resizeSplitter(QSplitter *splitter, int widget1Size, int widget2Size);
};