#include "Gate.hh"

Gate::Gate(QString name) : prop(name)
{

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
    if(around.x() >= position.x() && around.x() < (position.x() + NODE_X) && around.y() <= position.y() && around.y() > position.y() - NODE_Y) return this; else return nullptr;
}