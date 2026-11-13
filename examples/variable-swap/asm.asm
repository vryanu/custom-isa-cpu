* This program will write 4 numbers, then swap their addresses

* Create 2 numbers in memory (2,1)
SET REGA 1
SET REGB 1
ADD * = 2
STORE * 2 in 00
LOAD
MOV ACC REGA * rega = 2
SUB * = 1
SET MAR 1
STORE * 1 in 01 & 2 in 00

* Values are currently: REGA=2, REGB=1, MAR=1, ACC=2

* Start first swap (2,1)->(1,2)
SET MAR 1
LOAD * Get the value of the first swap number into output (1)
SET MAR 0 * Move MAR to other numbers address (00)
MOV ACC ACC * Move first swap number (1) to the ACC
LOAD * Load second swap number in output (2)
STORE * Store the ACC in the swapped address (1 in 00)
SET MAR 1 * Move MAR back to first address
MOV ACC ACC * Move second swap number (2) to ACC
STORE * Store the second swap number in the original numbers address (2 in 01)
* Now it is (1,2)

* Values are currently: REGA=2, REGB=1, MAR=1, ACC=2

* Create 2 more numbers in memory (4,3)
ADD * = 3
SET MAR 3
STORE * 3 in 03
SET REGB 2
MUL * = 4
SET MAR 2
STORE * 4 in 02 & 3 in 03

* Values are currently: REGA=2, REGB=2, MAR=2, ACC=4

* Start second swap (4,3) -> (3,4)
LOAD * Get the value of the first swap number into output (4)
SET MAR 3 * Move MAR to other numbers address (03)
MOV ACC ACC * Move first swap number (4) to the ACC
LOAD * Load second swap number in output (3)
STORE * Store the ACC in the swapped address (4 in 03)
SET MAR 2 * Move MAR back to first address
MOV ACC ACC * Move second swap number (3) to ACC
STORE * Store the second swap number in the original numbers address (3 in 02)
* Now it is (3,4)

* Final: [1,2,3,4]

END
END

