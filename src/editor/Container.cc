#include "Container.hh"
#define NODE_X    120
#define NODE_Y    80

Container::Container(Event& event) : Node::Node()
{
    this->event = event;
}

Container::~Container() {}

void Container::setEvent(Event& event);
{
    if (!this->event)
        this->event = event;
}

double Container::getProbability(double time)
{
    return event.getDistribution()->getProbability(time);
}

Event& Container::getEvent()
{
    return event;
}

bool Container::check(QList<QString> &errors)
{
    
    if (!event.getDistribution())
    {
        QString error = event.getProperties().getName();
        error.append(": Probability must be set.\n");
        errors.append(error);
        return false;
    }
    return true;
}


Node* Container::search(QPoint around)
{
    return this;
}

void accept(Editor &editor, EditVisitor &visitor) {visitor.visit(*this);}

void accept(RenderVisitor &visitor) {visitor.visit(*this);}
