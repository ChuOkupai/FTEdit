#pragma once
#include "Gate.hh"
#include "Transfert.hh"
#include "Container.hh"

class EvalVisitor{
	private :
	double time;
	double proba;
	
<<<<<<< HEAD

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


<<<<<<< HEAD
public :
	EvalVisitor(double time,double proba);
	double visit(And& andVisitor);
	double visit(Or& orVisitor);
	double visit(Xor& xorVisitor);
	double visit(Inhibit& inVisitor);
	double visit(VotingOR& vorVisitor);
	double visit(Transfert& transVisitor);
	double visit(Container& eventVisitor);
	double getProba();
	void reset();
	void setTime(double time);
=======
>>>>>>> parent of dcbed97... Merge branch 'dev' into evaluator
=======

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


>>>>>>> parent of dcbed97... Merge branch 'dev' into evaluator
};
