#include "FTEdit.hh"

void test1(void)
{
	QList<QString>	errors;
	Editor			e;

	e.detach();
	e.getGates() << new And(e.generateName(PREFIX_GATE));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getSelection()->setTop(e.getGates()[0]);
	Container *c1 = new Container(&(e.getEvents()[0]));//changed to remove compiling mismatched type
	c1->attach(e.getGates()[0]);
	Container *c2 = new Container(&(e.getEvents()[1]));//changed to remove compiling mismatched type
	c2->attach(e.getGates()[0]);
	e.refresh();
	e.getSelection()->getTop()->check(errors);
	errors.removeDuplicates();
	if (errors.size())
	{
		qDebug() << "Errors list:";
		for (int i = 0; i < errors.size(); ++i)
			qDebug() << errors.at(i);
	}

	qDebug() << "Trees size: " << e.getTrees().size();
	qDebug() << "Events size: " << e.getEvents().size();
	qDebug() << "Gates size: " << e.getGates().size();
	e.remove(e.getSelection()->getTop());
	qDebug() << "Trees size: " << e.getTrees().size();
	qDebug() << "Events size: " << e.getEvents().size();
	qDebug() << "Gates size: " << e.getGates().size();
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	MainWindow window;

	window.show();
	return app.exec();
}
