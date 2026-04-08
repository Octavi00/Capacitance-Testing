#include "Capacitor.h"
#include <vector>
using namespace std;
#ifndef CAPACITORLIST_H
#define CAPACITORLIST_H

class CapacitorList
{
    private:
        vector<Capacitor> capacitors;
        string order; //parallel or series, this is used for some of the functions to know how to calculate total capacitance and how to approach the goal capacitance
        long double totalCapacitance;
        int totalCapacitors;

    public:
        //Default
        CapacitorList() {
            //can be "parallel" or "series"
            order = "";
            totalCapacitance = 0;
            totalCapacitors = 0;
        }

        //Copy constructor
        CapacitorList(vector<Capacitor> caps, string order, long double totalCapacitance) {
            capacitors = caps;
            this->order = order;
            this->totalCapacitance = totalCapacitance;
        }


        //Capcitors have a capacitance and a quantity, so we can represent a list of capacitors as a vector of Capacitor objects
        void pushCapacitor(Capacitor c) {
            capacitors.push_back(c);
            totalCapacitors += c.getQuantity();
        }

        //removes by index, and decrements quantity
        void popCapacitor(int index) {
            if (index < 0 || index >= capacitors.size()) {
                throw out_of_range("Index out of range");
            }

            totalCapacitors -= capacitors[index].getQuantity();
            capacitors.erase(capacitors.begin() + index);
        }
        
        Capacitor getCapacitor(int index) const {
            if (index < 0 || index >= capacitors.size()) {
                throw out_of_range("Index out of range");
            }
            return capacitors[index];
        }



        
        int getListSize() const {
            return capacitors.size();
        }
        
        int getTotalQuantity() const {
            return totalCapacitors;
        }

        //just incase some weird things happen, can recaculate, just takes longer than simply tracing add and removals
        int calculateTotalCapacitors() {
            int total = 0;
            for (const auto& c : capacitors) {
                total += c.getQuantity();
            }
            totalCapacitors = total;
            return total;
        }
        
        bool empty() const {
            return capacitors.empty();
        }
        

        void setOrder(string order) {
            this->order = order;
        }
        
        string getOrder() const {
            return order;
        }
        
        void setTotalCapacitance(long double totalCapacitance) {
            this->totalCapacitance = totalCapacitance;
        }
        long double getTotalCapacitance() const {
            return totalCapacitance;
        }
        

        vector<Capacitor> getCapacitorsVector() const {
            return capacitors;
        }

        //descending sort
        void descendingSort() {
            sort(capacitors.begin(), capacitors.end(),
                [](const Capacitor& a, const Capacitor& b) {
                return a.getCapacitance() > b.getCapacitance(); // descending order
            });
        }



        //capacitance calculators
        void updateTotalCapacitance(){
            if (order == "parallel")
            {
                totalCapacitance = totalParallelCapacitance();
            }
            else if (order == "series")
            {
                totalCapacitance = totalSeriesCapacitance();
            }
        }

        long double totalParallelCapacitance() {
            long double total = 0;
            for (const Capacitor cap : capacitors) {
                total += cap.getCapacitance() * cap.getQuantity();
            }
            return total;
        }


        long double totalSeriesCapacitance() {
            long double inverseTotal = 0;
            for (const Capacitor cap : capacitors) {
                inverseTotal += (1.0L / cap.getCapacitance()) * cap.getQuantity();
            }
            return 1.0L / inverseTotal;
        }


        string toString() const {
            string result = "Capacitor List (Order: " + order + "):\n";
            for (const auto& c : capacitors) {
                result += "Quantity: " + to_string(c.getQuantity()) + "pcs, \t Capacitance: " + to_string(c.getCapacitance()) + "F\n";
            }
            
            result += "Total Quantity: " + to_string(getTotalQuantity()) + "pcs\n";

            return result;
        }
};

#endif