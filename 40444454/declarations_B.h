#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

// *** BINARY SEARCH TREE DECLARATIONS & NODE STRUCT ***

// Node of a tree, stores an identifier
struct Identifier {
  string name;
  string scope;
  string type;
  int line_number;
  int number_of_references;
  bool is_a_function;  // when this is false it's a variable
};

struct node {
  // Identifiers stored in this node of the tree
  Identifier identifier;
  Identifier current_variable;
  // The left branch of the tree
  node *left;
  // The right branch of the tree
  node *right;
};

class BinarySearchTree {
 public:
  // **Constructors and destructors**

  // Adds a parameter to the tree
  static void insert(node **tree, Identifier identifier);
  // Searches Tree
  static Identifier *search(node *tree, string name);
  // Clean up tree
  ~BinarySearchTree();
  void destroy(node *tree);
  void inorder(node *tree);
  void preorder(node *tree);

 private:
  node *root = nullptr;  // pointer to the root node of the tree
};

// *** PARSER CLASS DECLARATIONS ***

// alias for vector<vector<string>>
using LinesOfCode = vector<vector<string>>;

// alias for vector<vector<string>>
using Function = vector<vector<string>>;

// alias for vector<vector<vector<string>>>
using FunctionList = vector<Function>;

const std::unordered_set<string> set_of_ctypes(
    {"char", "short", "int", "long", "long long", "float", "double", "char*",
     "short*", "int*", "long*", "long long*", "float*", "double*", "void"});

class Parser {
 private:
  string path_to_file;
  vector<int> empty_lines_before_func;
  node *identifiers;
  std::ofstream output_file;

  void print_symbols();
  FunctionList get_function_list(LinesOfCode lines_of_code);
  bool is_a_ctype(std::string lookup);
  void parse_inline_declarations(vector<string> line, Function function,
                                 int line_number, int line_index);
  void count_special_tokens(vector<string> line);
  void increment_count_if_found(string name, string scope);
  void write_identifier_to_file(Identifier current_variable);
  void check_line_for_declarations(int line_index, vector<string> line,
                                   int line_number, Function function);

 public:
  Parser(string filename);
  void parse();
};
