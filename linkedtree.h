#include "binary_tree.h"
#include <cstddef>

template<class E>
class LinkedTree : public BinaryTree<E> {
 private:
  class Node {
   public:
    Node(const E& v, Node* p) : val(v), parent(p), left(NULL), right(NULL) {}
    E val;
    Node* left;
    Node* right;
    Node* parent;
  };
 public:
  class Position : public BinaryTree<E>::template Position<Position> {
   public:
    Position(Node* n, LinkedTree& tree) : current(n), theTree(tree) { };
    E& operator*() { return current->val; }
    Position parent() { return Position(current->parent); }
    Position left() { return Position(current->left); }
    Position right() { return Position(current->right); }
    bool isValid() const { return current != NULL; }
    bool isLeaf() const {
      return (current->left == NULL && current->right == NULL);
    }
    bool isRoot() const {
      return (current->parent == NULL);
    }
    void insertRight(const E& val) {
      Node* toInsert = new Node(val, current);
      toInsert->right = current->right;
      if ( toInsert->right != NULL ) {
        toInsert->right->parent = toInsert;
      }
      current->right = toInsert;
    }
    void insertLeft(const E& val) {
      Node* toInsert = new Node(val, current);
      toInsert->left = current->left;
      if ( toInsert->left != NULL ) {
        toInsert->left->parent = toInsert;
      }
      current->left = toInsert;
    }

   private:
    LinkedTree& theTree;
    Node* current;
  };

  LinkedTree(const E& r) : root(new Node(r, NULL)), _size(0) {}

  Position getRoot() {
    return Position(root);
  }

  virtual int size() const { return _size; }

 private:
  Node* root;
  int _size;

};
