#pragma once
#include "Gate.hh"
#include "Transfert.hh"
#include "Container.hh"

class EvalVisitor{
	public :
		EvalVisitor();
		void visit(And& andVisitor);
		void visit(Or& orVisitor);
		void visit(Inhibit& inVisitor);
        //void visit(VotingOr const& vorVisitor);
//		void visit(Transfert& transVisitor);
		void visit(Container& eventVisitor);

};
