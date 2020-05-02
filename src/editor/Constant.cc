#include "Distribution.hh"
#include "VisitorDistribution.hh"

Constant::Constant(QString name) :
Distribution(name)
{}

Constant::~Constant()
{}

double Constant::getProbability(double time)
{
	(void)time;
	return (value);
}

void Constant::accept(VisitorDistribution& visitor)
{
	visitor.visit(*this);
}