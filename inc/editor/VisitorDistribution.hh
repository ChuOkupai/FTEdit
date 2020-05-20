#pragma once
#include "Distribution.hh"

class VisitorDistribution
{
public:
    virtual void visit(Constant& constdistrib) = 0;
    virtual void visit(Exponential& expdistrib) = 0;
    virtual void visit(Weibull& weibulldistrib) = 0;

};