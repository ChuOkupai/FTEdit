#pragma once
#include "Node.hh"
#include "Tree.hh"

class VisitorNode;

class Transfert : public Node
{
    protected:
    Tree* link;
    Properties prop;
    public:
    Transfert(QString name);
    ~Transfert();

    Tree* getLink() const;
    void setLink(Tree* link);

    double getProbability(double time);
    bool check(QList<QString>& errors);

    Node* search(QPoint around);

    bool detectCycle(Node* n);
	void accept(VisitorNode& visitor);
    void remove();


};