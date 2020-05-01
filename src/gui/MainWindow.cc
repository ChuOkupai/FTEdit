#include <QDir>
#include <QList>
#include <QDebug>
#include "MainWindow.hh"
#include "EditContainerDialog.hh"
#include "ManageDistributionsDialog.hh"
#include "ManageEventsDialog.hh"
#include "WidgetLinker.hh"

MainWindow::MainWindow() : editor(nullptr), modified(false), zoomLevel(100)
{
	toolBar = new QToolBar;
	toolBar->setFloatable(false);
	toolBar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
	toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
	addToolBar(Qt::TopToolBarArea, toolBar);
	statusBar(); // barre de status
	createActions();
	createMenus();

	setWindowTitle("FTEdit");
	QRect r = QGuiApplication::primaryScreen()->geometry();
	setMinimumSize(MIN(r.width(), RES_MIN_X), MIN(r.height(), RES_MIN_Y));
	resize(r.width() / 1.5, r.height() / 1.5);

	auto centralwidget = new QWidget(this);
	setCentralWidget(centralwidget);
	centralwidget->setStyleSheet("selection-background-color: #4684e3;"
	"background-color:0xfcfcfc;");
	auto gridLayout = new QGridLayout(centralwidget);
	gridLayout->setMargin(0);
	hSplitter = new QSplitter(centralwidget);
	hSplitter->setOrientation(Qt::Horizontal);
	auto horizontalLayout = new QWidget(hSplitter);
	auto explorerLayout = new QHBoxLayout(horizontalLayout);
	explorerLayout->setContentsMargins(0, 0, 0, 0);
	explorer = new QTreeWidget(horizontalLayout);
	explorer->headerItem()->setText(0, "Project Explorer");
	explorerLayout->addWidget(explorer);

	hSplitter->addWidget(horizontalLayout);
	vSplitter = new QSplitter(hSplitter);
	vSplitter->setOrientation(Qt::Vertical);
	auto verticalLayout = new QWidget(vSplitter);
	auto graphicsViewLayout = new QVBoxLayout(verticalLayout);
	graphicsView = new QGraphicsView(verticalLayout);
	graphicsViewLayout->setContentsMargins(0, 0, 0, 0);

	graphicsViewLayout->addWidget(graphicsView);

	vSplitter->addWidget(verticalLayout);
	auto verticalLayout2 = new QWidget(vSplitter);
	auto groupBoxLayout = new QVBoxLayout(verticalLayout2);
	groupBoxLayout->setContentsMargins(0, 0, 0, 0);
	auto groupBox = new QGroupBox(verticalLayout2);
	groupBox->setTitle("Error list");
	groupBoxLayout->addWidget(groupBox);
	auto gridLayout2 = new QGridLayout(groupBox);
	gridLayout2->setContentsMargins(2, 2, 2, 2);
	errorList = new QListWidget(groupBox);
	errorList->setStyleSheet("selection-background-color: #d62b2b;"
	"background-color:#ffe3e3;");
	gridLayout2->addWidget(errorList, 0, 0, 1, 1);

	vSplitter->addWidget(verticalLayout2);
	hSplitter->addWidget(vSplitter);
	gridLayout->addWidget(hSplitter, 0, 0, 1, 1);
	explorer->resize(0, explorer->height());
	toggleExplorer();
	errorList->resize(errorList->width(), 0);
	toggleErrorList();
	this->newFile();
}

void MainWindow::newFile()
{
	if (!maybeSave())
		return ;
	reset();
	current = nullptr;
	editor = new Editor();
}

void MainWindow::open()
{
	if (!maybeSave())
		return ;
	QString path = QFileDialog::getOpenFileName(this, "Open project", QDir::homePath(),
	"Open-PSA project (*.opsa);;All Files (*)");
	if (path.isEmpty())
		return ;
	// chargement du projet
	reset(); // a enlever si implémenté
}

void MainWindow::save()
{
	// save file
	modified = false; // si pas d'erreurs
}

void MainWindow::saveAs()
{
	QString path = QFileDialog::getSaveFileName(this, "Save project as", QDir::homePath(),
	"Open-PSA project (*.opsa);;All Files (*)");
	if (path.isEmpty())
		return ;
	// save file
	modified = false; // si pas d'erreurs
}

