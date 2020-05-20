#pragma once
#include "Gate.hh"
#include "Container.hh"
#include "Transfert.hh"

class VisitorNode
{
public:    
    virtual void visit(And& andgate) = 0;
    virtual void visit(Or& orgate) = 0;
    virtual void visit(Xor& xorgate) = 0;
    virtual void visit(VotingOR& xorgate) = 0;
    virtual void visit(Inhibit& inhibgate) = 0;
    virtual void visit(Transfert& transfertgate) = 0;
    virtual void visit(Container& container) = 0;
};