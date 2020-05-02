#include "Distribution.hh"
#include "Visitor.hh"

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

void Constant::accept(Visitor& visitor)
{
	visitor.visit(*this);
}