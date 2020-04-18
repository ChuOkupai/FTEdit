#include <cmath>
#include "Exponential.hh"


Exponential::Exponential(QString name) : Distribution(name) {}

double Exponential::getLambda() const { return value; }

void Exponential::setLambda(double lambda) { value = lambda; }

double Exponential::getProbability(double time) { return 1 - exp(-value*time); }
