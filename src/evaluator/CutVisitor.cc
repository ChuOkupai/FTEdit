#include "CutVisitor.hh"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return is_base_of<Base, T>::value;
}


CutVisitor::CutVisitor(QList<QList<Node*>>& cutset) : cutset(cutset){//：后括号初始化赋值，ex:a(10),对于对象、引用、常量的赋值必须在引入函数前就进行初始化，之后不能再改变
}
CutVisitor::~CutVisitor(){}


void CutVisitor::setIndex(int i, int j){
    this->i = i;
    this->j = j;
}


void CutVisitor::visit(And& andgate){/*si c'est une Porte AND*/
    visitGate(andgate);//Debug

    QList<Node*>& childrens=andgate.getChildren();/*recuperer les fils de cette porte*/
    cutset[i][j] = childrens.at(0);
    for(int m=1; m<childrens.size();m++){
        cutset[i].append(childrens[m]);
    }
}

void CutVisitor::visit(Or& orgate){
    visitGate(orgate);

    QList<Node*> *lstcopy; /*un pointer pointe les nouvelle liste vide*/
    QList<Node*>& childrens=orgate.getChildren();

    cutset[i][j] = childrens.at(0);/*remplacer cette porte de son premier fils*/
    for(int m=1; m<childrens.size();m++){/*parcourir les enfants*/
        lstcopy = new QList<Node*>;/*faire le pointer pointe une autre nouvelle liste vide*/

        for(int n=0; n<cutset[i].size();n++){/*copier une nouvelle liste avec le meme contenu*/
            lstcopy->append(cutset[i][n]);
        }

        lstcopy->replace(j,childrens.at(m));/*mettre les autres fils dans la meme position de leurs liste*/
        cutset.append(*lstcopy); /*mettre cette nouvelle liste a la fin de cs*/
    }
}


void CutVisitor::visit(Xor& xorgate){
    QList<Node*> lstcopy; // pour mettre la copie de la liste.

    visitGate(xorgate);

    cutset[i][j] = xorgate.getChildren().at(0);/*remplacer cette porte de son premier fils*/
    for(int n=0; n<cutset[i].size();n++){/*copier une nouvelle liste avec le meme contenu*/
        lstcopy.append(cutset[i][n]);
    }
    /*remplacer cette porte de son deuxieme fils dans la copie*/
    lstcopy[j]=xorgate.getChildren().at(1);// Xor n'a que 2 enfants.
    cutset.append(lstcopy);/*ajoute la copie dans le matrice*/

}

void CutVisitor::visit(VotingOR& vorgate){
        visitGate(vorgate);
        Gate* vor = vorgate.getSubTree();
        cutset[i][j] = vor;
    }

void CutVisitor::visit(Inhibit& inhibgate){
    visitGate(inhibgate);

//    QList<Container> containers;
    Event cond("conditon " + inhibgate.getProperties().getName());
    Constant proba("proba " + inhibgate.getProperties().getName());

    if(inhibgate.getCondition()){
        proba.setValue(1);
    }else{
        proba.setValue(0);
    }
    cond.setDistribution(&proba);
    Container condition(&cond);

    cutset[i][j] = inhibgate.getChildren().at(0);/*ajouter le fils de inhibit*/
    cutset[i].append(&condition);/*ajouter sa condition*/

    }

void CutVisitor::visit(Transfert& transfertgate)
    {
        cutset[i][j] = transfertgate.getLink()->getTop();
    }

void CutVisitor::visit(Container& container)
    {
        qDebug() << "C'est un event de base: " << container.getEvent()->getProperties().getName();
    }
