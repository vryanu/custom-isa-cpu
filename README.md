# Cpu

**8bit CPU in Logisim + ISA + toolchain**

* Registers REGB00, REGA01, MAR10, ACC11
* Operators ADD000, SUB001, MUL010, DIV011, MOD100, AND101, OR110, XOR111

**ISA**

ART & RAM & LOOP commands

ART [00000][000 OP]

RAM [00 MOV/SET VAL][MOV][LOAD][STORE][SET][00 MOV/SET LOC]

LOOP [3 BITS ITERATIONS][2 BITS ENABLE][3 BITS JUMP BACK AMOUNT]

* ACC acts as RAM output when used as a val
* MOV must be 1 for SET to be used

**Commands Usage**
* MOV [Val] [Loc] Moves a value to another register
* SET [2 bit number val] [Loc] Sets a value to a register
* STORE stores a value at the selected address
* LOAD loads a value at the selected address
* LOOP [Iterations] [Jump back] Loops a segment of code
* LOOP [i] [7] will print on every iteration

<img width="334" height="205" alt="hello-world" src="https://github.com/user-attachments/assets/9b7af1dd-dd15-43a3-8152-46aae2a7dbbe" />

[Examples](examples/)
