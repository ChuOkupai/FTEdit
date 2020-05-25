#include "FTEdit_FMS.hh"
#include "PrintResult.hh"
#include "WidgetLinker.hh"

void PrintResult::exportResult()
{
	QString path(QDir::homePath() + "/fault-tree-analysis-" + date + ".csv");
	path = QFileDialog::getSaveFileName(this, "Export analysis", path, "Comma-separated values (*.csv)");
	if (path.isEmpty()) return ;
	FileManagerSystem fms;
	fms.exportAs(path, *result);
	if (fms.getErrorMessage().isEmpty())
		return ;
	QMessageBox msg(this);
	msg.setIcon(QMessageBox::Critical);
	msg.setWindowTitle("Error");
	msg.setText(fms.getErrorMessage());
	msg.exec();
}

void PrintResult::initBoolean(ResultBoolean *res)
{
	QList<double> l = res->getProbabilities();
	prb->setRowCount(l.size());
	double t = 0;
	int i = 0;
	for (double p : l)
	{
		// Time
		auto item = new QTableWidgetItem(DoubleSpinBox::toStringNotFilled(t, 'e', 12));
		item->setToolTip(DoubleSpinBox::toStringNotFilled(t, 'f', 12));
		prb->setItem(i, 0, item);

		// Failure rate
		item = new QTableWidgetItem(DoubleSpinBox::toStringNotFilled(p, 'e', 12));
		item->setToolTip(DoubleSpinBox::toStringNotFilled(p, 'f', 12));
		prb->setItem(i, 1, item);

		t += res->getStep();
		++i;
	}
}

void PrintResult::initMCS(ResultMCS *res)
{
	QList<double> l = res->getProbabilities();
	QList<QList<QString>> l2 = res->getMCS();
	QString set;
	mcs->setRowCount(l2.size());
	for (int i = 0; i < l2.size(); ++i)
	{
		// Probability
		auto *item = new QTableWidgetItem(DoubleSpinBox::toStringNotFilled(l[i], 'e', 12));
		item->setToolTip(DoubleSpinBox::toStringNotFilled(l[i], 'f', 12));
		mcs->setItem(i, 0, item);

		// Quantity
		QList<QString> &l3(l2[i]);
		item = new QTableWidgetItem(QString::number(l3.size()));
		mcs->setItem(i, 1, item);

		// Events
		set = l3.first();
		for (int j = 1; j < l3.size(); ++j)
			set += " / " + l3[j];
		item = new QTableWidgetItem(set);
		mcs->setItem(i, 2, item);
		set.clear();
	}
}

PrintResult::PrintResult(QWidget *parent, Result *result, QString date) :
QDialog(parent), result(result), date(date)
{
	QStringList header;
	setWindowTitle("Analysis results - " + date);
	setWindowIcon(QIcon(":icons/manage.png"));
	resize(640, 480);
	auto layout = new QVBoxLayout(this);
	layout->setMargin(1);
	WidgetLinker linker(this, layout);
	auto tabs = linker.addTabWidget();
	linker.set(tabs);
	auto menu = new QMenuBar(this);
	auto m = menu->addMenu("&File");
	auto exportAct = new QAction("Export...", this);
	exportAct->setShortcut(QKeySequence("Ctrl+E"));
	exportAct->setStatusTip("Export data to a file in CSV format");
	exportAct->setIcon(QIcon(":icons/saveAs.png"));
	connect(exportAct, &QAction::triggered, this, &PrintResult::exportResult);
	m->addAction(exportAct);
	layout->setMenuBar(menu);
	QVBoxLayout *l;
	QWidget *w;
	if (result->getResultBoolean())
	{
		l = new QVBoxLayout;
		l->setMargin(1);
		w = new QWidget;
		w->setLayout(l);

		prb = new QTableWidget(this);
		prb->setColumnCount(2);
		header << "Time" << "Failure rate of " + result->getResultBoolean()->getTopEventName();
		prb->setHorizontalHeaderLabels(header);
		header.clear();
		prb->setSortingEnabled(true);
		prb->setEditTriggers(QAbstractItemView::NoEditTriggers);
		prb->verticalHeader()->setVisible(false);
		prb->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		prb->horizontalHeader()->setStretchLastSection(true);
		l->addWidget(prb);
		tabs->addTab(w, QString("Probabilities"));
		initBoolean(result->getResultBoolean());
	}
	if (result->getResultMCS())
	{
		l = new QVBoxLayout;
		l->setMargin(1);
		w = new QWidget;
		w->setLayout(l);

		auto label = new QLabel;
		label->setText("TopEvent propability risk: " + DoubleSpinBox::toStringNotFilled(result->getResultMCS()->getProbabilities().last(), 'e', 4));
		label->setToolTip(DoubleSpinBox::toStringNotFilled(result->getResultMCS()->getProbabilities().last(), 'f', 12));
		l->addWidget(label);

		mcs = new QTableWidget;
		mcs->setColumnCount(3);
		header << "Probability" << "Quantity" << "Events";
		mcs->setHorizontalHeaderLabels(header);
		mcs->setSortingEnabled(true);
		mcs->setEditTriggers(QAbstractItemView::NoEditTriggers);
		mcs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		mcs->horizontalHeader()->setStretchLastSection(true);
		l->addWidget(mcs);
		tabs->addTab(w, QString("Minimal cuts set"));
		initMCS(result->getResultMCS());
	}

	tabs->setCurrentIndex(0);
}
