#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"


Inhibit::Inhibit(QString name) : Gate(name)
{}

Inhibit::Inhibit (Inhibit& cop) : Gate(cop.getProperties().getName()) , condition(cop.getCondition())
{}


Inhibit::~Inhibit()
{}

bool Inhibit::getCondition() const
{
    return condition;
}

void Inhibit::setCondition(bool condition)
{
    this->condition = condition;
}


bool Inhibit::check (QList<QString>& errors)
{
    if(children.size() != 1)
    {
        errors << prop.getName() + ": There must be only 1 input.";
		return (false);
    }
    children.at(0)->check(errors);
    return (errors.size() > 0);
}

void Inhibit::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double Inhibit::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}