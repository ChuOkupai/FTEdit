
#include "ResultMCS.hh"
#include <math.h>
#include <iostream>
#include <QMap>
#include <vector>
using namespace std;
#define LIMIT	(100000)

template<typename Base, typename T> /*verifier le type d'un objet*/
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}


ResultMCS::ResultMCS(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step){
    cs = {{top}};/*cs contient tous les coupe*/
}

ResultMCS::~ResultMCS(){}

//void ResultMCS::computeCS(){/*trouver tous les coupes*/

//    QList<Node*> *lstcopy;/*un pointer pointe les nouvelle liste vide*/

//    for(int i=0; i<cs.size(); i++){
//        for(int j=0; j<cs[i].size();j++){

//            if(instanceof<Gate>(cs[i][j])){/*si c'est une Porte*/
//                QList<Node*>* childrens = cs[i][j]->getChildren();/*recuperer les fils de cette porte*/

//                if(instanceof<And>(cs[i][j])){/*si c'est une Porte AND*/
//                    cs[i][j] = childrens->at(0);
//                    for(int m=1; m<childrens->size();m++){
//                        cs[i].append(childrens[m]);
//                    }
//                }
//                else if(instanceof<Or>(cs[i][j])){/*si c'est une Porte OR*/
//                    cs[i][j] = childrens->at(0);/*remplacer cette porte de son premier fils*/
//                    for(int m=1; m<childrens->size();m++){/*parcourir les enfants*/
//                        lstcopy = new QList<Node*>;/*faire le pointer pointe une autre nouvelle liste vide*/

//                        for(int n=0; n<cs[i].size();n++){/*copier une nouvelle liste avec le meme contenu*/
//                            lstcopy->append(cs[i][n]);
//                        }

//                        lstcopy->replace(j,childrens->at(m));/*mettre les autres fils dans la meme position de leurs liste*/
//                        cs.append(*lstcopy); /*mettre cette nouvelle liste a la fin de cs*/

//                    }
//                }

//                computeCS();/*recursif*/
//            }

//        }
//    }
//}

//void ResultMCS::convertCS(){/*Convertit la liste de liste de Node en liste de liste d'évènements*/
//    for(int i=0; i<cs.size(); i++){
//        mcs.append(QList<Event>());
//        for(int j=0; j<cs[i].size();j++){
//            mcs[i].append(*cs[i][j]->getEvent());
//        }
//    }
//}

//void ResultMCS::reduceCS(){/*enlever les doublons et reduire */
//    QList<int> premiers;
//    QList<Event> lstEvent;/*contient tous les events non-doublons dans cet arbre*/
//    QMap<Event, int> mapEvent;/*lier chaque event avec un nombre premier*/
//    QMap<QList<Event>, int> mapMul;/*Key est chaque coupe dans mcs, valeur est resultatMul de chaque coupe correspondant*/
//    int mul;/*y mettre le mul de premier dans chaque coupe*/

//    for(int i=0; i<mcs.size(); i++){/*enlever les doublons dans les coupes */
//        mcs[i].toSet().toList();
//    }

//    for(int i=0; i<mcs.size(); i++){/*trouver tous les events non-doublons dans cet arbre*/
//        for(int j=0; j<mcs[i].size();j++){
//            if(!lstEvent.contains(mcs[i][j])){
//                lstEvent.append(mcs[i][j]);
//            }
//        }
//    }

//    premiers=sieveOfAtkin(LIMIT);
//    for(int i=0; i<lstEvent.size(); i++){/*assigner chaque event un nombre premier*/
//        mapEvent[lstEvent[i]] = premiers[i];
//    }

//    for(int i=0; i<mcs.size(); i++){
//        mul=1;
//        for(int j=0; j<mcs[i].size();j++){
//            mul *= mapEvent[mcs[i][j]];
//        }
//        mapMul[mcs[i]]=mul;
//    }

//    sortCut(mapMul);

//    for(int i=0; i<mcs.size();i++){
//        for(int j=i+1; j<mcs.size();j++){
//            if(!mapMul[mcs[j]]%mapMul[mcs[i]]){ /*mcs[j] mod mcs[i] ==0*/
//                mcs[j].clear();/*supprimer la coupe qui a mul plus grand*/
//            }
//        }
//    }
//    for(int i=0; i<mcs.size();i++){
//        if(mcs[i].isEmpty()){
//            mcs.takeAt(i);
//            i--;
//        }
//    }

//}


/*Trie les coupes en triant par ordre croissant selon l'assignation des nombres premiers */
//void ResultMCS::sortCut(QMap<QList<Event>, int> mapMul){
//    QList<Event> temp;

//    for(int j=mcs.size(); j>=1; j--){/*sort croissant*/
//        for(int i=0;i<j-1;i++){
//            if(mapMul[mcs[i]] > mapMul[mcs[i+1]]){/*mettre le plus grand à la fin*/
//                temp = mcs[i];
//                mcs[i] = mcs[i+1];
//                mcs[i+1] = temp;
//            }
//        }
//    }



//}

QList<int> ResultMCS::sieveOfAtkin(int limit){/*Génère un nombre de nombres premiers selon le nombre limite n.*/
    QList<int> premiers;
    bool sieve_list[limit + 1];
    int n, x, y, k, i;

    /* is_prime(i) ← false, ∀ i ∈ [5, limit] */
    for(n = 5; n <= limit; n++){
        sieve_list[n] = false;
    }

    /* for (x, y) in [1, √limit] × [1, √limit]: */
    for(x = 1; x <= (int)sqrt(limit); x++){
        for(y = 1; y <= (int)sqrt(limit); y++){
            /*n ← 4x²+y²:if (n ≤ limit) and (n mod 12 = 1 or n mod 12 = 5):is_prime(n) ← ¬is_prime(n)*/
            n = 4 * x * x + y * y;
            if(n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve_list[n] = ~sieve_list[n];
            /*n ← 3x²+y²:if (n ≤ limit) and (n mod 12 = 7):is_prime(n) ← ¬is_prime(n)*/
            n = 3 * x * x + y * y;
            if(n <= limit && n % 12 == 7)
                sieve_list[n] = ~sieve_list[n];
            /*n ← 3x²-y²:if (x > y) and (n ≤ limit) and (n mod 12 = 11):is_prime(n) ← ¬is_prime(n)*/
            n = 3 * x * x - y * y;
            if(x > y && n <= limit && n % 12 == 11)
                sieve_list[n] = ~sieve_list[n];
        }
    }

    /*for n in [5, √limit]: if is_prime(n):is_prime(k) ← false, k ∈ {n², 2n², 3n², ..., limit}*/
    for(n = 5; n <= sqrt(limit); n++){
        if(sieve_list[n] == true){
            i = 1;
            k = i++ * n * n;
            while(k <= limit){
                sieve_list[k] = false;
                k = i++ * n * n;
            }
        }
    }
    premiers<<2<<3;/* append 2, 3 */
    for(n = 5; n <= limit; n++){ /* append les premiers suivants*/
        if(sieve_list[n] == true)
            premiers<<n;
    }

    return premiers;
}


QList<QList<Event>> ResultMCS::getMCS(){
//    computeCS();
//    convertCS();
//    reduceCS();
    return mcs;
}
QList<double> ResultMCS::getProbabilities(){
    QList<double> tab;
    return tab;

}
