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

double EvalVisitor::getProba(){
	return proba;
}

void EvalVisitor::setTime(double time){
	this->time = time;
}

void EvalVisitor::reset(){
	this->proba = 0;
}

double EvalVisitor::visit(And& andVisitor){


	for(int i = 1; i < andVisitor.getChildren().size() ; i++){
		if(this->proba ==0){
			proba = andVisitor.getChildren().at(i)->accept(*this);

		}else{
		 proba = proba * andVisitor.getChildren().at(i)->accept(*this);
		}
	}
	return proba;//to remove compiling warning
}

double EvalVisitor::visit(Or&  orVisitor){

	for(int i = 0; i < orVisitor.getChildren().size() ; i++){

			 proba += orVisitor.getChildren().at(i)->accept(*this);
		}
	return proba;//to remove compiling warning
}

double EvalVisitor::visit(Inhibit& inVisitor){
	inVisitor.getParent();
	if(inVisitor.getCondition()){
		 proba += inVisitor.getChildren().at(0)->accept(*this);
	}
	return proba;//to remove compiling warning
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

double EvalVisitor::visit(Xor& xorVisitor){
	return xorVisitor.getChildren().at(0)->accept(*this);
	return xorVisitor.getChildren().at(1)->accept(*this);
}
