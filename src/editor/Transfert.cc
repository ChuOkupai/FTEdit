#include "Transfert.hh"
#include "Visitor.hh"

Transfert::Transfert(QString name) : Node() , link(nullptr) , prop(name,false)
{}

Transfert::~Transfert()
{}

Tree* Transfert::getLink() const
{
	return link;
}
void Transfert::setLink(Tree* link)
{
	if(link)
	{	
		this->link = link;
	}
}

double Transfert::getProbability(double time)
{
	Gate* g = link->getTop();
	return g->getProbability(time);
}

bool Transfert::check(QList<QString>& errors)
{
	Gate* g = link->getTop();
	g->check(errors);
	return(errors.size() > 0);
}

Node* Transfert::search(QPoint around)
{
	if (around.x() >= position.x() && around.x() < position.x() + NODE_X
	&& around.y() >= position.y() && around.y() < position.y() + NODE_Y)
		return (this);
	Node* n = nullptr;
	return (n);
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

void Transfert::accept(Visitor& visitor)
{
	visitor.visit(*this);
}

void Transfert::remove()
{
	link->getTop()->remove();
	link = nullptr;
	delete this;
}