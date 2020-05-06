#include "Container.hh"
#include "Node.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Container::Container(Event* event) :
Node::Node(), event(event)
{
	event->getProperties().incrementRefCount();
}

Container::Container(const Container& cop) : Node() , event(cop.getEvent())
{}

Container::~Container()
{
	if(this->event)
		event->getProperties().decrementRefCount();
}




void Container::setEvent(Event* event)
{
	if(this->event)//décrémente si event non null
			this->event->getProperties().decrementRefCount();
	this->event = event;
	if(this->event)//incrémente si event non null
		this->event->getProperties().incrementRefCount();
}

Event* Container::getEvent() const
{
	return (event);
}

bool Container::check(QList<QString> &errors)
{
	if (!event->getDistribution())
	{
		errors << event->getProperties().getName() + ": Probability must be set.";
		return (false);
	}
	return (true);
}


Node* Container::search(QPoint around)
{
	/*
	if(around == this->position)
	return(this);
	else
	{
		return this;
	}
	*/
	
	if (around.x() >= position.x() && around.x() < position.x() + NODE_X
	&& around.y() <= position.y() && around.y() > position.y() - NODE_Y)
		return (this);
	Node* n = nullptr;
	return (n);
	
}

void Container::balanceNodePos()
{
	return;
}

void Container::remove()
{
	delete this;
}

void Container::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double Container::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}