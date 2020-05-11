#include "Transfert.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Transfert::Transfert() : Node() , link(nullptr)
{}

Transfert::Transfert(const Transfert& cop) : Node()
{
	setLink(cop.getLink());
}

Transfert::~Transfert()
{}

Tree* Transfert::getLink() const
{
	return link;
}
void Transfert::setLink(Tree* link)
{
	if (this->link)
		this->link->getProperties().decrementRefCount();
	this->link = link;
	if (link)
		link->getProperties().incrementRefCount();
}

bool Transfert::check(QList<QString>& errors)
{
	if (!link)
	{
		errors << "Transfert: There must be a link to a fault tree.";
	}
	Gate* g = link->getTop();
	g->check(errors);
	return(errors.size() == 0);
}

Node* Transfert::search(QPoint around)
{
	if (around.x() >= position.x() && around.x() < position.x() + (CARD_X /*+ CARD_GAP_X*/)
	&& around.y() <= position.y() && around.y() > position.y() - (CARD_Y + CARD_GAP_Y))
		return (this);
	Node* n = nullptr;
	return (n);
}

QPoint 	Transfert::top_node_coord(QPoint cpt)
{
	return cpt;
}

void Transfert::balanceNodePos()
{
	return;
}

bool Transfert::detectCycle(Node* n)
{
	bool ret = false;
	if(n == this)  ret = true;
	Gate * g = dynamic_cast<Gate*>(n);
	QList<Node*> tmp = g->getChildren();
	for(int i=0; i < tmp.size();i++)
	{
		ret = ret || detectCycle(tmp.at(i));
	}
	return ret;
}

void Transfert::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double Transfert::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}

void Transfert::remove()
{
	if(parent)
		this->detach();
	if (link)
		link->getProperties().decrementRefCount();
	link = nullptr;
	delete this;
}