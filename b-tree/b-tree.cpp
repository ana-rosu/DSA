#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("abce.in");
ofstream g("abce.out");

class Node {
private:
    static int order; // maximum number of children a node can have (maximum number of keys a node can have is order - 1)
    int nrKeys; // number of keys
    vector<int> keys; // array of keys
    vector<Node*> children; //array of child pointers
    bool leaf;
public:
  Node(bool leaf);

  void splitChild(int, Node*);
  void insertNewKey(int key);
  void traverse();
  void traverseInterval(int, int);
  bool search(int);
  int searchBiggestNrSmallerThan(int);
  int searchSmallestNrBiggerThan(int);

  bool isFull();
  static void setOrder(int);
  friend class BTree;
};
// initializing the static member variable order to some default value
int Node::order = 0;

class BTree{
private:
  Node* root;
  int order; // the order of the BTree (maximum nr of children of a node == maximum nr of keys + 1 of a node) 
public:
  BTree(int);
  void insert(int);
  void deleteKey(int);
  void traverse();
  void traverseInterval(int, int);
  bool search(int);
  int searchBiggestNrSmallerThan(int);
  int searchSmallestNrBiggerThan(int);
  void deleteNodes(Node* node){
    for(auto child: node->children)
      if(child != nullptr)
          deleteNodes(child);
    delete node;
  }
  ~BTree(){
    deleteNodes(root);
  }
};

// constructors 
Node::Node(bool leaf){
  nrKeys = 0;
  this->leaf = leaf;
}
BTree::BTree(int order){
  this->root = nullptr;
  this->order = order;
}
// setters
// setter for order (to use it in main)
void Node::setOrder(int order) {
  Node::order = order;
}


//check if the node contains the maximum number of keys or not
bool Node::isFull(){
  return this->nrKeys == Node::order - 1;
}
void Node::splitChild(int i, Node* child){

  Node* newNode = new Node(child->leaf);
  int newNrKeys = (Node::order - 1)/2;
  newNode->nrKeys = newNrKeys;

  // copy the last half keys of node to the newNode
  for (int index = 0; index < child->keys.size() - newNrKeys - 1; ++index)
    newNode->keys.push_back(child->keys[index + newNrKeys + 1]);

  // copy the last half children of child to newNode
  if(!child->leaf) 
    for(int index = 0; index < child->keys.size() - newNrKeys - 2; ++index)
      newNode->children.push_back(child->children[index + newNrKeys + 1]);

  child->nrKeys = newNrKeys;
  child->keys.resize(newNrKeys);
  //  THIS node is having newNode as a child, so we find the correct position for newNode
  this->children.resize(this->children.size() + 1);
  for (int index = this->nrKeys; index >= i+1; index--)
    this->children[index + 1] = this->children[index];
  this->children[i+1] = newNode;

  // now, we move the middle key of the child node we're splitting to this node
  // finding the correct position
  this->keys.resize(this->keys.size() + 1);
  for (int index = this->nrKeys-1; index >= i; index--)
    this->keys[index + 1] = this->keys[index];

  this->keys[i] = child->keys[newNrKeys];
  this->nrKeys = this->nrKeys + 1;
}

void Node::insertNewKey(int key){
  // initiliaze index at the rightmost key of this node
  int index = nrKeys - 1;
  if (!leaf){
    // INTERNAL NODE (has children)

    // we find the position at which to insert our key 
    while(key < this->keys[index] && index >= 0){
      index--;
    }
    if(this->children[index + 1]->isFull()){
        // split children[index+1] into two
        this->splitChild(index+1, children[index+1]);
        // after split, the middle key of children[i] went up 
        if(key < this->keys[index+1])
          this->children[index + 1]->insertNewKey(key);
        else
          this->children[index + 2]->insertNewKey(key);
    } 
    // if the child node is NOT full, we insert the key 
    else{
      this->children[index + 1]->insertNewKey(key);
    }
  } 
  else {
    // LEAF NODE

    // if and while the key we want to insert is smaller than the keys present in this node, we move all the keys greater than it one position to the right in order to make space and insert our new key at its correct position
    keys.resize(keys.size() + 1);
    while(key < keys[index] && index >= 0){
      keys[index + 1] = keys[index];
      index--;
    }
    keys[index + 1] = key;
    this->nrKeys  = this->nrKeys + 1;
  }
}

