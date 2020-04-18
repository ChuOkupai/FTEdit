#include <QDebug>
#include "FTEdit.hh"

void test1(void)
{
	Editor e;

	e.detach();
	e.getGates() << new And(e.generateName(PREFIX_GATE));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getSelection()->setTop(e.getGates()[0]);
	Container *c1 = new Container(e.getEvents()[0]);
	c1->attach(e.getGates()[0]);
	Container *c2 = new Container(e.getEvents()[1]);
	c2->attach(e.getGates()[0]);
	e.remove(e.getSelection()->getTop());
	qDebug() << "Trees size: " << e.getTrees().size();
	qDebug() << "Events size: " << e.getEvents().size();
	qDebug() << "Gates size: " << e.getGates().size();
	e.refresh();
	qDebug() << "Trees size: " << e.getTrees().size();
	qDebug() << "Events size: " << e.getEvents().size();
	qDebug() << "Gates size: " << e.getGates().size();
}

int main(void)
{
	test1();
	return (0);
}
