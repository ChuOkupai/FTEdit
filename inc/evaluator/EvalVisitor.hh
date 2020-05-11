#pragma once
#include "FTEdit_Editor.hh"

class EvalVisitor{
private :
	double time;

public :
	EvalVisitor(double time);
	double visit(And& andVisitor);
	double visit(Or& orVisitor);
    double visit(Xor& XorVisitor);
	double visit(Inhibit& inVisitor);
	double visit(VotingOR& vorVisitor);
	double visit(Transfert& transVisitor);
	double visit(Container& eventVisitor);
	double getProba(Gate* top,double time);
	void setTime(double time);
};
