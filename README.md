# Simple CAD for electrical circuit 
 This project will calculate series or parallel circuit its equivalent total resistance, total current, branch currents, the voltage drop across each resistive component and power consumption for each resistor.
For series circuit, the script file using filename series.cir can be described as :
START 
SERIES 
V_1 4 0 DC 9 ; 9 volts voltage source from node 1 to node 4 
R1 1 2 3000 ; 3000 ohm resistor named R1 from node 1 to node 2 
R2 2 3 10000 ; 10000 ohm resistor named R2 from node 2 to node 3 R3 3 4 5000 ; 5000 ohm resistor named 
R3 from node 3 to node 4 
END

For parallel circuit, the script file using filename series.cir can be described as :
START PARALLEL V_1 2 DC 9 ; 9 volts DC voltage source from node 1 to node 2 
R1 1 2 10000 ; 10000 ohm resistor named R1 from node 1 to node 2 
R2 1 2 2000 ; 2000 ohm resistor named R2 from node 1 to node 2 
R3 1 2 1000 ; 1000 ohm resistor named R3 from node 1 to node 2 
END