#include <iostream>
using namespace std;

class Node {
  public:
    int data;
    Node* left;
    Node* right; 

    Node(int value) : data(value), left(nullptr), right(nullptr) {} 
};

class BST {
  private:
    Node* root;

    Node* insert(Node* node, int value) {
      if (node == nullptr) {
        return new Node(value);
      }

      if (value < node->data) {
        node->left = insert(node->left, value);
      } else {
        node->right = insert(node->right, value);
      }

      return node;
    }

    Node* search(Node* node, int value) const {
      if (node == nullptr || node->data == value) {
        return node;
      } 

      if (value < node->data) {
        return search(node->left, value);
      } else {
        return search(node->right, value);
      }

      return node;

    }

    void inOrder(Node* node) const {
      if (node != nullptr) { 
        inOrder(node->left);
        cout<<node->data<<" ";
        inOrder(node->right);
      }
    }

    Node* findMin(Node* node) const {
      while (node->left != nullptr) {
        node = node->left;
      }

      return node;
    }

    Node* remove(Node* node, int value) {
      if (node == nullptr) {
        return node;
      }

      if (value < node->data) {
        node->left = remove(node->left, value);
      } else if (value > node->data) {
        node->right = remove(node->right, value);
      } else {
        if (node->left == nullptr) {
          Node* temp = node->right;
          delete node;
          return temp;
        } else if (node->right == nullptr) {
          Node* temp = node->left;
          delete node;
          return temp;
        }
 
        Node* temp = findMin(node->right);  
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
      } 

      return node;
    }   

    void destroyTree(Node* node) {
      if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
      }
    }

    public:
      BST() : root(nullptr) {}

      ~BST() {
        destroyTree(root);
      }

      void insert(int value) {
        root = insert(root, value);
      }
      
      void remove(int value) {
        root = remove(root, value);
      }
    
      void inOrder() const {
        inOrder(root);
      }

      Node* search(int value) const {
        return search(root, value);
      } 
};

int main() {
  BST* bst = new BST();

  bst->insert(21);
  bst->insert(14);
  bst->insert(7);
  bst->insert(28);
  bst->insert(42);
  bst->insert(49);
  bst->insert(63);
  bst->insert(56);
  bst->insert(70);

  cout<<"In-order: ";

  bst->inOrder();

  bst->remove(21);
  
  cout<<endl<<"In-order after removal: ";

  bst->inOrder();

  cout<<endl<<"Search for an existing node: "<<bst->search(49);
  cout<<endl<<"Search for a missing node: "<<bst->search(27);

  return 0;
}
