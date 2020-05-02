#pragma once
#include <QList>
#include "Node.hh"
#include "Properties.hh"

class VisitorNode;

class Gate : public Node
{
protected:
	Properties prop;
	QList<Node*> children;

public:
	Gate(QString name);
	~Gate();

	Properties&		getProperties();
    QList<Node*>*	getChildren();
    Event* getEvent();//defined to prevent the class to be abstract

	Node*	search(QPoint around);
	void	remove();
};

class And : public Gate
{
public:
	And(QString name);
	~And();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
};

class Inhibit : public Gate
{
	protected:
	bool condition;

	public:
	Inhibit(QString name);
	~Inhibit();

	bool getCondition() const;
	void setCondition(bool condition);
	double getProbability(double time);

	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);

}; 

class Or : public Gate
{
public:
	Or(QString name);
	~Or();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
};

class VotingOR : public Gate // TODO
{
	protected:
	int k;
	Gate* subTree;
	public:
	VotingOR(QString name);
	~VotingOR();


	void updateSubTree();
	Gate* generateComb(int i,int k,int n);
	int getK() const;
	void setK(int k);
	Gate* getSubTree() const;
	double getProbability(double time);
	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
};

class Xor : public Gate
{
public:
	Xor(QString name);
	~Xor();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	void accept(VisitorNode& visitor);
};
