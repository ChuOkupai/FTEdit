#include "Gate.hh"

Gate::Gate(QString name) : prop(name, false)
{}

Gate::~Gate()
{}

Properties& Gate::getProperties()
{
	return (prop);
}

QList<Node*>* Gate::getChildren()
{
	return (&children);
}

Event* Gate::getEvent()
{
	return nullptr;
}

Node* Gate::search(QPoint around)
{ 
	if (around.x() >= position.x() && around.x() < position.x() + NODE_X
	&& around.y() >= position.y() && around.y() < position.y() + NODE_Y)
		return (this);
	Node *n = nullptr;
	for (int i = 0;
	i < children.size() && !(n = children.at(i)->search(around)); ++i);
	return (n);
}

void Gate::remove()
{
	for (int i = 0; i < children.size(); ++i)
		children[i]->remove();
	children.clear();
}