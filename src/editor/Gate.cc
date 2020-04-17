#include "Gate.hh"

Gate::Gate(QString name) : Properties(name)
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
    if(around.x < (Position.x + 60) && around.x >(Position.x - 60) && around.y <(Position.y +40) && around.y>(Position.y -40)) return this; else return nullptr;
}