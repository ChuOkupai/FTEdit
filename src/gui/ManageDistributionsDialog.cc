#include "ManageDistributionsDialog.hh"
#include "WidgetLinker.hh"

void ManageDistributionsDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
}

ManageDistributionsDialog::ManageDistributionsDialog(QWidget *parent, QList<Distribution*> &list)
: QDialog(parent), list(list)
{
	setWindowTitle("Distributions list");
	setWindowIcon(QIcon(":icons/manage.png"));
}