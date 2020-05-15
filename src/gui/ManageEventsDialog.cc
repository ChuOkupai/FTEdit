#include "ManageEventsDialog.hh"
#include "WidgetLinker.hh"

void ManageEventsDialog::closeEvent(QCloseEvent *event)
{
	table->setRowCount(0); // Delete all items stored in table
	event->accept();
}

void ManageEventsDialog::cellChanged(int y, int x)
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

ManageEventsDialog::ManageEventsDialog(QWidget *parent, QList<Event> &list)
: QDialog(parent), list(list)
{
	setWindowTitle("Events list");
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
	header << "Name" << "Description" << "Keep ?" << "Distribution";
	table->setHorizontalHeaderLabels(header);
	table->verticalHeader()->setVisible(false);

	for (int i = 0; i < list.size(); ++i)
	{
		Event &e = list[i];

		// Name
		auto *item = new QTableWidgetItem(e.getProperties().getName());
		table->setItem(i, 0, item);

		// Description
		item = new QTableWidgetItem(e.getProperties().getDesc());
		table->setItem(i, 1, item);

		// Keep
		item = new QTableWidgetItem;
		item->setCheckState(e.getProperties().getKeep() ? Qt::Checked : Qt::Unchecked);
		table->setItem(i, 2, item);

		// Distribution
		Distribution *dist = e.getDistribution();
		item = new QTableWidgetItem(dist ? dist->getProperties().getName() : "");
		table->setItem(i, 3, item);
	}
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}