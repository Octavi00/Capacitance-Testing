#include <stdexcept>
using namespace std;
#ifndef CAPACITOR_H
#define CAPACITOR_H
class Capacitor
{
    private:
        unsigned int qunatity;
        long double capacitance; // in Farads


    public:
        // 5 0.0005F capacitors would be represented as Capacitor(5, 0.0005)
        Capacitor(int q, double c) {
            qunatity = q;
            capacitance = c;
        }

        long double getCapacitance() const {
            return capacitance;
        }
        int getQuantity() const {
            return qunatity;
        }

        void setQuantity(int q) {
            qunatity = q;
        }

        //throws error if quantity is 0 or less, since you cannot have negative quantity of capacitors, and you cannot decrement 0 quantity of capacitors
        void decrementQuantity() {
            if (qunatity <= 0) {
                throw invalid_argument("0 quantity cannot be decremented");
            }
            qunatity--;
        }
};
#endif