#include "EvalVisitor.hh"

EvalVisitor::EvalVisitor(){}

double EvalVisitor::getProba(Gate *top,double time){
	this->time = time;
	return top->accept(*this);
}


double EvalVisitor::visit(And& andVisitor){
	double result = andVisitor.getChildren().first()->accept(*this); // il y a toujours 1 fils ou plus (check fait en amont)
	for(int i = 1; i < andVisitor.getChildren().size() ; i++){
		 	result *= andVisitor.getChildren().at(i)->accept(*this);
	}
	
	return result;
}

double EvalVisitor::visit(Or&  orVisitor){
	double result = 0;
	for(int i = 0; i < orVisitor.getChildren().size() ; i++){

			result += orVisitor.getChildren().at(i)->accept(*this);
		}
	return result;
}

double EvalVisitor::visit(Xor&  xorVisitor){

   double result = ( xorVisitor.getChildren().at(0)->accept(*this) * (1 - xorVisitor.getChildren().at(1)->accept(*this)) ) + ( (1 - xorVisitor.getChildren().at(0)->accept(*this)) * xorVisitor.getChildren().at(1)->accept(*this) ) ;
   return result;
}

double EvalVisitor::visit(Inhibit& inVisitor){
	double result = 0;
	if(inVisitor.getCondition()){
		 result = inVisitor.getChildren().at(0)->accept(*this);
	}
	return result;
	
}

double EvalVisitor::visit(Transfert& transVisitor){
	
	return transVisitor.getLink()->getTop()->accept(*this);
	
}

double EvalVisitor::visit(VotingOR& vorVisitor){
	
	 return vorVisitor.getSubTree()->accept(*this);
}

double EvalVisitor::visit(Container& eventVisitor){
	
	 return eventVisitor.getEvent()->getDistribution()->getProbability(time);
}
