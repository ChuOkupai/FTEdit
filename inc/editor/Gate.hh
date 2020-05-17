#pragma once
#include <QList>
#include "Node.hh"
#include "Properties.hh"

class VisitorNode;
class EvalVisitor;

class Gate : public Node
{
protected:
	Properties prop;
	QList<Node*> children;

public:
	Gate(QString name,bool keep = true);
	virtual ~Gate();

	Properties&		getProperties();
	QList<Node*>&	getChildren();
	void 	balanceNodePos();	
	QPoint 	top_node_coord(QPoint cpt);
	Node*	search(QPoint around);
	void	remove();
};

class And : public Gate
{
public:
	And(QString name,bool keep = true);
	And( And&);
	~And();


	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);
};

class Inhibit : public Gate
{
	protected:
	bool condition;

	public:
	Inhibit(QString name,bool keep = true);
	Inhibit( Inhibit&);
	~Inhibit();

	bool getCondition() const;
	void setCondition(bool condition);
	
	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);


}; 

class Or : public Gate
{
public:
	Or(QString name,bool keep = true);
	Or( Or&);
	~Or();


	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);

};

class VotingOR : public Gate
{
	protected:
	int k;
	Gate* subTree;
	public:
	VotingOR(QString name,bool keep = true);
	VotingOR( VotingOR&);
	~VotingOR();


	void updateSubTree();
	Node* generateComb(int i,int k,int n);
	int getK() const;
	void setK(int k);
	Gate* getSubTree();
	bool check(QList<QString>& errors);
	void remove() override;
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);

};

class Xor : public Gate
{
public:
	Xor(QString name,bool keep = true);
	Xor( Xor&);
	~Xor();


	bool check(QList<QString>& errors);

	void accept(VisitorNode& visitor);
    double accept(EvalVisitor& eval);

};
