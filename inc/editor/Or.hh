#pragma once
#include "Gate.hh"

class Or : public Gate
{
private:
	Or(QString name);
	~Or();

	bool check (QList<QString>& errors);
	//void accept(Editor& editor,EditVisitor& visitor);
	//void accept(RenderVisitor& visitor);
};