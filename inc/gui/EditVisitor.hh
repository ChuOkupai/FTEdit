#pragma once
#include "Dialog.hh"
#include "WidgetLinker.hh"

// Generic visitor for Node properties editing
class EditVisitor : public VisitorNode
{
private:
	QWidget *parent;
	Editor &editor;

public:
	EditVisitor(QWidget *parent, Editor &editor);

	void visit(And &gate);

	void visit(Or &gate);

	void visit(Xor &gate);

	void visit(VotingOR &gate);

	void visit(Inhibit &gate);

	void visit(Transfert &gate);

	void visit(Container &cont);
};

// Basic dialog box for generic gate (AND, OR, XOR...) with common Properties
class EditGateDialog : public PropertiesDialog
{
	Q_OBJECT

public:
	EditGateDialog(QWidget *parent, Editor &editor, Gate &gate, QString name);
};

// Almost like EditGateDialog except it has one more parameter
class EditInhibitDialog : public PropertiesDialog
{
	Q_OBJECT

private:
	Inhibit &gate;
	QComboBox *condition;

public:
	EditInhibitDialog(QWidget *parent, Editor &editor, Inhibit &gate);
};

// Almost like EditGateDialog except it has one more parameter
class EditVotingORDialog : public PropertiesDialog
{
	Q_OBJECT

private:
	VotingOR &gate;
	QSpinBox *k;

private slots:
	void updateK(int k2);

public:
	EditVotingORDialog(QWidget *parent, Editor &editor, VotingOR &gate);
};

class EditTransfertDialog : public QDialog
{
	Q_OBJECT

private:
	Editor &editor;
	Transfert &gate;
	QComboBox *trees;

public:
	EditTransfertDialog(QWidget *parent, Editor &editor, Transfert &gate);
};

// Complex dialog box for Container
class EditContainerDialog : public PropertiesDialog
{
	Q_OBJECT

private:
	Container &cont;
	QComboBox *events; // Choose an event between...
	QComboBox *distributions; // Choose a distribution between...
	QPushButton *edit; // Edit distribution
	int index; // Mandatory for slots

private slots:
	void updateName(QString s);
	void setEvent(int index);
	void setDistribution(int index);
	void editDistribution();
	void addDistribution();

public:
	EditContainerDialog(QWidget *parent, Editor &editor, Container &cont);
};