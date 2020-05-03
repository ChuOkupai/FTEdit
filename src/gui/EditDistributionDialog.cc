#include "EditDistributionDialog.hh"

// VisitorEditDistribution

VisitorEditDistribution::VisitorEditDistribution(QWidget *parent, Editor &editor) :
parent(parent), editor(editor)
{}

void VisitorEditDistribution::visit(Constant &distribution)
{
	(void)distribution;
	//EditConstantDialog(parent, editor, distribution).exec();
}

void VisitorEditDistribution::visit(Exponential &distribution)
{
	(void)distribution;
	//EditExponentialDialog(parent, editor, distribution).exec();
}

void VisitorEditDistribution::visit(Weibull &distribution)
{
	(void)distribution;
	//EditWeibullDialog(parent, editor, distribution).exec();
}

// EditConstantDialog

/*EditConstantDialog::EditConstantDialog(QWidget *parent, Editor &editor, Constant &dist) :
QDialog(parent), editor(editor), dist(dist)
{

}

void EditConstantDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
}*/