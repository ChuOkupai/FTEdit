#pragma once
#include <QList>
#include "Node.hh"
#include "Properties.hh"

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

	Node*	search(QPoint around);
};

class And : public Gate
{
private:
	And(QString name);
	~And();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
};

class Inhibit; // TODO

class Or : public Gate
{
private:
	Or(QString name);
	~Or();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
};

class VotingOR; // TODO

class Xor : public Gate
{
private:
	Xor(QString name);
	~Xor();

	double getProbability(double time);

	bool check(QList<QString>& errors);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
};