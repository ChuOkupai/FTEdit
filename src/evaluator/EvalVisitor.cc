#include "EvalVisitor.hh"


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
    this->proba = andVisitor.getChildren()->at(i)->accept(this);
    for(int i = 1; i < andVisitor.getChildren()->size() ; i++){
         this->proba = this->proba * andVisitor.getChildren()->at(i)->accept(this);
        
    }
}

double EvalVisitor::visit(Or&  orVisitor){
    for(int i = 0; i < orVisitor.getChildren()->size() ; i++){
       
            this->proba = this->proba + orVisitor.getChildren()->at(i)->accept(this);
        }
}

double EvalVisitor::visit(Inhibit& inVisitor){
    if(inVisitor.getCondition()){
        this->proba = this->proba + inVisitor.getChildren()->at(0)->accept(this);
    }

}

double EvalVisitor::visit(Transfert& transVisitor){
   transVisitor.getLink()->getTop()->accept(this);

}

double EvalVisitor::visit(VotingOr& vorVisitor){
    vorVisitor.getSubTree()->accept(this);
}

double EvalVisitor::visit(Container& eventVisitor){
   this->proba = eventVisitor.getEvent()->getDistribution(time);

}
