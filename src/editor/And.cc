#include "And.hh"

And::And(QString name) : Gate(name)
{}
And::~And()
{}

double And::getProbability(double time)
{
    return prop.getProbability(time);
}

bool And::check(QList<QString>& errors)
{
    if(children.count()<2)
    {
        errors << "And Gate "+ name +" with less than 2 children";
        return false;
    }
    else
    {
        return true;
    }
    
}

void And::accept(Editor& editor,EditVisitor& visitor)
{
    visitor.visit(this);
}
void And::accept(RenderVisitor& visitor)
{
    visitor.visit(this);
}