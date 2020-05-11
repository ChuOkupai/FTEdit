#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class ManageDistributionsDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);
    void cellChanged(int y, int x);
private:
	QList<Distribution*> &list;
    QTableWidget *table;

public:
	ManageDistributionsDialog(QWidget *parent, QList<Distribution*> &list);
};
