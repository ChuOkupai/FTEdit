#include "Gate.hh"


Inhibit::Inhibit(QString name) : Gate(name)
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

double Inhibit::getProbability(double time)
{
    if(condition) return children.at(0)->getProbability(time);
    else return 0;
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