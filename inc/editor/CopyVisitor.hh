#pragma once
#include "VisitorNode.hh"
#include <QString>
class CopyVisitor: public VisitorNode
{
private:
    Node* copied;

public:
    CopyVisitor();
    ~CopyVisitor();
    Node* getCopied() const;
    void  setCopied(Node* n);
 
    Gate* find(Node* n,QString name);

    void visit(And& andgate);
    void visit(Or& orgate);
    void visit(Xor& xorgate);
    void visit(VotingOR& xorgate);
    void visit(Inhibit& inhibgate);
    void visit(Transfert& transfertgate);
    void visit(Container& container);
};