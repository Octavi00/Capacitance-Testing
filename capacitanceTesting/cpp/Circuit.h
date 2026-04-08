#include "CapacitorList.h"
#include "Capacitor.h"
#include <vector>
#include <iostream>
using namespace std;

#ifndef CIRCUIT_H
#define CIRCUIT_H


//linked data types to reduce data usage
//Contains an Overall vector which is a parallel of all possible lists, not particularly recurssive due to lack of a need for it
class Circuit
{
    private:
        long double totalCapacitance;
        int quantity;
        vector<CapacitorList*> circuit;


    public:
        //Default constructor
        Circuit()
        {
            clear();
        }

        //destructor
        ~Circuit()
        {
            clear();
        }

        //delete all allocated ptrs
        void clear()
        {
            circuit.clear();
            quantity = 0;
            totalCapacitance = 0;
        }

        void pushList(CapacitorList &c)
        {
            //Create ptr, push into list
            CapacitorList* temp;
            temp = &c;
            circuit.push_back(temp);

            //update quantity and totalCapacitance counters
            quantity += c.getTotalQuantity();
            totalCapacitance += c.getTotalCapacitance();
        }

        //removes most recently added list
        void popList()
        {
            if (circuit.empty())
            {
                //Maybe consider throwing an error during debugging if needed
                return;
            }

            //Save ptr
            CapacitorList* temp = circuit[circuit.size() -1];

            //decrease size, and capacitance counters
            quantity -= temp->getTotalQuantity();
            totalCapacitance -= temp->getTotalCapacitance();

            // pop from vector
            circuit.pop_back();
        }

        const vector<CapacitorList*> getList()
        {
            return circuit;
        }

        const long double getTotalCapacitance()
        {
            return totalCapacitance;
        }

        void const printBoard()
        {
            /*
            Drawing

            Circuit
            Wires: | -
            Capacitors: represented by numbers
            Left is positive terminal


               |->1-------|
            |  |->1-------|
            |--|->1-------|-|
            |  |->1-------|
               |->1->2->3-|
            */

            vector<string> board;
            int t_capacitance;
            string t_row;

            for (auto c : circuit)
            {
                if (c->getOrder() == "parallel")
                {
                    //Individually adds each capacitor to the vector, thats what it means to add parallel to parallel
                    for (auto cap : c->getCapacitorsVector())
                    {
                        t_capacitance = cap.getCapacitance() * 1000000000; // 10^9 implies result becomes nano
                        for (int i = 0; i < cap.getQuantity(); i++)
                        {
                            board.push_back("| --> " + to_string(t_capacitance) + "nF ");
                        }
                    }
                }

                else if (c->getOrder() == "series")
                {
                    t_row = "| ";
                    
                    //Individually adds each capacitor to row, then add it to the outer parallel board diagram
                    for (auto cap : c->getCapacitorsVector())
                    {
                        //for simplicity
                        t_capacitance = cap.getCapacitance() * 1000000000; // 10^9 implies result becomes nano
                        for (int i = 0; i < cap.getQuantity(); i++)
                        {
                            t_row += ("--> " + to_string(t_capacitance) + "nF ");
                        }
                    }

                    board.push_back(t_row);
                }

                else
                {
                    throw invalid_argument("Capacitor has no proper order");
                }
            }


            //now print it out
            cout << "Circuit Board" << endl;
            t_capacitance = board.size(); //reusing this variable for space saving purposes
            for (int i = 0; i < t_capacitance; i++)
            {
                if (i == t_capacitance / 2)
                {
                    cout << "+ --\t" << board[i] << endl;
                }

                else
                {
                    cout << '\t' << board[i] << endl;
                }
            }
            cout << "Total Capacitance: " << totalCapacitance << " \t Total Quantity Required: " << quantity << endl;

        }


    


};

#endif
