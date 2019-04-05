// BTree.cpp
// Erroll Abrahamian, CISP 430
// 04-07-2019

#include <iostream>
#include <chrono>
using namespace std;

const int oneK = 1000;
const int tenK = 10000;
const int fifK = 50000;
const int otfK = 125000;
const int tftK = 250000;

void sayHi();

template <typename T, int N>
static int calcTreeSize(T (&arr1)[N])
{
  return N;
}

struct BinNode
{
  int data;
  BinNode *left, *right;
};

class BinTree
{
private:
  BinNode *tree;
  int nodeNum;

public:
  BinTree()
  {
    tree = nullptr;
  }

  void growBurn(int size);
  void growTree(int size);
  bool isEmpty(BinNode *tree);
  bool isLeaf(BinNode *tree);
  bool hasLeft(BinNode *tree);
  bool hasRight(BinNode *tree);
  int treeSize(BinNode *tree);
  void insert(BinNode *&tree, int data);
  bool find(BinNode *tree, int data);
  void inOrder(BinNode *tree);
  void preOrder(BinNode *tree);
  void burnTheTree(BinNode *&tree);
};

int main()
{
  srand(time(0));
  sayHi();

  BinTree hw5;

  int numNodes[] = {10, oneK, tenK, fifK, otfK, tftK};
  int numTrees = calcTreeSize(numNodes);
  for (int i = 0; i < numTrees; i++) {
    hw5.growBurn(numNodes[i]);
  }

  return 0;
}

void sayHi()
{
  cout << "Hi!!\n\n";
}

void BinTree::growBurn(int size)
{
  growTree(size);
  // inOrder(tree);
  nodeNum = 0;
  if (size <= 1000)
    preOrder(tree);
  burnTheTree(tree);
}

void BinTree::growTree(int size)
{
  int randNum;

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++) {
    randNum = (rand() % 1000);
    insert(*&tree, randNum);
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  cout << "There are " << treeSize(tree) << " nodes on the tree.\n";
  cout << "Time to grow the tree: " << chrono::duration_cast<chrono::microseconds>(timing).count() << " microseconds.\n\n";//, with a top node of [" << tree->data << "].\n\n";
}

bool BinTree::isEmpty(BinNode *tree)
{
  return tree == nullptr;
}

bool BinTree::isLeaf(BinNode *tree)
{
  return tree->left == nullptr && tree->right == nullptr;
}

bool BinTree::hasLeft(BinNode *tree)
{
  return tree->left != nullptr;
}

bool BinTree::hasRight(BinNode *tree)
{
  return tree->right != nullptr;
}

int BinTree::treeSize(BinNode *tree)
{
  if (!isEmpty(tree))
    return 1 + treeSize(tree->left) + treeSize(tree->right);
  else
    return 0;
}

void BinTree::insert(BinNode *&tree, int data)
{
  if (isEmpty(tree))
    tree = new BinNode{data, nullptr, nullptr};
  else
  {
    if (data < tree->data)
      insert(tree->left, data);
    else
      insert(tree->right, data);
  }
}

bool BinTree::find(BinNode *tree, int data)
{
  if (isEmpty(tree))
    return false;
  else
  {
    if (data == tree->data)
      return true;
    else if (data < tree->data)
      return find(tree->left, data);
    else
      return find(tree->right, data);
  }
}

void BinTree::inOrder(BinNode *tree)
{
  if (tree)
  {
    inOrder(tree->left);
    cout << "[" << tree->data << "]";
    inOrder(tree->right);
  }
}

void BinTree::preOrder(BinNode *tree)
{
  /*
  if (tree)
  {
    cout << "[" << tree->data << "]";
    cout << "\nGoing left.... ";
    preOrder(tree->left);
    cout << "\nGoing right... ";
    preOrder(tree->right);
  }
  */

  if (tree)
  {
    nodeNum++;
    if (isLeaf(tree))
    {
      cout << "to leaf "<< nodeNum << "... [" << tree->data << "]";
    }
    else
    {
      if (nodeNum > 1) {
        cout << "to node " << nodeNum << "... [" << tree->data << "]";
        // cout << "node " << nodeNum << "->" << nodeNum + 1 << "... [" << tree->data << "]";
      }
      else
      {
        cout << "Node 1: [" << tree->data << "]";
      }

      if (hasLeft(tree)) {
        cout << "\nGoing left... ";//" to node " << nodeNum << "... ";
      //  nodeNum++;
        preOrder(tree->left);
      }
      if (hasRight(tree)) {
        cout << "\nGoing right.. ";//to node " << nodeNum << "... ";
      //  nodeNum++;
        preOrder(tree->right);
      }
    }
  }
}

void BinTree::burnTheTree(BinNode *&tree)
{
  if (!isEmpty(tree))
  {
    burnTheTree(tree->left);
    burnTheTree(tree->right);
    delete tree;
    tree = nullptr;
  }
}
