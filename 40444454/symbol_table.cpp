/*
 *  @author: Stella Williams 40444454
 *  Last Modified: 02/05/2021
 *  Purpose: Functions as a compiler symbol table. This will read in a .c
 *  file containing a C language program, and will record information about
 *  each identifier (variable name or functionname) in a file called
 * "identifiers.txt".
 */
#include <iostream>
#include <string>

#include "parser_A.cpp"

int main(int number_of_arguments,
         const char *
             *arguments) {  // passes the parse class and performs the functions
                            // in the class to print the symbol table
  if (number_of_arguments != 2) {
  std:
    cout << "Input correct number of arguments";
    exit(1);
  }

  Parser parser(arguments[1]);
  parser.parse();
}
