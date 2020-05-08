#include <QMap>
#include <math.h>
#include <iostream>
#include "ResultMCS.hh"
using namespace std;
#define LIMIT	(100000)

/*Constructeur*/
ResultMCS::ResultMCS(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step){
    QList<Container*> containers;//mettre dedans des containers alloues dynamiques
    QList<QList<Node*>> cs;
    QList<QList<Event>> mcs;
    cs = {{top}};/*cs contient tous les coupe*/
    computeCS(cs, containers);
    convertCS(cs, mcs);
    reduceCS(mcs);

    for(int i=0; i<mcs.size(); i++){//recuperer les noms de chaque event
        mcsNames.append(QList<QString>());
        for(int j=0; j<mcs[i].size();j++){
            mcsNames[i].append(mcs[i][j].getProperties().getName());
        }
    }

    for(int i=0; i<mcsNames.size(); i++){//montrer les resultat
        for(int j=0; j<mcsNames[i].size();j++){
            qDebug()<<"("<<i<<", "<<j<<"): "<<mcsNames[i][j];
        }
    }

    for(int i=0;i<containers.size();i++){//librer les memoire dynamique
        delete containers[i]->getEvent()->getDistribution();
        delete containers[i]->getEvent();
        delete containers[i];
    }

}
/*Deconstructeur*/
ResultMCS::~ResultMCS(){}



void ResultMCS::computeCS(QList<QList<Node*>>& cs, QList<Container*>& containers){// trouver tous les coupes
    CutVisitor visitor(cs, containers);

	for(int i=0; i<cs.size(); i++){
		for(int j=0; j<cs[i].size();j++){

            if(!dynamic_cast<Container*>(cs[i][j])){/*si c'est pas un Event de base, si c'est un event de base, pass directement*/
                visitor.setIndex(i,j);//donner visitor l'index courant.
                cs[i][j]->accept(visitor);//recuperer les enfants et les mettre dans le matrice selon le type de la porte
                                            // les facons d'ajouter sont deja definis dans visitor.

                computeCS(cs, containers);/*recursif*/
			}
		}
    }
}

void ResultMCS::convertCS(QList<QList<Node*>>& cs, QList<QList<Event>>& mcs){/*Convertit la liste de liste de Node en liste de liste d'évènements*/
    for(int i=0; i<cs.size(); i++){
		mcs.append(QList<Event>());
		for(int j=0; j<cs[i].size();j++){
            Container *c = (Container*)cs[i][j];
            mcs[i].append(*c->getEvent());
		}// (utilise le dynamic cast)
    }
}

