#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class ManageDistributionsDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);

private:
	QList<Distribution*> &list;

public:
	ManageDistributionsDialog(QWidget *parent, QList<Distribution*> &list);
};