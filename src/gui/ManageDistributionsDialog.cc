#include "ManageDistributionsDialog.hh"
#include "WidgetLinker.hh"

VisitorDistributionName::VisitorDistributionName()
{}

void VisitorDistributionName::visit(Constant &distribution)
{
	distType = QString{ "Constant(%1)" }.arg(distribution.getValue(), 1, 'e', 2, '0');
}

void VisitorDistributionName::visit(Exponential &distribution)
{
	distType = QString{ "Exponential(%1)" }.arg(distribution.getLambda(), 1, 'e', 2, '0');
}

void VisitorDistributionName::visit(Weibull &distribution)
{
	distType = QString{ "Weibull(%1, %2)" }.arg(distribution.getScale(), 1, 'e', 2, '0')
	.arg(distribution.getShape(), 1, 'e', 2, '0');
}

QString VisitorDistributionName::type(Distribution *dist)
{
	distType.clear();
	dist->accept(*this);
	return (distType);
}

void ManageDistributionsDialog::cellChanged(int y, int x)
{
	if (x != 2)
		return ;
	QString s = table->item(y, 0)->text();
	bool keep = table->item(y, x)->checkState() == Qt::Checked;
	for (int i = 0; i < list.size(); ++i)
		if (s == list[i]->getProperties().getName())
		{
			list[i]->getProperties().setKeep(keep);
			break ;
		}
}

ManageDistributionsDialog::ManageDistributionsDialog(QWidget *parent, QList<Distribution*> &list)
: QDialog(parent), list(list)
{
	setWindowTitle("Distributions list");
	setWindowIcon(QIcon(":icons/manage.png"));
	resize(640, 480);
	auto layout = new QVBoxLayout(this);
	layout->setMargin(0);
	table = new QTableWidget(this);
	layout->addWidget(table);
	table->setColumnCount(4);
	table->setRowCount(list.size());
	table->setSortingEnabled(true);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QStringList header;
	header << "Name" << "Description" << "Keep ?" << "Value";  //"Law"
	table->setHorizontalHeaderLabels(header);
	table->verticalHeader()->setVisible(false);

	VisitorDistributionName v;
	for (int i = 0; i < list.size(); ++i)
	{
		Distribution *e = list[i];

		// Name
		auto *item = new QTableWidgetItem(e->getProperties().getName());
		table->setItem(i, 0, item);

		// Description
		item = new QTableWidgetItem(e->getProperties().getDesc());
		table->setItem(i, 1, item);

		// Keep
		item = new QTableWidgetItem;
		item->setCheckState(e->getProperties().getKeep() ? Qt::Checked : Qt::Unchecked);
		table->setItem(i, 2, item);

		// Value
		item = new QTableWidgetItem(v.type(e));
		table->setItem(i, 3, item);
	}

	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));

}
