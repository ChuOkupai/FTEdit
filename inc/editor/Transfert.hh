#pragma once
#include "Node.hh"
#include "Tree.hh"

class VisitorNode;
class EvalVisitor;

class Transfert : public Node
{
protected:
    Tree* link;
public:
    Transfert();
    ~Transfert();

    Tree* getLink() const;
    void setLink(Tree* link);
    bool check(QList<QString>& errors);
    Node* search(QPoint around);
    bool detectCycle(Node* n);
    void balanceNodePos();
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);
    void remove();
};