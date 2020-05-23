#pragma once
#include "VisitorNode.hh"
class PasteVisitor: public VisitorNode
{
private:
    Node* pasted;
    Gate* parent;
    Editor&    e;

    void visitChildren(Gate& gate,Gate* parent);
public:
    PasteVisitor(Editor& e);
    ~PasteVisitor();
    Node* getPasted() const;
 
    void visit(And& andgate);
    void visit(Or& orgate);
    void visit(Xor& xorgate);
    void visit(VotingOR& xorgate);
    void visit(Inhibit& inhibgate);
    void visit(Transfert& transfertgate);
    void visit(Container& container);
};