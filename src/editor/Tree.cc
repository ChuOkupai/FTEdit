#include "Tree.hh"

Tree::Tree(QString name) :
prop(name, true), top(nullptr)
{}

Tree::~Tree()
{}

Properties &Tree::getProperties()
{
	return (prop);
}

Gate *Tree::getTop() const
{
	return (top);
}

void Tree::setTop(Gate *top)
{
	this->top = top;
}