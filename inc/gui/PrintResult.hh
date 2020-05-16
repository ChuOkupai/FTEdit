#pragma once
#include <QtWidgets>
#include "Result.hh"

class PrintResult : public QDialog
{
	Q_OBJECT

public:
	PrintResult(QWidget *parent, Result *result);

private slots:
	void exportResult();

private:
	Result *result;
	QTableWidget *prb;
	QTableWidget *mcs;

	void initBoolean(ResultBoolean *res);
	void initMCS(ResultMCS *res);
};
