#include "Gate.hh"
#include "Tree.hh"

Tree::Tree(QString name) :
prop(name, true), top(nullptr)
{}

Tree::Tree(const Tree& cop) : prop(cop.prop) , top(cop.getTop())
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
	if (this->top)
		this->top->getProperties().decrementRefCount();
	this->top = top;
	if (top)
		top->getProperties().incrementRefCount();
}