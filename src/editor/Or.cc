#include <QtGlobal>
#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Or::Or(QString name) : Gate(name)
{}

Or::Or(Or& cop) : Gate(cop.getProperties().getName())
{}

Or::~Or()
{}


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

void Or::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double Or::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}
