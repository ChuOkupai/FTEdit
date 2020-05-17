#pragma once
#include "VisitorNode.hh"
class ClipVisitor: public VisitorNode
{
private:
    Node* copied;
    Gate* parent;

    void visitChildren(Gate& gate,Gate* parent);
public:
    ClipVisitor();
    ~ClipVisitor();
    Node* getCopied() const;
 
    void visit(And& andgate);
    void visit(Or& orgate);
    void visit(Xor& xorgate);
    void visit(VotingOR& xorgate);
    void visit(Inhibit& inhibgate);
    void visit(Transfert& transfertgate);
    void visit(Container& container);
};