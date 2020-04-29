#pragma once
#include "Node.hh"
#include "Tree.hh"

class SaveVisitor;

class Transfert : public Node
{
    protected:
    Tree* link;
    public:
    Transfert();
    ~Transfert();

    Tree* getLink() const;
    void setLink(Tree* link);

    double getProbability(double time);
    bool check(QList<QString>& errors);

    Node* search(QPoint around);

    bool detectCycle(Node* n);
	void accept(SaveVisitor& visitor);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
    //void remove();


};