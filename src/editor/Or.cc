#include <QtGlobal>
#include "Gate.hh"

Or::Or(QString name) : Gate(name)
{}

Or::~Or()
{}

double Or::getProbability(double time)
{
	double p = children[0]->getProbability(time);
	for (int i = 1; i < children.size(); ++i)
		p += children.at(i)->getProbability(time);
	return (qBound(0.0, p, 1.0));
}

bool Or::check(QList<QString>& errors)
{
	if (children.size() < 2)
	{
		errors << prop.getName() + ": There must be 2 or more inputs.";
		return (false);
	}
	return (true);
}

/*void Or::accept(Editor& editor,EditVisitor& visitor)
{
	visitor.visit(this);
}
void Or::accept(RenderVisitor& visitor)
{
	visitor.visit(this);
}*/