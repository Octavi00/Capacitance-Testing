# Capacitance-Testing
A c++ based capacitance approximation for large capacitors to reach large or equal capacitances. Technically could do Resistances just as well by flipping definitions of Parallel or Series.

Limited Functionality:
    This program isn't complete by two means.
    1. Lacks UI, in an ideal world I would have the time to implete a UI, preferably a Python Tkinter interface, and is next on the to-do list.
    2. Limited to pure Parallel, pure Series, or Parallel/Series mix. Program will need future iterations to achieve a much more optimal approximation in certain test cases by taking advantage of Kirckoff's loop rules for non Parallel / Series circuits. Program could also benefit from having a more flexible Circuit Data Type for embedded Parallel / Series circuits.