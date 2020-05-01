#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

class ChooseDistributionDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);
	void confirm();

private:
	Editor &editor;
	Distribution **dist; // where to store the new distribution
	QButtonGroup *laws;

public:
	ChooseDistributionDialog(QWidget *parent, Editor &editor, Distribution **dist);
};