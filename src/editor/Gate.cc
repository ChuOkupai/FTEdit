#include "Gate.hh"

Gate::Gate(QString name) :Node(),prop(name, false)
{}

Gate::~Gate()
{}

Properties& Gate::getProperties()
{
	return (prop);
}

QList<Node*>& Gate::getChildren()
{
	return (children);
}

Node* Gate::search(QPoint around)
{ 
	if (around.x() >= position.x() && around.x() < position.x() + NODE_X
	&& around.y() <= position.y() && around.y() > position.y() - NODE_Y)
		return (this);
	Node *n = nullptr;
	for (int i = 0;
	i < children.size() && !(n = children.at(i)->search(around)); ++i);
	return (n);
}



void Gate::balanceNodePos()
{
	QPoint tmp;
	for(int i =0; i<children.size();i++)
	{
		tmp.ry() = (this->position.y() - NODE_Y) -10;
		tmp.rx() = (this->position.x() + (i*(NODE_X))+(i*10));

		if(parent)
		{
			for(int j=0 ; j<parent->getChildren().size(); j++)
			{
				if(parent->getChildren()[j]->search(tmp) != nullptr)
				{
					this->position.setX(this->position.x()+(NODE_X +10));
					tmp.rx() = this->position.x();
					j--;
				}	
			}
		}	
		children[i]->setPosition(tmp);
		children[i]->balanceNodePos();

	}
}


void Gate::remove()
{
	for (int i = 0; i < children.size(); ++i)
		children[i]->remove();
	children.clear();
}