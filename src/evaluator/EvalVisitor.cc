#include "EvalVisitor.hh"


using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}

EvalVisitor::EvalVisitor(){}
/*
void EvalVisitor::visit(And& andVisitor){
    for(int i = 0; i < andVisitor.getChildren().size() ; i++){
        if( instanceof<Gate>(andVisitor.getChildren().at(i)) ){
            this->visit(andVisitor.getChildren().at(i));
        }else if(instanceof<Container>(andVisitor.getChildren().at(i))){
            andVisitor.getChildren().at(i)->getProbability(0); //TODO
        }else{
            this->visit(andVisitor.getChildren().at(i));
        }
    }
}

void EvalVisitor::visit(Or&  orVisitor){
    for(int i = 0; i < orVisitor.getChildren().size() ; i++){
        if( instanceof<Gate>(orVisitor.getChildren().at(i)) ){
            this->visit(orVisitor.getChildren().at(i));
        }else if(instanceof<Container>(orVisitor.getChildren().at(i))){
            orVisitor.getChildren().at(i)->getProbability(0); //TODO
        }else{
            this->visit(orVisitor.getChildren().at(i));
        }
    }
}

void EvalVisitor::visit(Inhibit& inVisitor){

}

void visit(Transfert& transVisitor){
    
}

void visit(Container& eventVisitor){
    eventVisitor.getProbability(0);

}
*/