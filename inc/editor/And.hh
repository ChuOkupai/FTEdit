#pragma once
#include <QList>
#include "Gate.hh"

class And : public Gate
{
private:
	And(QString name);
	~And();
	double getProbability(double time);
	bool check (QList<QString>& errors);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
};