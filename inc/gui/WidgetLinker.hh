#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"

/*
** Classe qui sert d'interface temporaire pour simplifier la création des
** éléments disposés sur la fenêtre.
*/

class LineEditName : public QLineEdit
{
private:
	Editor &editor;
	bool isValid;

public:
	LineEditName(QWidget *parent, Editor &editor);

	// Checks if name is valid compared to the old one
	// This method should be called with signal editingFinished() in your own method
	// Returns a valid QString in any case
	QString check(Properties &prop);
	// Returns true if name is valid
	bool valid() const;
};

class WidgetLinker
{
private:
	QWidget *parent;
	QBoxLayout *layout;

public:
	WidgetLinker(QWidget *parent, QBoxLayout *layout);
	~WidgetLinker();

	QComboBox *addComboBox();

	QLabel *addLabel(const QString &content);

	QLayoutItem *addLayoutItem(QLayoutItem *item);

	QLineEdit *addLineEdit(const QString &content);

	// Custom widget
	LineEditName *addLineEditName(Editor &editor);

	QPushButton *addPushButton(const QString &content);

	QRadioButton *addRadioButton(const QString &content);

	QTextEdit *addTextEdit(const QString &content);

	// Sets the parent widget
	void set(QWidget *parent);
	// Sets a layout make a link with the previous one
	void set(QBoxLayout *layout);
	// Use another layout
	void replace(QBoxLayout *layout, QBoxLayout *with);
};