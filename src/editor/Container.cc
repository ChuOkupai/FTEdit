#include "Container.hh"
#include "Node.hh"
#include "FTEdit_FMS.hh"
//#include "EvalVisitor.hh"

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

double Container::getProbability(double time)
{
	return (event->getDistribution()->getProbability(time));
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

QList<Node*>* Container::getChildren()
{
	return nullptr;
}


void Container::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}

/* remove commentary when header is added
void Container::accept(EvalVisitor& visitor)
{
	visitor.visit(*this);
}
*/
//void accept(Editor &editor, EditVisitor &visitor) {visitor.visit(*this);}

//void accept(RenderVisitor &visitor) {visitor.visit(*this);}
