#pragma once
#include <QMainWindow>
#include "FTEdit_Evaluator.hh"
#include "FTEdit_FMS.hh"
#include "WidgetLinker.hh"

#define ICON_SIZE	48
#define RES_MIN_X	460
#define RES_MIN_Y	320
#define MIN(A, B) ((A) < (B) ? (A) : (B))

class NodeItem;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent* e);

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
	void clearClipboard();
		// Add
		void addAnd();
		void addInhibit();
		void addKN();
		void addOr();
		void addXor();
		void addTransfert();
		void addEvent();
	void moveItemFirst();
	void moveItemLeft();
	void moveItemRight();
	void moveItemLast();
	void editItem();
	void removeItem();
	void detach();
	void join();
	void newTransfert();
	// View
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void showToolBar();
	void toggleExplorer();
	void toggleErrorList();
	// Show
	void showDistributions();
	void showEvents();
	// Analysis
	void evaluate();
	// Help
	void about();

	// Change item selection
	void changeItem();
	// Check new selected item
	void explorerItemClicked(QTreeWidgetItem *item, int column);
	// Show context menu
	void explorerShowContextMenu(const QPoint &pos);
	void editTreeProperties();
	void addTree();
	void removeTree();
	void removeResult();
	void removeAllResults();

private:
	Editor				*editor;
	FileManagerSystem	*fileManager;
	bool				modified;
	NodeItem			*curItem;
	QList<Result*>		resultsHistory;
	int					curTreeRow;
	int					selectedRow;

	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *clearClipboardAct;
	QAction *addAndAct;
	QAction *addInhibitAct;
	QAction *addOrAct;
	QAction *addKNAct;
	QAction *addXorAct;
	QAction *addTransfertAct;
	QAction *addEventAct;
		// Context menus actions
		QAction *moveItemFirstAct;
		QAction *moveItemLeftAct;
		QAction *moveItemRightAct;
		QAction *moveItemLastAct;
		QAction *editItemAct;
		QAction *removeItemAct;
		QAction *detachItemAct;
		QAction *joinItemAct;
		QAction *newTransfertAct;
	QAction *zoomInAct;
	QAction *zoomOutAct;
	QAction *zoomResetAct;
	QAction *showToolBarAct;
	QAction *toggleExplorerAct;
	QAction *toggleErrorListAct;
	QAction *distributionsAct;
	QAction *eventsAct;
	QAction *evaluateAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	QAction *editTreePropertiesAct;
	QAction *addTreeAct;
	QAction *removeTreeAct;
	QAction *removeResultAct;
	QAction *removeAllResultsAct;

	QMenu			*childItemsMenu; // for childs (Container + Transfert)
	QMenu			*itemsMenu; // for gates
	QMenu			*gatesMenu;
	QToolBar		*toolBar;
	QTreeWidget		*explorer;
	QTreeWidgetItem	*trees; // Fault trees list
	QTreeWidgetItem	*results; // Results list
	GraphicsView	*view;
	QGraphicsScene	*scene;
	ListWidget		*errorList;
	QSplitter		*vSplitter; // vertical split: graphicsView <-> errorList
	QSplitter		*hSplitter; // horizontal split: explorer <-> vSplitter

	void createActions();
	void createMenus();
	void createToolBar();
	// Renvoie vrai si le projet peut être écrasé
	bool maybeSave();
	// Réinitialise l'interface (en cas de chargement ou de nouveau fichier)
	void reset();
	// Redimensionne le layout
	void resizeSplitter(QSplitter *splitter, int widget1Size, int widget2Size);
	// Set enabled buttons
	void setEnabledButton();
	// Add new Gate
	void addGate(Gate *g);
	// Refresh current scene
	void updateScene(Node *selection);

public:
	QMenu *itemsContextMenu();
	QGraphicsScene *getScene();
};
