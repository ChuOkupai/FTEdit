#include "Transfert.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

Transfert::Transfert() : Node() , link(nullptr)
{}

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
		return(errors.size() == 0);
	}
	else
	{
		if(link->getTop())
		{
			if(detectCycle(link->getTop()))
			{
				errors << "Transfert: Fault tree linked result in a loop.";
				return(false);//no need to check link because the loop was already checked.	
			}
			Gate* g = link->getTop();
			g->check(errors);
			return(errors.size() == 0);
		}
		else
		{
			errors << "Transfert: Fault tree linked is empty.";
			return(errors.size() == 0);
		}
	}
}

Node* Transfert::search(QPoint around)
{
	if (around.x() >= position.x() && around.x() < position.x() + (CARD_X)
	&& around.y() <= position.y() && around.y() > position.y() - (CARD_Y + CARD_GAP_Y))
		return (this);
	Node* n = nullptr;
	return (n);
}

void Transfert::balanceNodePos()
{
	return;
}

bool Transfert::detectCycle(Node* n)
{
	bool ret = false;
	if(n == this) return true;
	if(dynamic_cast<Gate*>(n))
	{
		Gate * g = dynamic_cast<Gate*>(n);
		for(int i=0; i <g->getChildren().size();i++)
		{
			if((ret = detectCycle(g->getChildren()[i])))
			break;
		}
	}
	if(dynamic_cast<Transfert*>(n))
	{
		Transfert* t = dynamic_cast<Transfert*>(n);
		if(t->getLink())
		{
			if(t->getLink()->getTop() == this->getLink()->getTop())
				return true;
			ret = detectCycle(t->getLink()->getTop());
		}
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