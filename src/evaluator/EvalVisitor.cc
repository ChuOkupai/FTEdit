#include "EvalVisitor.hh"

/***
 *  ATTENTION NE PAS FAIRE ATTENTION AU CODE "RETURN 0" OU "GETPARENTS" LE VRAI CODE SE TROUVE ACTUELLEMENT ENTRE COMMENTAIRE
 * EN ATTENTE DE L'IMPLEMENTATION DES METHODES ACCEPT POUR LE EVALVISITOR DANS LE MODULE EDITEUR
 *
 *
 * ***/

//les méthodes visit() ne sont plus commentés. Elles furent légèrement modifiés pour pouvoir compiler.  

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return is_base_of<Base, T>::value;
}

EvalVisitor::EvalVisitor(double time,double proba){
	this->time = time;
	this->proba = proba;
}

double EvalVisitor::getProba(Gate *top,double time){
	this->time = time;
	return top->accept(*this);
}

void EvalVisitor::setTime(double time){
	this->time = time;
}

void EvalVisitor::reset(){
	this->proba = 0;
}

double EvalVisitor::visit(And& andVisitor){
	
	
	for(int i = 0; i < andVisitor.getChildren().size() ; i++){
		if(this->proba ==0){
			this->proba = andVisitor.getChildren().at(i)->accept(*this);

		}else{
		 this->proba = this->proba * andVisitor.getChildren().at(i)->accept(*this);
		}
	}
	
	return this->proba;
}

double EvalVisitor::visit(Or&  orVisitor){

	for(int i = 0; i < orVisitor.getChildren().size() ; i++){

			this->proba = this->proba + orVisitor.getChildren().at(i)->accept(*this);
		}
	return this->proba;
}

double EvalVisitor::visit(Xor&  xorVisitor){

   this->proba = ( xorVisitor.getChildren().at(0)->accept(*this) * (1 - xorVisitor.getChildren().at(1)->accept(*this)) ) + ( (1 - xorVisitor.getChildren().at(0)->accept(*this)) * xorVisitor.getChildren().at(1)->accept(*this) ) ;
   return this->proba;
}

double EvalVisitor::visit(Inhibit& inVisitor){
	
	if(inVisitor.getCondition()){
		 this->proba = this->proba + inVisitor.getChildren().at(0)->accept(*this);
	}
	return this->proba;
	
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
