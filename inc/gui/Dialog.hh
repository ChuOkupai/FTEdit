#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"
#include "FTEdit_Evaluator.hh"
#include "WidgetLinker.hh"

// Choose a new distribution dialog
class ChooseDistributionDialog : public QDialog
{
	Q_OBJECT

private slots:
	// Add a new distribution to the Editor's distributions list.
	void closeEvent(QCloseEvent *event);

private:
	Editor &editor;
	QButtonGroup *laws; // Possible choices

public:
	ChooseDistributionDialog(QWidget *parent, Editor &editor);
};

// Basic Properties dialog layout
class PropertiesDialog : public QDialog
{
	Q_OBJECT

private:
	Properties *prop; // Current Properties
	QLineEdit *nameWidget; // Name text field
	QTextEdit *descWidget; // Description text field
	bool isValid;

private slots:
	// Quit when name is valid
	void closeEvent(QCloseEvent *event);
	// Checks if new name is unique
	void checkName();
	// Save the new description in Properties
	void editDesc();

signals:
	// When the name field is changed, send a signal if necessary
	void nameChanged(QString value);

protected:
	Editor &editor;

	// Initialize widgets (must be called if initialized was set to false)
	void init();
	// Sets new Properties
	void setProperties(Properties *prop);
	// Returns true if current name name is valid
	bool valid();

public:
	PropertiesDialog(QWidget *parent, Editor &editor, Properties *prop, bool initialized = true);
};

class ChooseResultDialog : public QDialog
{
	Q_OBJECT

private:
	Gate *top;
	QList<Result> &results;
	QCheckBox *useBoolean;
	QCheckBox *useMCS;
	DoubleSpinBox *missionTime;
	DoubleSpinBox *step;

private slots:
	void closeEvent(QCloseEvent *event);

	void checkChanged(int state);

public:
	// Stores Result in results list
	ChooseResultDialog(QWidget *parent, Gate *top, QList<Result> &list);
};

// Choose a new fault tree from list, store the index in treeIndex
class ChooseTreeDialog : public QDialog
{
	Q_OBJECT

private:
	Editor &editor;
	QComboBox *trees; // Possible choices
	int &treeIndex; // where to store the result

public:
	ChooseTreeDialog(QWidget *parent, Editor &editor, int &treeIndex);
};