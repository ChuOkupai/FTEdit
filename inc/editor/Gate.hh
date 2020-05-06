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
	Gate(QString name);
	~Gate();

	Properties&		getProperties();
	QList<Node*>&	getChildren();
	void 	balanceNodePos();	
	Node*	search(QPoint around);
	void	remove();
};

class And : public Gate
{
public:
	And(QString name);
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
	Inhibit(QString name);
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
	Or(QString name);
	Or( Or&);
	~Or();


	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);

};

class VotingOR : public Gate // TODO
{
	protected:
	int k;
	Gate* subTree;
	public:
	VotingOR(QString name);
	VotingOR( VotingOR&);
	~VotingOR();


	void updateSubTree();
	Gate* generateComb(int i,int k,int n);
	int getK() const;
	void setK(int k);
	Gate* getSubTree() const;
	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval);

};

class Xor : public Gate
{
public:
	Xor(QString name);
	Xor( Xor&);
	~Xor();


	bool check(QList<QString>& errors);

	void accept(VisitorNode& visitor);
	double accept(EvalVisitor& eval); //xor gate undefined in EvalVisitor

};