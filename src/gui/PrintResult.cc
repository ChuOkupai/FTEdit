#include "PrintResult.hh"


PrintResult::PrintResult(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean, QList<QString> errors)
        : QDialog(parent), resultMCS(resultMCS), resultBoolean(resultBoolean), errors(errors)
{
   

}
PrintResult::PrintResult(QWidget *parent, Result *result)
        : QDialog(parent), result(result)
{
    //QMenu *m = new QMenu(this);
    //m = menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);
    //m = menuBar()->addMenu("&Menu");
    //QAction *newAct = new QAction("&Export Result", this);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip("Create a new project");
    //newAct->setToolTip(newAct->statusTip());
    //connect(newAct, &QAction::triggered, this, &MainWindow::open);
    //m->addAction(newAct);

    setWindowTitle("Results");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QTableWidget *table = new QTableWidget(this);
    layout->addWidget(table);
    table->setColumnCount(5);

    QList<QString> err = result->getErrors();
    QListWidget *listErrors = new QListWidget(this);
    for(int i = 0; i< err.size(); ++i)
    {
        new QListWidgetItem(err[i], listErrors);
    }

    ResultMCS *resmcs =  result->getResultMCS();
    QList<double> proMcs = resmcs->getProbabilities();
    QList<QList<QString>> mcs = resmcs->getMCS();

    ResultBoolean *resB = result->getResultBoolean();
    QList<double> proB = resB->getProbabilities();

    table->setRowCount(proB.size());
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Event" << "Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i <proB.size(); ++i)
    {
        double e = proB[i];

        // value
        auto *item = new QTableWidgetItem(e);
        table->setItem(i, 0, item);
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));

}
void PrintResult::PrintResultMCS()
{
    setWindowTitle("Results MCS");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QTableWidget *table = new QTableWidget(this);
    layout->addWidget(table);
    table->setColumnCount(2);

    ResultMCS *resmcs =  result->getResultMCS();
    QList<double> proMcs = resmcs->getProbabilities();
    QList<QList<QString>> cs = resmcs->getMCS();
    int m = cs.size();

    table->setRowCount(m);
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Minimal Cut Set" << "Name";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i < m; ++i)
    {
        // MCS
        auto *item = new QTableWidgetItem();
        table->setItem(i, 0, item);

        double d = proMcs[i];
        // Proba pour
        item = new QTableWidgetItem(d);
        table->setItem(i, 1, item);
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}
void PrintResult::PrintResultBoolean()
{
    setWindowTitle("Results Boolean");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QTableWidget *table = new QTableWidget(this);
    layout->addWidget(table);
    table->setColumnCount(2);

    ResultBoolean *resB = result->getResultBoolean();
    QString topEvenet = resB->getTopEventName();
    QList<double> proB = resB->getProbabilities();
    int a = proB.size();
    table->setRowCount(a);
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Top Event Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    // Name
    auto *item = new QTableWidgetItem(topEvenet);
    table->setItem(0, 0, item);


    for (int i = 1; i < a; ++i)
    {
        double d = proB[i];

        // Proba
        item = new QTableWidgetItem(d);
        table->setItem(i, 1, item);

    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}

void PrintResult::PrintResultErrors()
{

    setWindowTitle("Errors");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);

    QList<QString> err = result->getErrors();
    QListWidget *listErrors = new QListWidget(this);
    for(int i = 0; i< err.size(); ++i)
    {
        new QListWidgetItem(err[i], listErrors);
    }
}


/*
void PrintResult::cellChanged(int y, int x)
{
    if (x != 2)
        return ;
    QString s = table->item(y, 0)->text();
    bool keep = table->item(y, x)->checkState() == Qt::Checked;
    for (int i = 0; i < list.size(); ++i)
        if (s == list[i].getProperties().getName())
        {
            list[i].getProperties().setKeep(keep);
            break ;
        }
}
*/


