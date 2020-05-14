#pragma once
#include "Evaluator.hh"
#include "CutVisitor.hh"
#include "Event.hh"

class ResultMCS : public Evaluator
{
	private : 
        QList<QList<QString>> mcsNames;//mettre dedans les noms des events

		QList<int> sieveOfAtkin(int n);
        void computeCS(QList<QList<Node*>>& cs, QList<Container*>& containers);
        void reduceCS(QList<QList<Event>>& mcs);
        void sortCut(QList<QList<Event>>& mcs);
        void convertCS(QList<QList<Node*>>& cs, QList<QList<Event>>& mcs);
        void combo(int n,int k,int a[],QList<QList<int>>& comb,int m);/*calculer les compositions des coupes minimales*/


	public :

	ResultMCS(Gate* top, double missionTime, double step);
	virtual ~ResultMCS();
    QList<QList<QString>> getMCS();
    QList<double> getProbabilities();/*probabilities[0] = proba de top*/

};
