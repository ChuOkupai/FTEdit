#include <QtGlobal>
#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Or::Or(QString name,bool keep) : Gate(name,keep)
{}


Or::~Or()
{}


bool Or::check(QList<QString>& errors)
{
	if (children.size() < 2)
	{
		errors << prop.getName() + ": There must be 2 or more inputs.";
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() == 0);
}

void Or::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double Or::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}
