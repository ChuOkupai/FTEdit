#include "Or.hh"

Or::Or(QString name) : Gate(name)
{}

Or::~Or()
{}

double Or::getProbability(double time)
{
    return prop.getProbability(time);
}


bool Or::check(QList<QString>& errors)
{

    if(children.count()<2)
    {
        errors << "Or Gate "+ name +" with less than 2 children";
        return false;
    }
    else
    {
        return true;
    }
    

}

void Or::accept(Editor& editor,EditVisitor& visitor)
{
    visitor.visit(this);
}
void Or::accept(RenderVisitor& visitor)
{
    visitor.visit(this);
}