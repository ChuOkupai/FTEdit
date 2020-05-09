#pragma once
#include "Node.hh"
#include "Tree.hh"

class VisitorNode;
class EvalVisitor;

class Transfert : public Node
{
    protected:
    Tree* link;
    Properties prop;
    public:
    Transfert(QString name);
    Transfert(const Transfert&);
    ~Transfert();

    Tree* getLink() const;
    void setLink(Tree* link);
    Properties& getProperties();

    bool check(QList<QString>& errors);

    Node* search(QPoint around);
    void 	balanceNodePos();
    QPoint 	top_node_coord(QPoint cpt);
    bool detectCycle(Node* n);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);

    void remove();


};