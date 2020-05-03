#pragma once
#include "Evaluator.hh"
#include "Event.hh"

class ResultMCS : public Evaluator
{
	private : 
		QList<QList<Event>> mcs;
		QList<QList<Node*>> cs;

		QList<int> sieveOfAtkin(int n);
		void computeCS();
		void reduceCS();
		void sortCut();
		void convertCS();


	public :

	ResultMCS(Gate* top, double missionTime, double step);
	~ResultMCS();
	QList<QList<Event>> getMCS();
	QList<double> getProbabilities();

};