void MainWindow::closeEvent(QCloseEvent* e)
{
	if (!maybeSave())
	{
		e->ignore();
		return ;
	}
	if (modified)
		save(); // appeler saveAs tant que path vide
	QMainWindow::closeEvent(e);
}

void MainWindow::cut()
{
	modified = true;
}

void MainWindow::copy()
{
	
}

void MainWindow::paste()
{
	modified = true;
}

void MainWindow::addAnd()
{
	modified = true;
}

void MainWindow::addInhibit()
{
	modified = true;
}

void MainWindow::addOr()
{
	modified = true;
}

void MainWindow::addKN()
{
	modified = true;
}

void MainWindow::addXor()
{
	modified = true;
}

void MainWindow::addEvent()
{
	modified = true;
	QList<Event> &events = editor->getEvents();
	events << Event(editor->generateName(PREFIX_EVENT));
	Container c(&events.last()); // test
	EditContainerDialog(this, *editor, c).exec();
}

void MainWindow::addTransfert()
{
	modified = true;
}

void MainWindow::zoomIn()
{
	if ((zoomLevel *= 1.2) > ZOOM_MAX)
		zoomLevel = ZOOM_MAX;
	qDebug() << "Zoom In to " << zoomLevel;
}

void MainWindow::zoomOut()
{
	if ((zoomLevel *= 0.8) < ZOOM_MIN)
		zoomLevel = ZOOM_MIN;
	qDebug() << "Zoom Out to " << zoomLevel;
}

void MainWindow::zoomReset()
{
	zoomLevel = 100.0;
	qDebug() << "Zoom Reset to " << zoomLevel;
}

void MainWindow::showToolBar()
{
	if (showToolBarAct->isChecked())
		toolBar->show();
	else
		toolBar->hide();
}

void MainWindow::toggleExplorer()
{
	if (explorer->width())
	{
		resizeSplitter(hSplitter, 0, errorList->width());
		return ;
	}
	QSize size = this->size();
	int width = size.width() / 6;
	resizeSplitter(hSplitter, width, 4 * width);
}

void MainWindow::toggleErrorList()
{
	if (errorList->height())
	{
		resizeSplitter(vSplitter, graphicsView->height(), 0);
		return ;
	}
	QSize size = this->size();
	int height = size.height() / 3;
	resizeSplitter(vSplitter, 2 * height, height);
}

void MainWindow::showDistributions()
{
	ManageDistributionsDialog(this, editor->getDistributions()).exec();
}

void MainWindow::showEvents()
{
	ManageEventsDialog(this, editor->getEvents()).exec();
}

void MainWindow::evaluate()
{
	qDebug() << "Evaluate fault tree";
}

void MainWindow::about()
{
	QMessageBox::about(this, "About FTEdit",
	"FTEdit is an open source editor fault tree analysis tool.<br><br>"
	"License: GPLv3<br>Source code is available on "
	"<a href='https://github.com/ChuOkupai/FTEdit'>GitHub</a><br>");
}

