#include <QtGlobal>
#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Xor::Xor(QString name,bool keep) : Gate(name,keep)
{}

Xor::Xor(Xor& cop) : Gate(cop.getProperties().getName(),cop.getProperties().getKeep())
{}


Xor::~Xor()
{}


bool Xor::check(QList<QString>& errors)
{
	if (children.size() != 2)
	{
		errors << prop.getName() + ": There must be 2 inputs.";
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() == 0);
}

void Xor::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}


double Xor::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}
