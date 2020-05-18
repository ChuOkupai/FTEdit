#include "Gate.hh"
#include <cmath>

Gate::Gate(QString name,bool keep) :Node(),prop(name, keep)
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
	if (around.x() >= position.x() && around.x() < position.x() + (CARD_X) 
	&& around.y() <= position.y() && around.y() > position.y() - (CARD_Y + CARD_GAP_Y))
		return (this);
	Node *n = nullptr;
	for (int i = 0;
	i < children.size() && !(n = children.at(i)->search(around)); ++i);
	return (n);
}

static void first_pass(Node* me,int niveau,QVector<int>& liste)//first pass
{	
	QPoint tmp;

	if(liste[niveau] == -1)
	{
		if(!me->getParent())
		{
			liste[niveau] = 0;
			tmp.setX(liste[niveau]);
		}
		else
		{
			liste[niveau] = me->getParent()->getPosition().x();
			tmp.setX(liste[niveau]);
			tmp.setY(me->getParent()->getPosition().y());
		}
	}
	else
	{
		liste[niveau] += CARD_X;
		tmp.setX(liste[niveau]);
	}
	tmp.setY(niveau * (CARD_Y + CARD_GAP_Y));
	me->setPosition(tmp);

	if(dynamic_cast<Gate*>(me))
	{
		Gate* tmp = dynamic_cast<Gate*>(me);
		for(int i =0; i<tmp->getChildren().size();i++)
		{	
			first_pass(tmp->getChildren()[i],niveau+1,liste);
		}
	}
}

void Gate::balanceNodePos()
{
	QVector<int> liste(50);
	for(int i =0;i<50;i++)
	{
		liste[i] = -1;
	}
	int niveau = 0;
	first_pass(this,niveau,liste);
}


void Gate::remove()
{
	if(getProperties().getKeep()) // Gate from Editor
	{
		if(parent)
			this->detach();
		while (children.size())
			children[0]->remove();
		getProperties().setKeep(false);
		return ;
	}
	// Else Clipboard / VotingOR subtree
	for (int i = 0; i < children.size(); ++i)
		if (children[i]->getParent() == this)
			children[i]->remove();
	delete this;
}