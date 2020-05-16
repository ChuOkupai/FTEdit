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

    /*qualitative*/

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


    /*quantitative*//*probabilities[0] = proba de top*/

    double probaCoupe;
    for(int i=0; i<mcs.size(); i++){/*Calculer le proba de chaque coupe minimale */
        probaCoupe = 1;
        for(int j=0; j<mcs[i].size();j++){
            probaCoupe *= mcs[i][j].getDistribution()->getProbability(missionTime);
        }
        probabilities << probaCoupe;
    }

        /*calculer le proba de top event, parce que les coupes minimales ne sont pas indépendantes,
         * Donc il faut utiliser le Principe d'inclusion-exclusion, mettre le xx = x;*/

    double p=0;/*proba de top*/
    int klimit;/*limiter le nombre de s*/
    int n = probabilities.size();
    if(n<5){
        klimit = n+1;
    }else{
        klimit = 5;/*on calcule que S1-S4, les suivants sont trop petit et influence pas trop le resultat, donc n'a pas de sens a calculer
                    *sinon il doit calculer trop quand le nombre de coupes minimales est grand, pas la peine.*/
    }
    for(int i=1; i<klimit;i++){/**/
        double s=0;

        if(i==1){
            for(int j=0; j<n;j++){
                s += probabilities[j];
            }
        }
        else{/*i=1->klimit: p=∑(-1)^(i-1)Si; j=i/n -> Si=∏Mj*/
            QList<QList<int>> comb={};
            int a[i];
            combo(n,i,a,comb,0);/*trouver les compositions*/

            for(int j=0;j<comb.size();j++){
                QList<Event> l={};/*soit m1={e1,e2},m2={e1,e3}, donc P(m1m2)=p(e1e2e1e3)=p(e1e2e3)*/
                for(int m=0;m<i;m++){
                    QList<Event>& temp = mcs[comb[j][m]-1];/*l'index de coupe minimale commence de 0*/
                    for(int k=0; k<temp.size();k++){
                        if(!l.contains(temp[k])){/*ee=e -> p(e1e2e1e3)=p(e1e2e3)*/
                            l.append(temp[k]);
                        }
                    }
                }
                double mul=l[0].getDistribution()->getProbability(missionTime);
                for(int k=1; k<l.size();k++){
                    mul *= l[k].getDistribution()->getProbability(missionTime);/*p(e1e2e3)*/
                }
                s += mul;
            }
        }

        if(i%2==0){/*p=s1-s2+s3-0.5s4*/
            if(i==klimit-1 && mcs.size()>4){/*quand on a trop de coupes minimales >4, on prend que S1,S2,S3 et moitie de S4
                                               *pour obtenir un resultat approché*/
                p -= s/2;
            }
            p -= s;
        }
        else{
            if(i==klimit-1 && mcs.size()>4){
                p += s/2;
            }
            p += s;/*proba de top*/
        }

    }
    probabilities << p;/*probabilities.last() = proba de top*/


    /*tester*/
    QList<double> probas = probabilities;

    for(int i=0; i < probas.size();i++){
        qDebug()<< probas[i];
    }






    /*librer les memoire dynamique*/

    for(int i=0;i<containers.size();i++){
        delete containers[i]->getEvent()->getDistribution();
        delete containers[i]->getEvent();
        delete containers[i];
    }

}
/*Deconstructeur*/
ResultMCS::~ResultMCS(){}


void ResultMCS::combo(int n,int k,int a[],QList<QList<int>>& comb,int m){/*calculer les compositions des coupes minimales*/

    //当k==0的时候，将数组里面的三个数依次输出
    if( k == 0 ){
        QList<int>* lst = new QList<int>;
        for(int j= 0; j < m; ++j)
            *lst<<a[j];
        comb.append(*lst);
    }

    else
    {
        for(int i = n; i >= k; --i )
        {
            a[m] = i;
            combo(i-1,k-1,a,comb,m+1);
        }
    }
}

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

    sortCut(mcs);/*enlever les doublons dans les coupes et sort croissant les coupes par size de coupe*/

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



void ResultMCS::sortCut(QList<QList<Event>>& mcs){/*enlever les doublons dans les coupes et sort croissant les coupes par size de coupe*/

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
    
    QList<Event> temp;
    for(int j=mcs.size(); j>=1; j--){/*sort croissant les coupes par size de coupe*/
        for(int i=0;i<j-1;i++){
            if(mcs[i].size()>mcs[i+1].size()){
                temp = mcs[i];
                mcs[i] = mcs[i+1];
                mcs[i+1] = temp;
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

