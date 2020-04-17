#pragma once
#include <QString>
#include <QList>
#include "Gate.hh"

class Or : public Gate
{
private:
    Or(QString name);
    ~Or();
    double getProbability(double time);
    bool check (QList<QString>& errors);
    void accept(Editor& editor,EditVisitor& visitor);
    void accept(RenderVisitor& visitor);
};