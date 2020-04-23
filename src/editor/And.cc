#include "Gate.hh"

And::And(QString name) : Gate(name)
{}

And::~And()
{}

double And::getProbability(double time)
{
	double p = children[0]->getProbability(time);
	for (int i = 1; i < children.size(); ++i)
		p *= children.at(i)->getProbability(time);
	return (p);
}

bool And::check(QList<QString>& errors)
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

/*void And::accept(Editor& editor,EditVisitor& visitor)
{
	visitor.visit(this);
}
void And::accept(RenderVisitor& visitor)
{
	visitor.visit(this);
}*/