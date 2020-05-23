#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class VisitorDistributionName : public VisitorDistribution
{
private:
	QString distType;

public:
	VisitorDistributionName();

	void visit(Constant &distribution);
	void visit(Exponential &distribution);
	void visit(Weibull &distribution);

	QString type(Distribution *dist);
};

class ManageDistributionsDialog : public QDialog
{
	Q_OBJECT

private slots:
    void cellChanged(int y, int x);
private:
	QList<Distribution*> &list;
    QTableWidget *table;

public:
	ManageDistributionsDialog(QWidget *parent, QList<Distribution*> &list);
};
