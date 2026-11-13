* Loop demo

SET REGA 1 * Initialize start value

* Start main loop
ADD * Add the numbers 1 + 0
STORE * Store result 1 in 00
LOAD * Load 1 onto output
MOV ACC MAR * Set MAR to output (next address) 
MOV ACC REGB * Set REGB to next number
LOOP 5 4 * Iterate last 5 commands 4 times

* Final RAM output: [1,2,3,4,5] (5 numbers because the code runs once before looping)