void ResultMCS::reduceCS(QList<QList<Event>>& mcs){/*enlever les doublons et reduire */
	QList<int> premiers;
	QList<Event> lstEvent;/*contient tous les events non-doublons dans cet arbre*/
	QMap<Event, int> mapEvent;/*lier chaque event avec un nombre premier*/
	QMap<int, int> mapMul;/*Key est l'index dechaque coupe dans mcs, valeur est resultatMul de chaque coupe correspondant*/
	int mul;/*y mettre le mul de premier dans chaque coupe*/

    sortCut(mcs);/*enlever les doublons dans les coupes */

	for(int i=0; i<mcs.size(); i++){/*trouver tous les events non-doublons dans cet arbre*/
		for(int j=0; j<mcs[i].size();j++){
			if(!lstEvent.contains(mcs[i][j])){
				lstEvent.append(mcs[i][j]);
			}
		}
	}

	premiers=sieveOfAtkin(LIMIT);
	for(int i=0; i<lstEvent.size(); i++){/*assigner chaque event un nombre premier*/
		mapEvent[lstEvent[i]] = premiers[i];
	}

	for(int i=0; i<mcs.size(); i++){
		mul=1;
		for(int j=0; j<mcs[i].size();j++){
			mul *= mapEvent[mcs[i][j]];
		}
		mapMul[i]=mul;
	}

    int tempIndexs[mcs.size()];/*mets les indexs de chaque coupe*/
    int tempMuls[mcs.size()];/*mets les muls de chaque coupe*/
    int temp;//temporaire
    for(int i=0; i<mcs.size(); i++){//on ne peut pas modifier map parce que le key est le meme index que l'index de coupe dans le matrice
                                         // du coup on creer deux tableaus pour mettre l'index et mul qui peuvent etre modifier
        tempIndexs[i] = i;
        tempMuls[i] = mapMul[i];
    }

	for(int j=mcs.size(); j>=1; j--){/*sort croissant*/
		for(int i=0;i<j-1;i++){
            if(tempMuls[i] > tempMuls[i+1]){/*mettre l'index du plus grand à la fin*/
                temp = tempIndexs[i];
                tempIndexs[i] = tempIndexs[i+1];
                tempIndexs[i+1]=temp;

                temp = tempMuls[i];
                tempMuls[i] =tempMuls[i+1];
                tempMuls[i+1] = temp;
            }
		}
	}


	for(int i=0; i<mcs.size();i++){
		for(int j=i+1; j<mcs.size();j++){
            if(mapMul[tempIndexs[j]]%mapMul[tempIndexs[i]]==0){ /*MULde mcs[j] mod MULmcs[i] ==0*/
                mcs[tempIndexs[j]].clear();/*empty la coupe qui a mul plus grand*/
            }
		}
	}
	for(int i=mcs.size()-1; i>-1;i--){/*supprimer la coupe qui est vide*/
		if(mcs[i].isEmpty()){
			mcs.takeAt(i);
		}
	}

}



void ResultMCS::sortCut(QList<QList<Event>>& mcs){/*enlever les doublons dans les coupes */

	for(int i=0; i<mcs.size(); i++){/*enlever les doublons dans les coupes */

	// mcs[i].toSet().toList();
		for(int j=0; j<mcs[i].size();j++){
			for(int k=mcs[i].size()-1; k>j;k--){
				if(mcs[i][k] == mcs[i][j]){
					mcs[i].removeAt(k);
				}
			}
		}
	}
}

QList<int> ResultMCS::sieveOfAtkin(int limit){/*Génère un nombre de nombres premiers selon le nombre limite n.*/
	(void)limit;
    QList<int> premiers;
        bool sieve_list[limit + 1];
        int n, x, y, k, i;

        for(n = 5; n <= limit; n++){ /* is_prime(i) ← false, ∀ i ∈ [5, limit] */
            sieve_list[n] = false;
        }
        for(x = 1; x <= (int)sqrt(limit); x++){ /* for (x, y) in [1, √limit] × [1, √limit]: */
            for(y = 1; y <= (int)sqrt(limit); y++){

                n = 4 * x * x + y * y;/*n ← 4x²+y²:if (n ≤ limit) and (n mod 12 = 1 or n mod 12 = 5):is_prime(n) ← ¬is_prime(n)*/
                if(n <= limit && (n % 12 == 1 || n % 12 == 5)){
                    sieve_list[n] = !sieve_list[n];
                }
                n = 3 * x * x + y * y; /*n ← 3x²+y²:if (n ≤ limit) and (n mod 12 = 7):is_prime(n) ← ¬is_prime(n)*/
                if(n <= limit && n % 12 == 7){
                    sieve_list[n] = !sieve_list[n];
                }
                n = 3 * x * x - y * y;/*n ← 3x²-y²:if (x > y) and (n ≤ limit) and (n mod 12 = 11):is_prime(n) ← ¬is_prime(n)*/
                if(x > y && n <= limit && n % 12 == 11){
                    sieve_list[n] = !sieve_list[n];
                }
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
            if(sieve_list[n] == true){
                premiers<<n;
            }
        }
        return premiers;
}


QList<QList<QString>> ResultMCS::getMCS(){//rentrer les noms des events
    return mcsNames;
}

QList<double> ResultMCS::getProbabilities(){
    return probabilities;
}
