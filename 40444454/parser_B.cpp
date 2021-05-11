/*
 *  @author: Stella Williams 40444454
 *  Last Modified: 30/04/2021
 *  Purpose: Functions as a compiler symbol table. This will read in a .c
 *  file containing a C language program, and will record information about
 *  each identifier (variable name or functionname) in a file called
 * "identifiers.txt". It will use a binary search tree to find these variables
 *  and the information about it, print it out into the file.
 */
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#include "bst.cpp"
#include "declarations_B.h"

using namespace std;

// constructor: intialise file path
Parser::Parser(string file_path) {
  path_to_file = file_path;
  identifiers = nullptr;
}

bool Parser::is_a_ctype(
    std::string lookup) {  // looks up the string to see if it is a ctype
  return set_of_ctypes.count(lookup);  // 0 or 1 since its a set of unique items
}

FunctionList Parser::get_function_list(
    LinesOfCode lines_of_code) {  // searches through lines of code to find
                                  // closing bracket and semi-colon aka
                                  // properties of a function not a variable
  bool found_closing_bracket = true;
  FunctionList function_list;

  for (vector<string> line : lines_of_code) {
    // is line non empty and is the first item in the line a c_type
    // int/char/long etc
    if (line.size() > 0 && is_a_ctype(line[0]) && found_closing_bracket) {
      // is the last item in the line a semi colon?

      if (line.back() != ";") {
        // when last item is not ; this is a function because the line started
        // with a c_type

        // we found a new function
        // creating a new item in the list to represent the current function
        // add first line to first function
        function_list.push_back({line});
      } else {
        // it wasn't a new function so add it to the existing
        function_list.back().push_back({line});
      }
      // continue looking for closing bracket
      found_closing_bracket = false;
    }

    else if (line.size() > 0 && line[0] != "}")  // false
    {
      // line add to the current function
      // current function is always the last item in the list
      function_list.back().push_back({line});
    }

    else if (line.size() > 0 && line[0] == "}")  // true
    {
      // we might have found the end of the function
      function_list.back().push_back({line});

      // on the next line check if we found a function
      found_closing_bracket = true;
    }
  }

  return function_list;
}

LinesOfCode tokenize_file(
    ifstream &file_stream) {  // tokenizes file stores the tokenized string in a
                              // temp vector
  LinesOfCode parsed_lines;
  char current_line[256];

  while (!file_stream.eof()) {
    file_stream.getline(current_line, 256);

    char *current_token;
    const char *delimiter = " \n\t";
    current_token = strtok(current_line, delimiter);

    vector<string> temp;

    while (current_token != NULL) {
      temp.push_back(current_token);
      current_token = strtok(NULL, delimiter);
    }

    parsed_lines.push_back(temp);
  }
  return parsed_lines;
}

void Parser::write_identifier_to_file(
    Identifier current_variable) {  // writes identifier to file with the
                                    // properties found
  output_file << current_variable.name;

  if (current_variable.scope.length() > 0) {
    output_file << " (" << current_variable.scope << ")";
  }

  output_file << ", "
              << "line " << current_variable.line_number << ", ";

  if (current_variable.is_a_function) {
    output_file << "function";
  } else {
    output_file << "variable";
  }

  output_file << ", " << current_variable.type << ", "
              << "referenced " << current_variable.number_of_references << "\n";
}

void Parser::increment_count_if_found(
    string name,
    string scope) {  // Search is implemented with scope & functions. Checks for
                     // scope and if the variable is a function, adds to
                     // references if so.
  Identifier *var = BinarySearchTree::search(identifiers, name);
  if (var == nullptr) {
    return;
  }
  if (var->scope == scope) {
    var->number_of_references = var->number_of_references + 1;
    return;
  } else if (var->is_a_function) {
    var->number_of_references = var->number_of_references + 1;
    return;
  }
}

// void Parser::parse_inline_declarations(vector<string> line, Function
// function,
//                                        int line_number, int line_index) {
//   bool opening_bracket_found = false;
//   for (size_t token_index = 0; token_index < line.size() - 1; token_index++)
//   {
//     const string token = line[token_index];

