#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"
#include "WidgetLinker.hh"

class EditContainerDialog : public QDialog
{
	Q_OBJECT

private slots:
	void closeEvent(QCloseEvent *event);
	void checkName();
	void setEvent(int index);
	void setDistribution(int index);
	void editDistribution();
	void addDistribution();

private:
	Editor &editor;
	Container &cont;
	int index;
	QComboBox *events;
	LineEditName *name;
	QTextEdit *desc;
	QComboBox *distributions;
	QPushButton *edit;

public:
	EditContainerDialog(QWidget *parent, Editor &editor, Container &cont);
};