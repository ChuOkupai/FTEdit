#include "PrintResult.hh"


PrintResultat::PrintResultat(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean)
        : QDialog(parent), resultMCS(resultMCS), resultBoolean(resultBoolean)
{
   

}
void PrintResultat::PrintResultMCS()
{
    setWindowTitle("Results MCS");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QTableWidget *table = new QTableWidget(this);
    layout->addWidget(table);
    table->setColumnCount(4);
    table->setRowCount(resultMCS->getProbabilities().size());
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Event" << "Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i < resultMCS->getProbabilities().size(); ++i)
    {

    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}
void PrintResultat::PrintResultBoolean()
{
    setWindowTitle("Results Boolean");
    resize(640, 480);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QTableWidget *table = new QTableWidget(this);
    layout->addWidget(table);
    table->setColumnCount(4);
    table->setRowCount(resultBoolean->getProbabilities().size());
    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Name" << "Value";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    for (int i = 0; i < resultBoolean->getProbabilities().size(); ++i)
    {

    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}



