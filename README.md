# SET07109-2020
CPP Coursework; compiler and (not working) Binary Search Tree
**NAME OF PROGRAM**

symbol_table
symbol_table_B

**TOOL CHAIN**

gcc -std=c++17
________________________________________________________________________________________________________________________

**FILES**

*Files available:*
- symbol_table_A.cpp
- symbol_table_B.cpp

*Files required:*
- parser_A.cpp
- parser_B.cpp
- bst.cpp
- declarations_A.h
- declarations_B.h
- Makefile
________________________________________________________________________________________________________________________

**BUILDING**

*Build from command line inputs:* 
`make compile_run_a file="./file.c"`
`make compile_run_b file="./file.c"`

*Cleaning folder from command line:*
`make clean`

*Options:*
`g++ -std=c++17 symbol_table.cpp -o symbol_table` -> upon entering
this command the symbol table is processed.
`./symbol_table $(file)` -> upon entering the correct file name, 
the file is then read through and an output .txt file
exited.

________________________________________________________________________________________________________________________

**DESCRIPTION**

*An App that:*

* **PART A**
  Functions as a compiler symbol table. This will read in a
  file containing a C language program, and will record
  information about each identifier (variable name,
  functionname, line number, how many time referenced) to an output file called "identifiers.txt". In the console it will print out the information as well as how many if statements, for and while loops.

* **PART B**
  Using the above logic, however utilising a binary search tree
  to efficiently search through the file. It searches and
  inserts a new item into each node when finding the variables
  or functions. The BST also has a cleaning function.
