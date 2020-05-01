#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class ManageEventsDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);

private:
	QList<Event> &list;

public:
	ManageEventsDialog(QWidget *parent,QList<Event> &list);
};