#pragma once
#include "Node.hh"
#include "Tree.hh"

class SaveVisitor;

class Transfert : public Node
{
    protected:
    Tree* link;
    Properties prop;
    QList<Node*> child;//contain only child of Transfer: top Gate
    public:
    Transfert(QString name);
    ~Transfert();

    Tree* getLink() const;
    void setLink(Tree* link);

    double getProbability(double time);
    bool check(QList<QString>& errors);

    Node* search(QPoint around);

    bool detectCycle(Node* n);
    QList<Node*>*	getChildren();
	Event* getEvent();//defined to prevent the class to be abstract
    void remove();
	void accept(SaveVisitor& visitor);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);


};