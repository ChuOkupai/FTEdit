#pragma once

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QGridLayout>
#include <QtWidgets>
#include <QTabWidget>
#include <QFrame>


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

/*-----------------*/
    void openDialog();
/*-----------------*/
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
	QMenu *analysisMenu;
		QAction *evaluateAct;
	QMenu *helpMenu;
		QAction *aboutAct;
		QAction *aboutQtAct;
	/*---------------------------------*/
	QVBoxLayout *v_layout;
	QHBoxLayout *h_layout;
    QGridLayout *grid;
    QPushButton *m_btn;
    QDockWidget *dock;
    QTreeWidget* tree;
    QPushButton *m_quit;
    QWidget *m_mainwidget;
    QTabWidget *onglets;
    //QFrame *fram;
	/*---------------------------------*/
	void createActions();
	void createMenus();
	// Renvoie vrai si le projet peut être écrasé
	bool maybeSave();
	// réinitialise l'interface (en cas de chargement ou de nouveau fichier)
	void reset();
};
