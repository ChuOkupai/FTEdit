#include "Node.hh"


Node::Node() :
parent(nullptr), position(0, 0)
{}

Node::~Node()
{}

Gate* Node::getParent()
{
	return this->parent;
}

QPoint Node::getPosition()
{
	return this->position; 
}

void Node::setPosition(QPoint position)
{
	this->position = position;
}

void Node::attach(Gate* parent)
{
	this->parent = parent;
}

Node* Node::detach()
{
	return (nullptr);
}