void MainWindow::createActions()
{
	newAct = new QAction("&New project", this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip("Create a new project");
	newAct->setToolTip(newAct->statusTip());
	newAct->setIcon(QIcon(":assets/icons/new.png"));
	toolBar->addAction(newAct);
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

	openAct = new QAction("&Open...", this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip("Open an existing project");
	openAct->setToolTip(openAct->statusTip());
	openAct->setIcon(QIcon(":assets/icons/open.png"));
	toolBar->addAction(openAct);
	connect(openAct, &QAction::triggered, this, &MainWindow::open);

	saveAct = new QAction("&Save", this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip("Save the project to disk");
	saveAct->setToolTip(saveAct->statusTip());
	saveAct->setIcon(QIcon(":assets/icons/save.png"));
	toolBar->addAction(saveAct);
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);

	saveAsAct = new QAction("Save As...", this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip("Save the project to disk with a different name");
	saveAsAct->setToolTip(saveAsAct->statusTip());
	saveAsAct->setIcon(QIcon(":assets/icons/saveAs.png"));
	toolBar->addAction(saveAsAct);
	connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

	exitAct = new QAction("E&xit", this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip("Exit the application");
	exitAct->setToolTip(exitAct->statusTip());
	exitAct->setIcon(QIcon(":assets/icons/exit.png"));
	toolBar->addAction(exitAct);
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

	cutAct = new QAction("Cu&t", this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip("Cut the current selected node to the clipboard");
	cutAct->setToolTip(cutAct->statusTip());
	toolBar->addSeparator();
	cutAct->setIcon(QIcon(":assets/icons/cut.png"));
	toolBar->addAction(cutAct);
	connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

	copyAct = new QAction("&Copy", this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip("Copy the current selected node to the clipboard");
	copyAct->setToolTip(copyAct->statusTip());
	copyAct->setIcon(QIcon(":assets/icons/copy.png"));
	toolBar->addAction(copyAct);
	connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

	pasteAct = new QAction("&Paste", this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip("Paste the clipboard's contents into the current node");
	pasteAct->setToolTip(pasteAct->statusTip());
	pasteAct->setIcon(QIcon(":assets/icons/paste.png"));
	toolBar->addAction(pasteAct);
	connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

	addAndAct = new QAction("And", this);
	addAndAct->setStatusTip("Add a new and gate into the current tree");
	addAndAct->setToolTip(addAndAct->statusTip());
	addAndAct->setIcon(QIcon(":assets/icons/gate/and.png"));
	connect(addAndAct, &QAction::triggered, this, &MainWindow::addAnd);

	addInhibitAct = new QAction("Inhibit", this);
	addInhibitAct->setStatusTip("Add a new inhibit gate into the current tree");
	addInhibitAct->setToolTip(addInhibitAct->statusTip());
	addInhibitAct->setIcon(QIcon(":assets/icons/gate/inhibit.png"));
	connect(addInhibitAct, &QAction::triggered, this, &MainWindow::addInhibit);

	addOrAct = new QAction("Or", this);
	addOrAct->setStatusTip("Add a new or gate into the current tree");
	addOrAct->setToolTip(addOrAct->statusTip());
	addOrAct->setIcon(QIcon(":assets/icons/gate/or.png"));
	connect(addOrAct, &QAction::triggered, this, &MainWindow::addOr);

	addKNAct = new QAction("Voting or", this);
	addKNAct->setStatusTip("Add a new voting or gate into the current tree");
	addKNAct->setToolTip(addKNAct->statusTip());
	addKNAct->setIcon(QIcon(":assets/icons/gate/kn.png"));
	connect(addKNAct, &QAction::triggered, this, &MainWindow::addKN);

	addXorAct = new QAction("Xor", this);
	addXorAct->setStatusTip("Add a new xor gate into the current tree");
	addXorAct->setToolTip(addXorAct->statusTip());
	addXorAct->setIcon(QIcon(":assets/icons/gate/xor.png"));
	connect(addXorAct, &QAction::triggered, this, &MainWindow::addXor);

	addTransfertAct = new QAction("Transfert in", this);
	addTransfertAct->setStatusTip("Add a new transfert in gate into the current tree");
	addTransfertAct->setToolTip(addTransfertAct->statusTip());
	addTransfertAct->setIcon(QIcon(":assets/icons/gate/transfert.png"));
	connect(addTransfertAct, &QAction::triggered, this, &MainWindow::addTransfert);

	addEventAct = new QAction("Basic event", this);
	addEventAct->setStatusTip("Add a new basic event into the current tree");
	addEventAct->setToolTip(addEventAct->statusTip());
	addEventAct->setIcon(QIcon(":assets/icons/gate/basicEvent.png"));
	connect(addEventAct, &QAction::triggered, this, &MainWindow::addEvent);

	zoomInAct = new QAction("Zoom In", this); zoomInAct->setShortcuts(QKeySequence::ZoomIn);
	zoomInAct->setStatusTip("Zoom In");
	toolBar->addSeparator();
	zoomInAct->setIcon(QIcon(":assets/icons/zoomIn.png"));
	toolBar->addAction(zoomInAct);
	connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);

	zoomOutAct = new QAction("Zoom Out", this); zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
	zoomOutAct->setStatusTip("Zoom Out");
	zoomOutAct->setIcon(QIcon(":assets/icons/zoomOut.png"));
	toolBar->addAction(zoomOutAct);
	connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);

	zoomResetAct = new QAction("Reset Zoom", this);
	zoomResetAct->setStatusTip("Reset Zoom");
	zoomResetAct->setIcon(QIcon(":assets/icons/zoomReset.png"));
	toolBar->addAction(zoomResetAct);
	connect(zoomResetAct, &QAction::triggered, this, &MainWindow::zoomReset);

	showToolBarAct = new QAction("Show Toolbar", this);
	showToolBarAct->setStatusTip("Enable or disable Toolbar");
	showToolBarAct->setCheckable(true);
	showToolBarAct->setChecked(true);
	connect(showToolBarAct, &QAction::triggered, this, &MainWindow::showToolBar);

	toggleExplorerAct = new QAction("Toggle Project Explorer", this);
	toggleExplorerAct->setStatusTip("Display or hide Project Explorer section");
	connect(toggleExplorerAct, &QAction::triggered, this, &MainWindow::toggleExplorer);

	toggleErrorListAct = new QAction("Toggle Error List", this);
	toggleErrorListAct->setStatusTip("Display or hide Error List section");
	connect(toggleErrorListAct, &QAction::triggered, this, &MainWindow::toggleErrorList);

	distributionsAct = new QAction("Manage distributions...", this);
	distributionsAct->setStatusTip("Show the list of all distributions");
	connect(distributionsAct, &QAction::triggered, this, &MainWindow::showDistributions);

	eventsAct = new QAction("Manage events...", this);
	eventsAct->setStatusTip("Show the list of all events");
	connect(eventsAct, &QAction::triggered, this, &MainWindow::showEvents);

	evaluateAct = new QAction("Evaluate...", this);
	evaluateAct->setStatusTip("Perform a fault tree analysis");
	openAct->setToolTip(openAct->statusTip());
	toolBar->addSeparator();
	evaluateAct->setIcon(QIcon("assets/icons/evaluate.png"));
	toolBar->addAction(evaluateAct);
	connect(evaluateAct, &QAction::triggered, this, &MainWindow::evaluate);

	aboutAct = new QAction("About", this);
	aboutAct->setStatusTip("About FTEdit");
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

	aboutQtAct = new QAction("About Qt", this);
	aboutQtAct->setStatusTip("About Qt");
	connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
	QMenu *m, *m2, *m3;

	m = menuBar()->addMenu("&File");
	m->addAction(newAct);
	m->addAction(openAct);
	m->addAction(saveAct);
	m->addAction(saveAsAct);
	m->addSeparator();
	m->addAction(exitAct);

	m = menuBar()->addMenu("&Edit");
	m->addAction(cutAct);
	m->addAction(copyAct);
	m->addAction(pasteAct);
	m->addSeparator();

	m2 = m->addMenu("Add...");
		m3 = m2->addMenu("Gate...");
		m3->addAction(addAndAct);
		m3->addAction(addInhibitAct);
		m3->addAction(addOrAct);
		m3->addAction(addKNAct);
		m3->addAction(addXorAct);
		m3->addAction(addTransfertAct);
	m2->addAction(addEventAct);

	m = menuBar()->addMenu("&View");
	m->addAction(zoomInAct);
	m->addAction(zoomOutAct);
	m->addAction(zoomResetAct);
	m->addSeparator();
	m->addAction(showToolBarAct);
	m->addAction(toggleExplorerAct);
	m->addAction(toggleErrorListAct);

	m = menuBar()->addMenu("&Show");
	m->addAction(distributionsAct);
	m->addAction(eventsAct);

	m = menuBar()->addMenu("&Analysis");
	m->addAction(evaluateAct);

	m = menuBar()->addMenu("&Help");
	m->addAction(aboutAct);
	m->addAction(aboutQtAct);
}

bool MainWindow::maybeSave()
{
	if (!modified)
		return (true);
	const QMessageBox::StandardButton ret = QMessageBox::warning(this, "FTEdit",
	"Do you want to save the changes you made?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	if (ret == QMessageBox::Cancel)
		return (false);
	else if (ret == QMessageBox::Save)
		save();
	return (true);
}

void MainWindow::reset()
{
	if (editor)
		delete editor;
	editor = nullptr;
	modified = false;
}

void MainWindow::resizeSplitter(QSplitter *splitter, int widget1Size, int widget2Size)
{
	QList<int> l;

	l << widget1Size << widget2Size;
	splitter->setSizes(l);
	l.clear();
}
