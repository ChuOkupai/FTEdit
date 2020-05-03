#pragma once
#include "FTEdit_Editor.hh"
#include "WidgetLinker.hh"

// Le visiteur (pour automatiquement choisir le bon dialogue)
class VisitorEditDistribution : public VisitorDistribution
{
private:
	QWidget *parent;
	Editor &editor;

public:
	VisitorEditDistribution(QWidget *parent, Editor &editor);

	void visit(Constant &distribution);
	void visit(Exponential &distribution);
	void visit(Weibull &distribution);
};

/*class EditConstantDialog : public QDialog
{
	Q_OBJECT

private:
	Editor &editor;
	Constant &dist;

private slots:
	void closeEvent(QCloseEvent *event);
	void checkName();

public:
	EditConstantDialog(QWidget *parent, Editor &editor, Constant &dist);
};

class EditExponentialDialog : public QDialog
{
	Q_OBJECT

private:
	Editor &editor;
	Exponential &dist;

private slots:
	void closeEvent(QCloseEvent *event);
	void checkName();

public:
	EditExponentialDialog(QWidget *parent, Editor &editor, Exponential &dist);
};

class EditWeibullDialog : public QDialog
{
	Q_OBJECT

private:
	Editor &editor;
	Weibull &dist;

private slots:
	void closeEvent(QCloseEvent *event);
	void checkName();

public:
	EditWeibullDialog(QWidget *parent, Editor &editor, Weibull &dist);
};*/