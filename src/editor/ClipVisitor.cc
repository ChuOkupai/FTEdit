#include "ClipVisitor.hh"

ClipVisitor::ClipVisitor() : copied(nullptr), parent(nullptr){}

ClipVisitor::~ClipVisitor() 
{}

Node* ClipVisitor::getCopied() const
{
    return copied;
}

void ClipVisitor::visitChildren(Gate& gate,Gate* parent)
{
    if(!copied)
        copied = parent;    
    parent->attach(this->parent);
    for(int i =0; i< gate.getChildren().size();i++)
	{
        this->parent = parent;
		gate.getChildren().at(i)->accept(*this);
    }
}


void ClipVisitor::visit(And& andgate)
{
    auto gate = new And("",false);
    visitChildren(andgate,gate);
}


void ClipVisitor::visit(Or& orgate)
{
    auto gate = new Or("",false);
    visitChildren(orgate,gate);
}

void ClipVisitor::visit(Inhibit& inhibgate)
{
    auto gate = new Inhibit("",false);
    visitChildren(inhibgate,gate);
}

void ClipVisitor::visit(VotingOR& vorgate)
{
    auto gate = new VotingOR("",false);
    visitChildren(vorgate,gate);
}

void ClipVisitor::visit(Xor& xorgate)
{
    auto gate = new Xor("",false);
    visitChildren(xorgate,gate);
}

void ClipVisitor::visit(Transfert& transfertgate)
{
    (void)transfertgate;
    auto trans = new Transfert;
    if(!copied)
        copied = trans;    
    trans->attach(parent);
    
}

void ClipVisitor::visit(Container& container)
{
    (void)container;
    auto con = new Container(nullptr);
    if(!copied)
        copied = con;    
    con->attach(parent);
}