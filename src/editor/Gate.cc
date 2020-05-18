#include "Gate.hh"

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

static void first_pass(Node *n, int i, QVector<int> &levelNextX) //first pass
{
	n->setPosition(QPoint(levelNextX[i],
	(n->getParent() ? n->getParent()->getPosition().y() + CARD_Y + CARD_GAP_Y : 0)));
	levelNextX[i] += CARD_X;
	if (dynamic_cast<Gate*>(n))
	{
		Gate *g = dynamic_cast<Gate*>(n);
		for (int j = 0; j < g->getChildren().size(); ++j)
			first_pass(g->getChildren()[j], i + 1, levelNextX);
	}
}

void Gate::balanceNodePos()
{
	QVector<int> levelNextX(64);
	first_pass(this, 0, levelNextX);
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