// 1. INSERT A KEY
void BTree::insert(int key){
  // if tree is empty, it means we are now inserting the root
  if(root == nullptr){
    root = new Node(true);
    root->keys.push_back(key);
    root->nrKeys = 1;
    return;
  }
  // if tree is not empty 
  else{
    // if the root is not full (it doesn't have the max nr of keys a node can have) => we append the key here in this node
    if(!root->isFull()){
      root->insertNewKey(key);
    }
    else{
      // if the root is full, we must split it and create a new root
      Node* newRoot = new Node(false);
      newRoot->children.push_back(root);
      newRoot->splitChild(0, root);
      // newRoot has 2 children nodes now
      // we want to append the key in one of them (so either on children[0] or on children[1]), coresponding to its value
      // in order to do that we compare the value of the key with the value in our newRoot
      if(key < newRoot->keys[0])
        newRoot->children[0]->insertNewKey(key);
      else
        newRoot->children[1]->insertNewKey(key);
      
      root = newRoot;
    }
  }
}
// 2. DELETE A KEY
void BTree::deleteKey(int key){
    if (root == nullptr) {
        return;
    } 
    // find the node that contains the key to be deleted
    Node* node = root;
    int index = 0;
    while (index < node->nrKeys && key > node->keys[index]) {
        index++;
    }
    
    if (index < node->nrKeys && key == node->keys[index]) {
        // the key to be deleted is in this node
        
        if (node->leaf) {
            // If the node is a leaf node, simply remove the key from the node
            node->keys.erase(node->keys.begin() + index);
            node->nrKeys--;
        }
        else {
            // If the node is an internal node, replace the key with its predecessor and delete the predecessor
            Node* predecessor = node->children[index];
            while (!predecessor->leaf) {
                predecessor = predecessor->children[predecessor->nrKeys];
            }
            int predecessorKey = predecessor->keys[predecessor->nrKeys-1];
            deleteKey(predecessorKey);
            node->keys[index] = predecessorKey;
        }
    }
    else {
        // the key to be deleted is not in this node => find the child node where the key might be
        Node* child = node->children[index];
        if (child == nullptr) {
            return;
        }
        if (child->nrKeys == (Node::order-1)/2) {
            // The child node has the minimum number of keys, we need to rebalance or merge the nodes
            if (index > 0 && node->children[index-1]->nrKeys > (Node::order-1)/2) {
                // Case 1: The left sibling has more than the minimum number of keys, borrow a key from the left sibling
                Node* leftSibling = node->children[index-1];
                int borrowedKey = leftSibling->keys[leftSibling->nrKeys-1];
                Node* borrowedChild = leftSibling->children[leftSibling->nrKeys];
                leftSibling->keys.erase(leftSibling->keys.begin() + leftSibling->nrKeys-1);
                leftSibling->children.erase(leftSibling->children.begin() + leftSibling->nrKeys);
                leftSibling->nrKeys--;
                child->keys.insert(child->keys.begin(), borrowedKey);
                child->children.insert(child->children.begin(), borrowedChild);
                child->nrKeys++;
                node->keys[index-1] = leftSibling->keys[leftSibling->nrKeys-1];
            }
            else if (index < node->nrKeys && node->children[index+1]->nrKeys > (Node::order-1)/2) {
                // Case 2: The right sibling has more than the minimum number of keys, borrow a key from the right sibling
                Node* rightSibling = node->children[index+1];
                int borrowedKey = rightSibling->keys[0];
                Node* borrowedChild = rightSibling->children[0];
                rightSibling->keys.erase(rightSibling->keys.begin());
                rightSibling->children.erase(rightSibling->children.begin() + rightSibling->nrKeys);
                rightSibling->nrKeys--;
                child->keys.insert(child->keys.begin(), borrowedKey);
                child->children.insert(child->children.begin(), borrowedChild);
                child->nrKeys++;
                node->keys[index-1] = rightSibling->keys[rightSibling->nrKeys-1];
            }
        }
    }
}
// 3. SEARCH FOR A KEY
bool Node::search(int key){
    int i = 0;
    while(this->keys[i] < key && i < this->nrKeys)
        i++;
    if(this->keys[i] == key)
        return true;
    // if we reach a leaf node and don't find the key there, it means the key doesn't exist in the btree
    if(this->leaf)
        return false;
    return this->children[i]->search(key);

  }
