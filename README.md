# Simulation-machine-with-a-data-flow-architecture


This projects goal was to implement a  simulator machine with a data flow architecture. 
An abstract operation can have any number of operands, it has an ID, and it produces a result,with a delay of T(time).The delay is specific to every operation. An operation gets an operand from an input port. An operation is not allowed to start until every operand shows up(gets calculated) on the operations input port. Every operation that is ready to execute, gets executed in "parralel". An operation sends its results through the input ports of other operations. Operations are this way connected in a network.

Arithmetic opeartion is a class that has at most two operands and produces a result. The arithmetic operations implemented in the project are addition(5ns),multiplication(8ns),exponents(10ns), setting value (3ns).

Expressions are constants and variables connected by operators +, *, ^. 

Program is written in a .txt file and is consisted of instructions(multiple lines of expressions).

Compiler is a class that translates the instructions written in the program. Its output is written in the .imf file. The sintax is described below.

Machine  can read and execute the program from an .imf file. Program gets executed by reading operations, making a graph of the operations and other data,  then operations get scheduled into an execution queue The operations are scheduled by putting those operations whitch have all input ports ready for the operation. Machine executes the program until the the exeqution queue is empty. Machine prints its execution trace in an output .log file. The sintax of the file is described below.


Memory allows writing and reding of variables. A value of a varible can be set, you can get a value, if a read operation is requested from a place in memory whitch is empty, the program will send an exeption.   

***********
Example program
x = 2
y = 3
z = 2*x^3 + x^5*y^3 + 5

***********
Example .imf file
(1) = x 2
(2) = y 3
(3) ^ x 3
(4) * 2 (3)
(5) ^ x 5
(6) ^ y 3
(7) * (5) (6)
(8) + (4) (7)
(9) + (8) 5
(10) = z (9)
***********
Example execution trace in .log file
(1) 0ns/3ns
(2) 0ns/3ns
(3) 3ns/13ns
(5) 3ns/13ns
(6) 3ns/13ns
(4) 13ns/21ns
(7) 13ns/21ns
(8) 21ns/26ns
(9) 26ns/31ns
(10) 31ns/36ns
***********
