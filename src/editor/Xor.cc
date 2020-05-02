#include <QtGlobal>
#include "Gate.hh"
#include "VisitorNode.hh"

Xor::Xor(QString name) : Gate(name)
{}

Xor::~Xor()
{}

double Xor::getProbability(double time)
{
	double p = children[0]->getProbability(time);
	p += children[1]->getProbability(time);
	return (qBound(0.0, p, 1.0));
}

bool Xor::check(QList<QString>& errors)
{
	if (children.size() != 2)
	{
		errors << prop.getName() + ": There must be 2 inputs.";
		return (false);
	}
	return (true);
}

void Xor::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}
