#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class ManageEventsDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);
	void cellChanged(int y, int x);

private:
	QList<Event> &list;
	QTableWidget *table;

public:
	ManageEventsDialog(QWidget *parent, QList<Event> &list);
};