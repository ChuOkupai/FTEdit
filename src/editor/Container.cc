#include "Container.hh"
#include "Node.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Container::Container(Event* event) :
Node::Node(), event(event)
{
	event->getProperties().incrementRefCount();
}

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

Event* Container::getEvent()
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
	(void)around;
	return (nullptr);
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