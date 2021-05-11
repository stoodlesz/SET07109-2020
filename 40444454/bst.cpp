#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#include "declarations_B.h"

void BinarySearchTree::insert(
    node **tree,
    Identifier
        identifier) {  // function to insert a new node from the identifiers
                       // struct, the name of the variable/function
  if (*tree == nullptr) {
    // Create new node
    *tree = new node;
    // Set new value
    (*tree)->identifier = identifier;
    // Set branches to nullptr
    (*tree)->left = nullptr;
    (*tree)->right = nullptr;
  } else {
    if (identifier.name < (*tree)->identifier.name) {
      insert(&(*tree)->left, identifier);
    } else if (identifier.name > (*tree)->identifier.name) {
      insert(&(*tree)->right, identifier);
    } else
      return;
  }
}

Identifier *BinarySearchTree::search(
    node *tree,
    string name) {  // function to search the tree if the name of the identifier
                    // is there, on both sides of the tree
  if (tree == nullptr) {
    return nullptr;
  }
  if (tree->identifier.name == name) {
    return &tree->identifier;
  }
  if (name < tree->identifier.name) {
    return search(tree->left, name);
  }
  return search(tree->right, name);
}

// Deletes the tree
void BinarySearchTree::destroy(node *tree) {  // function to delete the tree
  if (tree == nullptr) {
    return;
  }
  // Delete the left then right branches
  destroy(tree->left);
  delete tree->left;
  destroy(tree->right);
  delete tree->right;
}

BinarySearchTree::~BinarySearchTree()  // Destroys root of tree
{
  destroy(root);
}

void BinarySearchTree::inorder(node *tree) {  // Prints the tree in order
  if (tree == nullptr) {
    return;
  }
  inorder(tree->left);
  cout << tree->identifier.name << " " << endl;
  inorder(tree->right);
}

void BinarySearchTree::preorder(
    node *tree) {  // Prints the tree in pre-order (current node, left, right)
  if (tree == nullptr) {
    return;
  }
  cout << tree->identifier.name << " " << endl;
  inorder(tree->left);
  inorder(tree->right);
}
