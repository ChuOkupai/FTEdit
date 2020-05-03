#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

// Choose a new distribution dialog
class ChooseDistributionDialog : public QDialog
{
	Q_OBJECT

private slots:
	// Add a new distribution to the Editor's distributions list.
	void closeEvent(QCloseEvent *event);
	// Calls closeEvent
	void confirm();

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
	// Qui when name is valid
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