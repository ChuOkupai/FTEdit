#include "Gate.hh"
#include "FTEdit_FMS.hh"
//#include "EvalVisitor.hh"

VotingOR::VotingOR(QString name) : Gate(name)
{}

VotingOR::~VotingOR()
{}

int VotingOR::getK()const
{
    return k;
}

void VotingOR::setK(int k)
{
    this->k = k;
}

Gate* VotingOR::getSubTree()const
{
    return subTree;
}

double VotingOR::getProbability(double time)
{
    return subTree->getProbability(time);
}

bool VotingOR::check(QList<QString>& errors)
{
	if (children.size() < k)
	{
		errors << prop.getName() + ": k value must be less or equal children value.";
		return (false);
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() > 0);
}

/*
void VotingOR::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}
*/

/*
void VotingOR::accept(EvalVisitor& visitor)
{
	visitor.visit(*this);
}
*/

