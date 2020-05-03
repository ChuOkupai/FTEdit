#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

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


void VotingOR::accept(VisitorNode& visitor)
{
    visitor.visit(*this);
}

double VotingOR::accept(EvalVisitor& eval)
{
    return eval.visit(*this);
}
