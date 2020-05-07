#pragma once
#include "Dialog.hh"

class EditContainerDialog : public PropertiesDialog
{
	Q_OBJECT

private:
	Container &cont;
	QComboBox *events;
	QComboBox *distributions;
	QPushButton *edit;
	int index;

private slots:
	void updateName(QString s);
	void setEvent(int index);
	void setDistribution(int index);
	void editDistribution();
	void addDistribution();

public:
	EditContainerDialog(QWidget *parent, Editor &editor, Container &cont);
};