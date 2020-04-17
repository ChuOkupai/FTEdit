#include "Gate.hh"

Gate::Gate(QString name) : Properties(name)
{
    QList<Node*> children;
}

Gate::~Gate()
{

}

Properties& Gate::getProperties()
{
    return prop;
}

QList<Node*>& Gate::getChildren()
{
    return children;
}

Node* Gate::search(QPoint around)
{
    if(around == getPostion()) return this; else return nullptr;
}