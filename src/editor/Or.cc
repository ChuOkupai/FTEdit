#include <QtGlobal>
#include "Gate.hh"
#include "Visitor.hh"

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
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() > 0);
}

void Or::accept(Visitor& visitor)
{
	visitor.visit(*this);
}
