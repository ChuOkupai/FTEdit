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

static void first_pass(Node *n, int i, QVector<int> &maxX)
{
	QPoint p;
	if (n->getParent())
		p.setY(n->getParent()->getPosition().y() + CARD_Y + CARD_GAP_Y);
	Gate *g = dynamic_cast<Gate*>(n);
	if (g && g->getChildren().size())
	{
		if (n->getParent() && maxX[i - 1] > maxX[i])
			maxX[i] = maxX[i - 1];
		p.setX(maxX[i]);
		n->setPosition(p);
		int x = 0;
		for (int j = 0; j < g->getChildren().size(); ++j, x += CARD_X)
			first_pass(g->getChildren()[j], i + 1, maxX);
		x = g->getChildren().last()->getPosition().x() - g->getChildren().first()->getPosition().x();
		maxX[i] = g->getChildren().first()->getPosition().x() + x / 2;
		p.setX(maxX[i]);
		n->setPosition(p);
		maxX[i] += CARD_X;
		return ;
	}
	if (n->getParent() && maxX[i - 1] > maxX[i])
		maxX[i] = maxX[i - 1];
	p.setX(maxX[i]);
	n->setPosition(p);
	maxX[i] += CARD_X;
}

void Gate::balanceNodePos()
{
	QVector<int> maxX(64);
	first_pass(this, 0, maxX);
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
