#include "capFunctions.h"
#include "CapacitorList.h"
#include "Circuit.h"
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef UNITTEST_H
#define UNITTEST_H

//function prototypes
void introTest(CapacitorList list, vector<long double> goals);
void runTests(CapacitorList list, vector<long double> goals);
void printResults(const CapacitorList& test, const long double& goal);
void printCircuitResults(Circuit &c, const long double& goal);

//NOTE: Overides formatting state, and doesn't reset it.
void mainTest()
{
    CapacitorList list;
    
    // Simpler test: just a few capacitor values
    list.pushCapacitor(Capacitor(10, 0.0001));   // 100 uF
    list.pushCapacitor(Capacitor(10, 0.00025));  // 250 uF
    list.pushCapacitor(Capacitor(10, 0.0005));   // 500 uF
    list.pushCapacitor(Capacitor(10, 0.001));    // 1000 uF
    list.descendingSort(); // Ensure capacitors are in descending order of capacitance for the algorithms to work correctly

    vector<long double> goals;
    goals.push_back(0.0005); // 500 uF
    goals.push_back(0.00075); // 750 uF
    goals.push_back(0.0015); // 1500 uF

    //print introduction
    introTest(list, goals);

    //run tests
    runTests(list, goals);
}




void introTest(CapacitorList list, vector<long double> goals)
{
    cout << "Available Capacitors" << endl;
    for (auto i : list.getCapacitorsVector())
    {
        cout << "Capacitance: " << i.getCapacitance() << " Quantitiy: " << i.getQuantity() << endl;
    }

    cout << "Goals: ";
    for (auto i : goals)
    {
        cout << i << "\t ";
    }
    cout << endl << "Initiaiting unit tests" << endl;
}




void runTests(CapacitorList list, vector<long double> goals)
{
    cout << "Testing combinations\n\n\n\n" << endl;
    cout << ""<<endl;

    for (int i = 0; i < goals.size(); i++) {
        cout << "Running parrallel test" << endl;
        CapacitorList testP = parallelCapacitanceAprox(list, goals[i]);
        printResults(testP, goals[i]);
        cout << "\n\n\n\n" << endl;
        
        cout << "Running greedy parrallel test" << endl;
        CapacitorList testGP = greedyParallelCapacitanceAprox(list, goals[i]);
        printResults(testGP, goals[i]);
        cout << "\n\n\n\n" << endl;

        cout << "Running series test" << endl;
        CapacitorList testS = seriesCapacitanceAprox(list, goals[i]);
        printResults(testS, goals[i]);
        cout << "\n\n\n\n" << endl;
        
        cout << "Testing expiremental circuit (non-approximation, just for proof of theory)" << endl;
        Circuit circuit;
        circuit.pushList(testP);
        circuit.pushList(testS);
        circuit.printBoard();
        printCircuitResults(circuit, goals[i]);
        

        cout << "\n" << "END OF " <<  i+1 << " testing Iteration" << "\n\n\n\n" << endl;
    }


    

}




void printResults(const CapacitorList& test, const long double& goal)
{
    if (!test.empty()) {
        //save formatting state
        ios tempState(nullptr);
        tempState.copyfmt(std::cout);

        cout <<"Total quantity for " + test.getOrder() + " order Required = " << test.getTotalQuantity() << endl;
        cout << test.toString();
        cout << "Goal capacitance: " << scientific << goal << "F \t Achieved Capacitance: " << test.getTotalCapacitance() << "F \t Percent Achieved: " << fixed << setprecision(2) << (test.getTotalCapacitance()/goal * 100)<< "%" << endl;
        
        //undo formatting changes
        cout.copyfmt(tempState);
    }

    else {cout << "No solution found" << endl;}
}

void printCircuitResults(Circuit &c, const long double& goal)
{
    if (!c.getList().empty()) {
        //save formatting state
        ios tempState(nullptr);
        tempState.copyfmt(std::cout);

        cout << "Goal capacitance: " << scientific << goal << "F \t Achieved Capacitance: " << c.getTotalCapacitance() << "F \t Percent Achieved: " << fixed << setprecision(2) << (c.getTotalCapacitance()/goal * 100)<< "%" << endl;
        
        //undo formatting changes
        cout.copyfmt(tempState);
    }

    else {cout << "No solution found" << endl;}
}

#endif