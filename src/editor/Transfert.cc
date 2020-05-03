#include "Transfert.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

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
	link->getTop()->remove();
	link = nullptr;
	delete this;
}