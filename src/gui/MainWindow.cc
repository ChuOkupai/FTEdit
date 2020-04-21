#include <QDir>
#include <QtGlobal>
#include <QtWidgets>
#include "MainWindow.hh"

MainWindow::MainWindow() : editor(nullptr), modified(false), zoomLevel(100)
{
/*---------------------------------------------------------------------------------*/
	//setFixedSize(1000,800);
    setWindowIcon(QIcon(":/src/gui/images/icone.ico"));

    m_mainwidget = new QWidget(this);
    setCentralWidget(m_mainwidget);

    v_layout = new QVBoxLayout(this);
   	h_layout = new QHBoxLayout();

    m_btn = new QPushButton("Evaluate", m_mainwidget);
    m_quit = new QPushButton("Quit", m_mainwidget);

    h_layout->addWidget(m_btn, 1, Qt::AlignRight);
    h_layout->addWidget(m_quit,0);
    h_layout->addWidget(onglets,100);
/*-----------------------------------------------*/
      // Dock widget
    dock = new QDockWidget(tr("Error List"), m_mainwidget);
    tree = new QTreeWidget(m_mainwidget);
    QStringList treeHeader;
    treeHeader<<"Header1"<<"Header2";
    tree->setHeaderLabels(treeHeader);
    //Set tree on dockWidget
    dock->setWidget(tree);
    // Place dock
    addDockWidget(Qt::BottomDockWidgetArea, dock);
/*-----------------------------------------------*/
    v_layout->addStretch(1);
    v_layout->addLayout(h_layout);

    onglets = new QTabWidget(m_mainwidget);
    onglets->setGeometry(5,10,170,350);

    QWidget *p1 = new QWidget;
    QWidget *p2 = new QWidget;

    onglets->addTab(p1, "Edition");
    onglets->addTab(p2, "Projet Explorer");

    grid = new QGridLayout;

	//fram = new QFrame(m_mainwidget);
	//fram->setGeometry(175,35,500,390);
	//fram->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
	//setAcceptDrops(true);

    p1->setLayout(grid);
    p2->setLayout(grid);

    m_mainwidget->setLayout(v_layout);  

    connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_btn, SIGNAL(clicked()), this, SLOT(openDialog()));


    QLabel *a = new QLabel(p1);
    a->setPixmap(QPixmap(":/src/gui/images/icones/evenementDeBase.gif"));
    a->move(10, 10);
    a->show();
    a->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *b = new QLabel(p1);
    b->setPixmap(QPixmap(":/src/gui/images/icones/porteEt.gif"));
    b->move(10, 80);
    b->show();
    b->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *c = new QLabel(p1);
    c->setPixmap(QPixmap(":/src/gui/images/icones/porteKN.gif"));
    c->move(10, 160);
    c->show();
    c->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *d = new QLabel(p1);
    d->setPixmap(QPixmap(":/src/gui/images/icones/porteNonEt.gif"));
    d->move(60, 10);
    d->show();
    d->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *e = new QLabel(p1);
    e->setPixmap(QPixmap(":/src/gui/images/icones/porteNonOu.gif"));
    e->move(60, 80);
    e->show();
    e->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *f = new QLabel(p1);
    f->setPixmap(QPixmap(":/src/gui/images/icones/porteTransfert.gif"));
    f->move(60, 160);
    f->show();
    f->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *g = new QLabel(p1);
    g->setPixmap(QPixmap(":/src/gui/images/icones/porteOuEx.gif"));
    g->move(120, 10);
    g->show();
    g->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *h = new QLabel(p1);
    h->setPixmap(QPixmap(":/src/gui/images/icones/porteOu.gif"));
    h->move(120, 80);
    h->show();
    h->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *i = new QLabel(p1);
    i->setPixmap(QPixmap(":/src/gui/images/icones/evenementMaison.gif"));
    i->move(120, 160);
    i->show();
    i->setAttribute(Qt::WA_DeleteOnClose);

   
   

/*---------------------------------------------------------------------------------*/
	createActions();
	createMenus();

	statusBar()->showMessage("A context menu is available by right-clicking");
	setWindowTitle("FTEdit");
	QRect r = QApplication::desktop()->screenGeometry();
	setMinimumSize(MIN(r.width(), RES_MIN_X), MIN(r.height(), RES_MIN_Y));
	resize(r.width() / 2, r.height() / 1.5);
	this->newFile();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);
	menu.exec(event->globalPos());
}

void MainWindow::newFile()
{
	if (!maybeSave())
		return ;
	reset();
}

