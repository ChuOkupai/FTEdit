#include "PrintResult.hh"


PrintResult::PrintResult(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean, QList<QString> errors)
        : QDialog(parent), resultMCS(resultMCS), resultBoolean(resultBoolean), errors(errors)
{
   

}
PrintResult::PrintResult(QWidget *parent, Result *result)
        : QDialog(parent), result(result)
{
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
    table->setColumnCount(3);

    ResultMCS *resmcs =  result->getResultMCS();
    QList<double> proMcs = resmcs->getProbabilities();
    QList<QList<QString>> mcs = resmcs->getMCS();
    int a = proMcs.size();

    table->setRowCount(a);
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Event" << "Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i < a; ++i)
    {

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
    header << "Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i < a; ++i)
    {

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


