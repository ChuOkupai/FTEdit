#include "Container.hh"
#include "Node.hh"

Container::Container(Event& event) :
Node::Node(), event(event)
{
	event.getProperties().incrementRefCount();
}

Container::~Container()
{
	event.getProperties().decrementRefCount();
}

void Container::setEvent(Event& event)
{
	this->event = event;
}

double Container::getProbability(double time)
{
	return (event.getDistribution()->getProbability(time));
}

Event& Container::getEvent()
{
	return (event);
}

bool Container::check(QList<QString> &errors)
{
	if (!event.getDistribution())
	{
		errors << event.getProperties().getName() + ": Probability must be set.";
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

//void accept(Editor &editor, EditVisitor &visitor) {visitor.visit(*this);}

//void accept(RenderVisitor &visitor) {visitor.visit(*this);}
