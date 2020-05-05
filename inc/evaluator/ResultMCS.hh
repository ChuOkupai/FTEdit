#pragma once
#include "Evaluator.hh"
#include "CutVisitor.hh"
#include "Event.hh"

class ResultMCS : public Evaluator
{
	private : 
        QList<QList<QString>> mcsNames;//mettre dedans les noms des events
        QList<double> mcsProbas;

		QList<int> sieveOfAtkin(int n);
        void computeCS(QList<QList<Node*>>& cs, QList<Container*>& containers);
        void reduceCS(QList<QList<Event>>& mcs);
        void sortCut(QList<QList<Event>>& mcs);
        void convertCS(QList<QList<Node*>>& cs, QList<QList<Event>>& mcs);


	public :

	ResultMCS(Gate* top, double missionTime, double step);
	~ResultMCS();
    QList<QList<QString>> getMCS();
	QList<double> getProbabilities();

};
