
#include <vector>
#include "Capacitor.h"
#include "CapacitorList.h"
using namespace std;


#ifndef CAPFUNCTIONS_H
#define CAPFUNCTIONS_H

long double totalParallelCapacitance(const CapacitorList capacitors);
long double totalSeriesCapacitance(const CapacitorList capacitors);
int totalQuantity(const CapacitorList capacitors);

CapacitorList parallelCapacitanceAprox(CapacitorList capacitors, const long double goal);
CapacitorList greedyParallelCapacitanceAprox(CapacitorList capacitors, const long double goal);

CapacitorList seriesCapacitanceAprox(CapacitorList capacitors, const long double goal);
//do not make a greedy series, it would never be efficient

//make a pure optimal algorithm that mixes parallel and series (Future)

//make a non Parallel or Series approach (Future)
#endif