void MainWindow::open()
{
	if (!maybeSave())
		return ;
	QString path = QFileDialog::getSaveFileName(this, "Open project", QDir::homePath(),
	"Open-PSA project (*.opsa);;All Files (*)");
	if (path.isEmpty())
		return ;
	// chargement du projet
	reset();
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
		return ;
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

void MainWindow::showDistributions()
{
	qDebug() << "showDistributions";
}

void MainWindow::showEvents()
{
	qDebug() << "showEvents";
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
	newAct = new QAction("&New", this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip("Create a new project");
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

	openAct = new QAction("&Open...", this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip("Open an existing project");
	connect(openAct, &QAction::triggered, this, &MainWindow::open);

	saveAct = new QAction("&Save", this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip("Save the project to disk");
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);

	saveAsAct = new QAction("Save As...", this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip("Save the project to disk with a different name");
	connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

	exitAct = new QAction("E&xit", this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip("Exit the application");
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

	cutAct = new QAction("Cu&t", this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip("Cut the current selected node to the clipboard");
	connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

	copyAct = new QAction("&Copy", this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip("Copy the current selected node to the clipboard");
	connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

	pasteAct = new QAction("&Paste", this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip("Paste the clipboard's contents into the current node");
	connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

	addAndAct = new QAction("And", this);
	addAndAct->setStatusTip("Add a new and gate into the current tree");
	connect(addAndAct, &QAction::triggered, this, &MainWindow::addAnd);

	addInhibitAct = new QAction("Inhibit", this);
	addInhibitAct->setStatusTip("Add a new inhibit gate into the current tree");
	connect(addInhibitAct, &QAction::triggered, this, &MainWindow::addInhibit);

	addOrAct = new QAction("Or", this);
	addOrAct->setStatusTip("Add a new or gate into the current tree");
	connect(addOrAct, &QAction::triggered, this, &MainWindow::addOr);

	addKNAct = new QAction("Voting or", this);
	addKNAct->setStatusTip("Add a new voting or gate into the current tree");
	connect(addKNAct, &QAction::triggered, this, &MainWindow::addKN);

	addXorAct = new QAction("Xor", this);
	addXorAct->setStatusTip("Add a new xor gate into the current tree");
	connect(addXorAct, &QAction::triggered, this, &MainWindow::addXor);

	addEventAct = new QAction("Basic event", this);
	addEventAct->setStatusTip("Add a new basic event into the current tree");
	connect(addEventAct, &QAction::triggered, this, &MainWindow::addEvent);

	addTransfertAct = new QAction("Transfert in", this);
	addTransfertAct->setStatusTip("Add a new transfert in gate into the current tree");
	connect(addTransfertAct, &QAction::triggered, this, &MainWindow::addTransfert);

	zoomInAct = new QAction("Zoom In", this);
	zoomInAct->setShortcuts(QKeySequence::ZoomIn);
	zoomInAct->setStatusTip("Zoom In");
	connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);

	zoomOutAct = new QAction("Zoom Out", this);
	zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
	zoomOutAct->setStatusTip("Zoom Out");
	connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);

	zoomResetAct = new QAction("Reset Zoom", this);
	zoomResetAct->setStatusTip("Reset Zoom");
	connect(zoomResetAct, &QAction::triggered, this, &MainWindow::zoomReset);

	distributionsAct = new QAction("Manage distributions...", this);
	distributionsAct->setStatusTip("Show the list of all distributions");
	connect(distributionsAct, &QAction::triggered, this, &MainWindow::showDistributions);

	eventsAct = new QAction("Manage events...", this);
	eventsAct->setStatusTip("Show the list of all events");
	connect(eventsAct, &QAction::triggered, this, &MainWindow::showEvents);

	evaluateAct = new QAction("Evaluate...", this);
	evaluateAct->setStatusTip("Perform a fault tree analysis");
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
	fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu("&Edit");
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	editMenu->addSeparator();

	addNodeMenu = editMenu->addMenu("Add...");
	addGateMenu = addNodeMenu->addMenu("Gate...");
		addGateMenu->addAction(addAndAct);
		addGateMenu->addAction(addInhibitAct);
		addGateMenu->addAction(addOrAct);
		addGateMenu->addAction(addKNAct);
		addGateMenu->addAction(addXorAct);
		addGateMenu->addAction(addTransfertAct);
	addNodeMenu->addAction(addEventAct);

	viewMenu = menuBar()->addMenu("&View");
	viewMenu->addAction(zoomInAct);
	viewMenu->addAction(zoomOutAct);
	viewMenu->addAction(zoomResetAct);
	viewMenu->addSeparator();
	viewMenu = menuBar()->addMenu("&Show");
	viewMenu->addAction(distributionsAct);
	viewMenu->addAction(eventsAct);

	analysisMenu = menuBar()->addMenu("&Analysis");
	analysisMenu->addAction(evaluateAct);

	helpMenu = menuBar()->addMenu("&Help");
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

bool MainWindow::maybeSave()
{
	if (!modified)
		return (true);
	const QMessageBox::StandardButton ret = QMessageBox::warning(this, "Application",
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
/*-----------------------------------------*/
void MainWindow::openDialog()
{
	QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle(tr("Resultat"));
    dlg->resize(600,400);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    QPushButton *m_btn = new QPushButton("Ok", dlg);
    m_btn->move(150,0);

    QVBoxLayout *v_layout = new QVBoxLayout(dlg);
   	QHBoxLayout *h_layout = new QHBoxLayout();

    h_layout->addWidget(m_btn, 0, Qt::AlignRight);
 

    v_layout->addStretch(1);
    v_layout->addLayout(h_layout);

    dlg->setLayout(v_layout);

    connect(m_btn, SIGNAL(clicked()), dlg, SLOT(accept()));
    dlg->exec();

}
/*-----------------------------------------*/