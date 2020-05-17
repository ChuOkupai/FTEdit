#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

And::And(QString name,bool keep) : Gate(name,keep)
{}

And::And(And& cop) : Gate (cop.getProperties().getName(),cop.getProperties().getKeep())
{}

And::~And()
{}



bool And::check(QList<QString>& errors)
{
	if (children.size() < 2)
	{
		errors << prop.getName() + ": There must be 2 or more inputs.";
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() == 0);
}
void And::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}
double And::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}