#include "Gate.hh"

And::And(QString name) : Gate(name)
{}
And::~And()
{}

double And::getProbability(double time)
{
	(void)time;
	return (0);
}

bool And::check(QList<QString>& errors)
{
	if(children.count()<2)
	{
		errors << "And Gate "+ prop.getName() +" with less than 2 children";
		return false;
	}
	else
	{
		return true;
	}
	
}

/*void And::accept(Editor& editor,EditVisitor& visitor)
{
	visitor.visit(this);
}
void And::accept(RenderVisitor& visitor)
{
	visitor.visit(this);
}*/