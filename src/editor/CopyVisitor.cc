#include "CopyVisitor.hh"

template<typename Base, typename T>
inline bool instanceof(const T* a) {
    return dynamic_cast<const Base*>(a) != nullptr;
}

CopyVisitor::CopyVisitor() : copied(nullptr) {}

CopyVisitor::~CopyVisitor() 
{
    //if(copied)
    //    copied->remove();
}

Node* CopyVisitor::getCopied() const
{
    return copied;
}

void CopyVisitor::setCopied(Node* n)
{
    //delete copied;
    copied = n;
}

Gate* CopyVisitor::find(Node * n,QString name)
{
    if (instanceof<Gate>(n))
    {
        Gate * g = dynamic_cast<Gate*>(n);
        if(g->getProperties().getName() == name)
            return g;
        else
        {
        for(int i =0; i< g->getChildren().size();i++)
        {
            Gate* tmp = find(g->getChildren().at(i),name);
            if(tmp) return tmp;
        }
        }
    }
    return nullptr;
    
}

void CopyVisitor::visit(And& andgate)
{
    if(!copied)
        copied = new And(andgate);
	else
    {
        And * tmp = new And(andgate);
        tmp->attach(find(copied,andgate.getParent()->getProperties().getName()));        
    }
    
    for(int i =0; i< andgate.getChildren().size();i++)
	{
		andgate.getChildren().at(i)->accept(*this);
	}
}

void CopyVisitor::visit(Or& orgate)
{
    if(!copied)
        copied = new Or(orgate);
	else
    {
        Or * tmp = new Or(orgate);
        tmp->attach(find(copied,orgate.getParent()->getProperties().getName())) ;       
    }
    
    for(int i =0; i< orgate.getChildren().size();i++)
	{
		orgate.getChildren().at(i)->accept(*this);
	}
}

void CopyVisitor::visit(Inhibit& inhibgate)
{
    if(!copied)
        copied = new Inhibit(inhibgate);
	else
    {
        Inhibit * tmp = new Inhibit(inhibgate);
        tmp->attach(find(copied,inhibgate.getParent()->getProperties().getName()));        
    }
    
    for(int i =0; i< inhibgate.getChildren().size();i++)
	{
		inhibgate.getChildren().at(i)->accept(*this);
	}
}

void CopyVisitor::visit(VotingOR& vorgate)
{
    if(!copied)
        copied = new VotingOR(vorgate);
	else
    {
        VotingOR * tmp = new VotingOR(vorgate);
        tmp->attach(find(copied,vorgate.getParent()->getProperties().getName()));        
    }
    
    for(int i =0; i< vorgate.getChildren().size();i++)
	{
		vorgate.getChildren().at(i)->accept(*this);
	}
}

void CopyVisitor::visit(Xor& xorgate)
{
    if(!copied)
        copied = new Xor(xorgate);
	else
    {
        Xor * tmp = new Xor(xorgate);
        tmp->attach(find(copied,xorgate.getParent()->getProperties().getName()));        
    }
    
    for(int i =0; i< xorgate.getChildren().size();i++)
	{
		xorgate.getChildren().at(i)->accept(*this);
	}
}

void CopyVisitor::visit(Transfert& transfertgate)
{
    if(!copied)
        copied = new Transfert(transfertgate);
	else
    {
        Transfert * tmp = new Transfert(transfertgate);
        tmp->attach(find(copied,transfertgate.getParent()->getProperties().getName()));        
    }
    
}

void CopyVisitor::visit(Container& container)
{
    if(!copied)
        copied = new Container(container);
	else
    {
        Container * tmp = new Container(container);
        tmp->attach(find(copied,container.getParent()->getProperties().getName()));        
    }
}