//     if (token == "(") {
//       opening_bracket_found = true;
//     } else if (token == ")") {
//       opening_bracket_found = false;
//     } else if (is_a_ctype(token) && opening_bracket_found) {
//       string c_type = line[token_index];
//       string variable_name = line[token_index + 1];
//       string function_name = function[0][1];
//       string scope = function_name;
//       Identifier current_variable = {
//           .name = variable_name,
//           .scope = scope,
//           .type = c_type,
//           .line_number = line_number,
//           .number_of_references = 0,
//           .is_a_function = false,
//       };
//       identifiers->current_variable;
//     }
//   }
// }

// void Parser::check_line_for_declarations(int line_index, vector<string> line,
//                                          int line_number, Function function)
//                                          {
//   bool is_function =
//       line_index == 0 && is_a_ctype(line[0]) && line.back() != ";";

//   if (is_function) {
//     string function_name = line[1];
//     string function_type = line[0];

//     Identifier current_variable = {
//         .name = function_name,
//         .scope = "",
//         .type = function_type,
//         .line_number = line_number,
//         .number_of_references = 0,
//         .is_a_function = true,
//     };

//     identifiers->current_variable;

//     parse_inline_declarations(line, function, line_number, line_index);
//   } else if (line[0] == "for") {
//     // for loops
//     parse_inline_declarations(line, function, line_number, line_index);
//   } else if (line.size() > 0 && is_a_ctype(line[0])) {
//     // a normal variable declaration

//     if (line.back() == ";") {
//       string c_type = line[0];
//       string variable_name = line[1];
//       if (c_type == "long" && line[1] == "long") {
//         c_type = "long long";
//         variable_name = line[2];
//       }
//       string function_name = function[0][1];

//       Identifier current_variable{
//           .name = variable_name,
//           .scope = function_name,
//           .type = c_type,
//           .line_number = line_number,
//           .number_of_references = 0,
//           .is_a_function = false,
//       };

//       identifiers->current_variable;
//     }
//   }
// }

int if_counter = 0;
int while_counter = 0;
int for_counter = 0;

void Parser::count_special_tokens(
    vector<string>
        line) {  // finding special tokens if statements, for and while loops
  if (line[0] == "if") {
    if_counter++;
  }

  if (line[0] == "for") {
    for_counter++;
  }

  if (line[0] == "while") {
    while_counter++;
  }
}

void Parser::parse() {  // opens new .txt file called identifiers and trunicates
                        // each time.
  ifstream file_stream;
  file_stream.open(path_to_file);

  output_file.open("identifiers.txt", std::ios::trunc);

  if (!file_stream) {
    std::cout << "Unable to open file";
    file_stream.close();
    output_file.close();
    exit(1);
  }

  // LinesOfCode parsed_lines;

  // parsed_lines = tokenize_file(file_stream);
  // FunctionList function_list = get_function_list(parsed_lines);

  // int line_number = 0;

  // for (int function_index = 0; function_index < function_list.size();
  //      function_index++) {
  //   Function function = function_list[function_index];

  //   if (function_index > 0) {
  //     // since in the examples there is a new line after each new function
  //     // and we ignored new line characters this is needed to correct the
  //     // count
  //     line_number++;
  //   }

  //   for (int line_index = 0; line_index < function.size(); line_index++) {
  //     line_number++;
  //     vector<string> line = function[line_index];

  //     count_special_tokens(line);
  //     check_line_for_declarations(line_index, line, line_number, function);

  //     bool is_function_declaration =
  //         line_index == 0 && is_a_ctype(line[0]) && line.back() != ";";
  //     if (!is_function_declaration) {
  //       for (int token_idx = 0; token_idx < line.size(); token_idx++) {
  //         string token = line[token_idx];
  //         string prev_token = "";
  //         if (token_idx > 0) prev_token = line[token_idx - 1];

  //         if (!is_a_ctype(token) && !is_a_ctype(prev_token) &&
  //             regex_match(token, regex("[a-zA-Z_]+"))) {
  //           string function_name = function[0][1];
  //           increment_count_if_found(token, function_name);
  //         }
  //       }
  //     }
  //   }
  // }

  // std::cout << "Variables: " << identifiers.size() - function_list.size();
  // std::cout << "\n";
  // std::cout << "Functions: " << function_list.size();
  // std::cout << "\n";
  std::cout << "If statements: " << if_counter;
  std::cout << "\n";
  std::cout << "For loops: " << for_counter;
  std::cout << "\n";
  std::cout << "While loops: " << while_counter;
  std::cout << "\n";

  // for (Identifier identifier : identifiers) {
  //   write_identifier_to_file(identifier);
  // }

  file_stream.close();
  output_file.close();
}
