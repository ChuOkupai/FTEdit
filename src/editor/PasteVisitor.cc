#include "PasteVisitor.hh"

PasteVisitor::PasteVisitor(Editor& e) : pasted(nullptr), parent(nullptr), e(e){}

PasteVisitor::~PasteVisitor() 
{}

Node* PasteVisitor::getPasted() const
{
    return pasted;
}

void PasteVisitor::visitChildren(Gate& gate,Gate* child)
{
    e.getGates() << child;
    if(!pasted)
        pasted = child; 
    child->attach(this->parent);
    for(int i =0; i< gate.getChildren().size();i++)
	{
        this->parent = child;
		gate.getChildren().at(i)->accept(*this);
    }
}


void PasteVisitor::visit(And& andgate)
{
    auto gate = new And(e.generateName(PREFIX_GATE));
    visitChildren(andgate,gate);
}


void PasteVisitor::visit(Or& orgate)
{
    auto gate = new Or(e.generateName(PREFIX_GATE));
    visitChildren(orgate,gate);
}

void PasteVisitor::visit(Inhibit& inhibgate)
{
    auto gate = new Inhibit(e.generateName(PREFIX_GATE));
    visitChildren(inhibgate,gate);
}

void PasteVisitor::visit(VotingOR& vorgate)
{
    auto gate = new VotingOR(e.generateName(PREFIX_GATE));
    visitChildren(vorgate,gate);
}

void PasteVisitor::visit(Xor& xorgate)
{
    auto gate = new Xor(e.generateName(PREFIX_GATE));
    visitChildren(xorgate,gate);
}

void PasteVisitor::visit(Transfert& transfertgate)
{
    (void)transfertgate;
    auto trans = new Transfert;
    if(!pasted)
        pasted = trans;    
    trans->attach(parent);
    
}

void PasteVisitor::visit(Container& container)
{
    (void)container;
    e.getEvents() << Event(e.generateName(PREFIX_EVENT));
    auto con = new Container(&e.getEvents().last());
    
    if(!pasted)
        pasted = con; 
    con->attach(parent);
}