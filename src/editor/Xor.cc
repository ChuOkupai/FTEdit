#include <QtGlobal>
#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Xor::Xor(QString name) : Gate(name)
{}

Xor::~Xor()
{}


bool Xor::check(QList<QString>& errors)
{
    if (children.size() != 2)
    {
        errors << prop.getName() + ": There must be 2 inputs.";
        return (false);
    }
    return (true);
}

void Xor::accept(VisitorNode& visitor)
{
    visitor.visit(*this);
}

/* xor gate undefined in EvalVisitor
double Xor::accept(EvalVisitor& eval)
{
    return eval.visit(*this);
}
*/
