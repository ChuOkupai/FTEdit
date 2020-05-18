#pragma once
#include "FTEdit_Editor.hh"
#include <QDebug>

class CutVisitor : public VisitorNode
{
private :
    QList<QList<Node*>>& cutset;
    QList<Container*>& containers;
    int i;//index de cutset[i][j]
    int j;//index de cutset[i][j]

public :
    CutVisitor(QList<QList<Node*>>& cutset, QList<Container*>& containers);
    ~CutVisitor();

    void visit(And& andgate);
    void visit(Or& orgate);
    void visit(Xor& xorgate);
    void visit(VotingOR& xorgate);
    void visit(Inhibit& inhibgate);
    void visit(Transfert& transfertgate);
    void visit(Container& container);
    void setIndex(int i, int j);//donner le visitor les index de la porte courante

};
