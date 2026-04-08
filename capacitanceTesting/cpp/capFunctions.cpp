#include "capFunctions.h"
#include "CapacitorList.h"
#include <vector>

//Used for conserving long double precision
static const long double EPS = 1e-12L;


//returns a CapacitorList of the capacitors used, and their quantities. It tries to minimize capacitors used while approaching goal capacitance, but it does not guarantee the optimal solution
CapacitorList parallelCapacitanceAprox(const CapacitorList capacitors, const long double goal) {
    vector<CapacitorList> tempList;
    
    long double totalCapacitance;
    long double capCapacitance;

    int totalQuantity;
    int capQuantity;
    int capsAvailable;

    // capacitors should alreadby be in descending order of capacitance, before continuing
    // capacitors.descendingSort();

    for (int outer = 0; outer < capacitors.getListSize(); outer++) {
        CapacitorList used;
        totalCapacitance = 0;
        totalQuantity = 0;

        //try to use the largest capacitors first (outer), and keep adding them until we reach the goal capacitance or exceed it
        for (int i = outer; i < capacitors.getListSize(); i++) {
            capCapacitance = (capacitors.getCapacitor(i)).getCapacitance();  
        
        // Quick exits
            //if the current capacitor is greater than the goal capacitance, we can move on the next iteration
            if (capCapacitance > goal) continue;
            //if we already found a good solution, and if the current capacitor capicitance would require an more quantity than the best solution so far, we can skip it
            if (!tempList.empty() && tempList[tempList.size()-1].getTotalCapacitance() == goal  && 
            (totalQuantity + (goal - totalCapacitance) / capCapacitance) > tempList[tempList.size()-1].getTotalQuantity() ) break;            

            capsAvailable = (capacitors.getCapacitor(i)).getQuantity();
            capQuantity = 0;

            //while we can still add the current capacitor without exceeding the goal capacitance, and we have more of that capacitor to use, add it to the total capacitance and decrement the quantity of that capacitor
            while ( (totalCapacitance + capCapacitance <= goal + EPS) && (capQuantity < capsAvailable) ) {
                totalCapacitance += capCapacitance;
                capQuantity++;
            }

            //if we needed at least one of the current capacitor, push cap into temp vector
            if (capQuantity > 0) {
                used.pushCapacitor(Capacitor(capQuantity, capCapacitance));
            }
        }

        //now if we have found a solution
        if (!used.empty()) {
            //set order for the new solution
            used.setOrder("parallel");
            used.setTotalCapacitance(totalCapacitance);
            
            //if we already have a previous solution, then check if the new solution is better
            if (!tempList.empty() && (abs(totalCapacitance - goal) < abs(tempList[tempList.size() -1 ].getTotalCapacitance() - goal))) {
                //push better solution to the end, avoid shifting
                tempList.push_back(used);
            }
            //if we dont have a previous solution, then add this one
            else if (tempList.empty()) {
                tempList.push_back(used);
            }
        } 
        
    }
    
    //returns most efficient solution found (at end of tempList), or empty list if no solution found
    return tempList.empty() ? CapacitorList() : tempList[tempList.size() - 1];
}



// Fastest method, worst accuracy, only adds largest capacitors until we reach the goal capacitance, does not backtrack 
// capacitors must already be in descending order of capacitance
CapacitorList greedyParallelCapacitanceAprox(const CapacitorList capacitors, const long double goal) {
    CapacitorList used;

    long double totalCapacitance = 0.0L;
    long double capCapacitance;

    int capQuantity;
    int capsAvailable;

    //this is used to compare floating point numbers,
    const long double EPS = 1e-12L;

    // Single greedy pass: start with largest capacitors and add as many as possible without exceeding goal
    for (int i = 0; i < capacitors.getListSize(); i++) {
            capCapacitance = (capacitors.getCapacitor(i)).getCapacitance();  
        
            // Quick exit
            //if the current capacitor is greater than the goal capacitance, we can move on the next iteration
            if (capCapacitance > goal) continue;

            capsAvailable = (capacitors.getCapacitor(i)).getQuantity();
            capQuantity = 0;
            //while we can still add the current capacitor without exceeding the goal capacitance, and we have more of that capacitor to use, add it to the total capacitance and decrement the quantity of that capacitor
            while ( (totalCapacitance + capCapacitance <= goal + EPS) && (capQuantity < capsAvailable) ) {
                totalCapacitance += capCapacitance;
                capQuantity++;
            }

            //if we needed at least one of the current capacitor, push cap into temp vector
            if (capQuantity > 0) {
                used.pushCapacitor(Capacitor(capQuantity, capCapacitance));
            }
    }

    // Set properties and return
    used.setOrder("parallel");
    used.setTotalCapacitance(totalCapacitance);
    return used;
}





// finds needed capacitors for series, and returns a CapacitorList of the capacitors required, while trying to best approach the goal capacitance.
// CapacitorList capacitors should already be in descending order of capacitance
// This is a linear series (no parallel mix)
CapacitorList seriesCapacitanceAprox(const CapacitorList capacitors, const long double goal) {
    const long double inverseGoal = 1.0L/ (goal - EPS);

    long double inverseTotal;
    long double inverseCapValue;

    int capsAvailable;
    int capQuantity;

    //understand this, big capacitors make little difference in series, but small make big changes, remember that

    vector<CapacitorList> tempList;

    //iterate through smallest capacitors to biggest in list (ordered greatest to smallest)
    for (int outer = capacitors.getListSize() -1; outer >= 0; outer--)
    {
        CapacitorList used;
        inverseTotal = 0.0L;
        //slowly decrement from smallest to greatest
        for (int i = outer; i >= 0; i--)
        {
            //set counter quantities
            inverseCapValue = 1.0L / capacitors.getCapacitor(i).getCapacitance();
            capsAvailable = capacitors.getCapacitor(i).getQuantity();
            capQuantity = 0;

            //ensure capacitor is available and the added capacitor only contributes to the goal (+ or -)
            while (capQuantity < capsAvailable && (fabs(inverseGoal - (inverseTotal + inverseCapValue)) <= fabs(inverseGoal - inverseTotal)))
            {
                inverseTotal += inverseCapValue;
                capQuantity++;
            }

            //if we used a capacitor during this iteration, push it to the used list
            if (capQuantity > 0)
            {
                used.pushCapacitor(Capacitor(capQuantity, capacitors.getCapacitor(i).getCapacitance()) );
            }
        }

        if (!used.empty())
        {
            //Calculate total capacitance and set order for the new solution
            used.setOrder("series");
            long double newTotalCapacitance = 1/inverseTotal;
            used.setTotalCapacitance(newTotalCapacitance);

            if (!tempList.empty() && abs(newTotalCapacitance - goal) < abs(tempList[tempList.size() -1 ].getTotalCapacitance() - goal))
            {
                tempList.push_back(used);
            }

            else if (tempList.empty())
            {
                tempList.push_back(used);
            }
        }
    }

    //if we didnt find any solution, return empty list, otherwise return best solution found (at end of tempList)
    return tempList.empty() ? CapacitorList() : tempList[tempList.size() - 1];
}




