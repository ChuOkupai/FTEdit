#include "ManageEventsDialog.hh"
#include "WidgetLinker.hh"

void ManageEventsDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
}

ManageEventsDialog::ManageEventsDialog(QWidget *parent, QList<Event> &list)
: QDialog(parent), list(list)
{
	setWindowTitle("Events list");
}