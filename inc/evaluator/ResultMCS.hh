#pragma once
#include "Evaluator.hh"
#include "Event.hh"

class ResultMCS : public Evaluator
{
	private : 
		QList<QList<Event>> mcs;
		void computeCS();
		void reduceCS();
		void sortCut();
		void sieveOfAtkin(int n);


	public :

	ResultMCS(Gate* top, double missionTime, double step);
	~ResultMCS();
    void convertCS(QList<QList<Node*>> cs);
	QList<QList<Event>> getMCS();
	QList<double> getProbabilities();

};
