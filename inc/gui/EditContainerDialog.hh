#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

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
	bool valid;
	int index;
	QComboBox *events;
	QLineEdit *name;
	QTextEdit *desc;
	QComboBox *distributions;

public:
	EditContainerDialog(QWidget *parent, Editor &editor, Container &cont);
};