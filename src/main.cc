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

void test2(void)
{
	QList<QString>	errors;
	Editor			e;
	FileManagerSystem fms;
	
	e.detach();
	e.getGates() << new And(e.generateName(PREFIX_GATE));
	Gate* g = new Inhibit(e.generateName(PREFIX_GATE));
	e.getGates() << g;
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getSelection()->setTop(e.getGates()[0]);
	g->attach(e.getGates()[0]);
	((Inhibit*)g)->setCondition(true);
	Container *c1 = new Container(&(e.getEvents()[0]));
	c1->attach(e.getGates()[0]);
	Container *c2 = new Container(&(e.getEvents()[1]));
	c2->attach(e.getGates()[1]);
	//Container *c3 = new Container(&(e.getEvents()[0]));
	//c3->attach(e.getGates()[1]);
	e.refresh();
	e.getSelection()->getTop()->check(errors);
	errors.removeDuplicates();
	if (errors.size())
	{
		qDebug() << "Errors list:";
		for (int i = 0; i < errors.size(); ++i)
			qDebug() << errors.at(i);
	}
	
	fms.saveAs("lol.opsa", &e);

	qDebug() << "Trees size: " << e.getTrees().size();
	qDebug() << "Events size: " << e.getEvents().size();
	qDebug() << "Gates size: " << e.getGates().size();
}

/*
void test3(void)
{
	QList<QString>	errors;
	Editor			e;
	FileManagerSystem fms;

	e.detach();
	e.getGates() << new And(e.generateName(PREFIX_GATE));
	Transfert *t = new Transfert();
	e.getTrees()[0] = Tree("lol");
	t->setLink(&e.getTrees()[0]);
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getSelection()->setTop(e.getGates()[0]);
	Container *c1 = new Container(&(e.getEvents()[0]));
	c1->attach(e.getGates()[0]);
	e.refresh();

	fms.saveAs("lol.opsa", &e);

}
*/

void test4(void)
{
	QList<QString>	errors;
	Editor			e;
	FileManagerSystem fms;

	e.detach();
	e.getGates() << new And(e.generateName(PREFIX_GATE));
	e.getEvents() << Event(e.generateName(PREFIX_EVENT));
	e.getDistributions() << new Constant(e.generateName(PREFIX_DISTRIBUTION));
	e.getSelection()->setTop(e.getGates()[0]);
	Container *c1 = new Container(&(e.getEvents()[0]));
	e.getEvents()[0].setDistribution(e.getDistributions()[0]);
	c1->attach(e.getGates()[0]);
	e.refresh();

	fms.saveAs("lol.opsa", &e);

}

int main(int argc, char **argv)
{
	(void) argc, (void)argv;
	test4();
}
