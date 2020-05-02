#include "Transfert.hh"
#include "FTEdit_FMS.hh"

Transfert::Transfert(QString name) : Node(),  link(nullptr),prop(name,false)
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

		if(!this->child.isEmpty())
		{
			this->child.replace(0,link->getTop());
		}
		else
		{
			this->child.append(link->getTop());
		}

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
	QList<Node*>* tmp = n->getChildren();
	if(tmp)
	{
		for(int i=0; i < tmp->size();i++)
		{
			ret = ret || detectCycle(tmp->at(i));
		}
	}	
	return ret;
}

QList<Node*>* Transfert::getChildren()//child is top Gate returned as QList.
{ 
	return (&child);
}


Event* Transfert::getEvent()
{
	return nullptr;
}

void Transfert::remove()
{
	link->getTop()->remove();
	link = nullptr;
	child.clear();
}
void Transfert::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}

/*void Transfert::remove(Node *top)
{
	delete this;
}*/