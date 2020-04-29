#include "Distribution.hh"
#include "../fms/SaveVisitor.hh"

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

void Constant::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}