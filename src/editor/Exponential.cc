#include <cmath>
#include "Exponential.hh"


Exponential::Exponential(QString name) : Distribution(name) {}

const double Exponential::getLambda() { return value; }

void Exponential::setLambda(double lambda) { value = lambda; }

double Exponential::getProbability(double time) { return 1 - exp(-value*time); }
