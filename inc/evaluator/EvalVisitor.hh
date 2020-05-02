#pragma once
#include "Gate.hh"
#include "Transfert.hh"
#include "Container.hh"

class EvalVisitor{
	private :
	double time;
	double proba;
	

	public :
		EvalVisitor(double time,double proba);
		double visit(And& andVisitor);
		double visit(Or& orVisitor);
		double visit(Inhibit& inVisitor);
        double visit(VotingOr const& vorVisitor);
		double visit(Transfert& transVisitor);
		double visit(Container& eventVisitor);
		double getProba();
		void reset();
		void setTime(double time);


};