bool BTree::search(int key){
  if (this->root == nullptr)
    return 0;
  else
    return this->root->search(key);
}
// 4. SEARCH BIGGEST NUMBER SMALLER THAN A GIVEN X KEY 
int Node::searchBiggestNrSmallerThan(int x){
    int i = 0;
    while(this->keys[i] <= x && i < this->nrKeys)
        i++;
    if(this->keys[i-1] <= x)
        return this->keys[i-1];
    if(this->leaf)
        return -1;
    return this->children[i]->searchBiggestNrSmallerThan(x);

  }
int BTree::searchBiggestNrSmallerThan(int x){
  if (this->root == nullptr)
    return 0;
  else
    return this->root->searchBiggestNrSmallerThan(x);
}
// 5. SEARCH SMALLEST NUMBER BIGGER THAN A GIVEN X KEY 
int Node::searchSmallestNrBiggerThan(int x){
    int i = 0;
    while(this->keys[i] < x && i < this->nrKeys)
        i++;
    if(this->keys[i] >= x)
        return this->keys[i];
    if(this->leaf)
        return -1;
    return this->children[i]->searchSmallestNrBiggerThan(x);

  }
int BTree::searchSmallestNrBiggerThan(int x){
  if (this->root == nullptr)
    return 0;
  else
    return this->root->searchSmallestNrBiggerThan(x);
}
// 6. TRAVERSE INTERVAL
void Node::traverseInterval(int x, int y){
    int i;
    for (i = 0; i < this->nrKeys; ++i){
        if (!this->leaf)
          children[i]->traverseInterval(x, y);
        if(x <= keys[i] && keys[i] <= y)
            g<<this->keys[i]<<" ";
    }
    if (!this->leaf) children[i]->traverseInterval(x, y);
}
void  BTree::traverseInterval(int x, int y){
  if (this->root != nullptr)
      this->root->traverseInterval(x, y);
}
// TRAVERSAL
void Node::traverse(){
  int i;
  // a node has n keys and n+1 children

  // traverse the first n children of the node and printing the keys of the node
  for (i = 0; i < this->nrKeys; ++i) {
      // if this node is not a leaf, then before printing its keys,
      // traverse the subtree rooted with child children[i].
      if (!this->leaf) 
        this->children[i]->traverse();

      cout<<this->keys[i]<<" ";
  }
  // traverse the last child
  if (!this->leaf)
      this->children[i]->traverse();
}

void  BTree::traverse(){
  if (this->root != nullptr)
      this->root->traverse();
}
int main(){
  int m;
  m = 10;
  Node::setOrder(m);
  BTree btree(m);

  int command, X, Y, Q;
  f>>Q;
  for(int i = 0; i < Q; i++){
    f>>command>>X;
    switch(command){
      case 1:{
        btree.insert(X);
        break;
      }
      case 2:{
        btree.deleteKey(X);
        break;
      }
      case 3:{
        g<<btree.search(X)<<endl;
        break;
      }
      case 4:{
        g<<btree.searchBiggestNrSmallerThan(X)<<endl;
        break;
      }
      case 5:{
        g<<btree.searchSmallestNrBiggerThan(X)<<endl;
        break;
      }
      case 6:{
        f>>Y;
        btree.traverseInterval(X,Y);
        g<<endl;
        break;
      }
      default:{
        break;
      }
    }
  }
  f.close();
  g.close();
  return 0;
}