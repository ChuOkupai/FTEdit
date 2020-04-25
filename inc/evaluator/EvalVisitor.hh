#pragma once
#include "Gate.hh"
#include "Transfert.hh"
#include "Container.hh"

class EvalVisitor{
	public :
		void visit(And const& andVisitor);
		void visit(Or const& orVisitor);
		void visit(Inhibit const& inVisitor);
        //void visit(VotingOr const& vorVisitor);
		void visit(Transfert const& transVisitor);
		void visit(Container const& eventVisitor);

};
