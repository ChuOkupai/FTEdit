#include "EvalVisitor.hh"


using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return is_base_of<Base, T>::value;
}

EvalVisitor::EvalVisitor(double time){
	this->time = time;
	
}

double EvalVisitor::getProba(Gate *top,double time){
	this->time = time;
	return top->accept(*this);
}

void EvalVisitor::setTime(double time){
	this->time = time;
}


double EvalVisitor::visit(And& andVisitor){
	double result = 0;
	
	for(int i = 0; i < andVisitor.getChildren().size() ; i++){
		if(result == 0 ){
			result = andVisitor.getChildren().at(i)->accept(*this);

		}else{
		 	result *= andVisitor.getChildren().at(i)->accept(*this);
		}
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
		 result += inVisitor.getChildren().at(0)->accept(*this);
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
