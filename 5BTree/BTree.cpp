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
  void preOrder(BinNode *tree);
  void burnTheTree(BinNode *&tree);
  void hitEnter();
};

int main()
{
  BinTree hw5;
  srand(time(0));
  sayHi();

  hw5.hitEnter();

  int numNodes[] = {10, oneK, tenK, fifK, otfK, tftK};
  int numTrees = calcTreeSize(numNodes);
  for (int i = 0; i < numTrees; i++) {
    hw5.growBurn(numNodes[i]);
  }

  return 0;
}

void sayHi()
{
  cout << "Are you ready to build a binary search tree, and then...\n";
  cout << "...search it?\n";
}

void BinTree::growBurn(int size)
{
	nodeNum = 0;
  growTree(size);

  nodeNum = 0;
  if (size == 10)
    preOrder(tree);
  burnTheTree(tree);
  hitEnter();
}

void BinTree::growTree(int size)
{
  int randNum;

  // start the timing for insertion
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++) {
    randNum = (rand() % 1000);
    insert(*&tree, randNum);
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;
  // stop the timing and calculate insertion time

  cout << "\nThere are " << treeSize(tree) << " nodes on the tree.\n";
  cout << "Time to grow the tree: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";//, with a top node of [" << tree->data << "].\n\n";

	randNum = (rand() % 1000);

  // start the timing for search
	start = chrono::high_resolution_clock::now();

	bool found = find(tree, randNum);

	stop = chrono::high_resolution_clock::now();
	timing = stop - start;
  // stop the timing and calculate search time

  // if the number was found...
	if (found) {
    cout << "Random number " << randNum << " found!\n";
		cout << "Time to find random number: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";
	// ...or wasn't found
	}
	else {
    cout << "Random number " << randNum << " not found!\n";
    cout << "Failed search took " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";
	}
}

bool BinTree::isEmpty(BinNode *tree)
{
  // return true if the tree is null aka empty
  return tree == nullptr;
}

bool BinTree::isLeaf(BinNode *tree)
{
  // return true if left and right nodes are empty aka this is a leaf
  return tree->left == nullptr && tree->right == nullptr;
}

bool BinTree::hasLeft(BinNode *tree)
{
  // return true if left node is not empty
  return tree->left != nullptr;
}

bool BinTree::hasRight(BinNode *tree)
{
  // return true if right node is not empty
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
  // if we have an empty tree, grow one!
  if (isEmpty(tree))
    tree = new BinNode{data, nullptr, nullptr};
  // ...otherwise don't grow one and just add to it
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

void BinTree::preOrder(BinNode *tree)
{
  if (tree)
  {
    // increment node number for printing/tracking
    nodeNum++;
    if (isLeaf(tree))
      cout << "to leaf "<< nodeNum << "... [" << tree->data << "]";
    else
    {
      if (nodeNum > 1)
        cout << "to node " << nodeNum << "... [" << tree->data << "]";
      else
        cout << "Node 1: [" << tree->data << "]";

      if (hasLeft(tree)) {
        cout << "\nGoing left... ";
        preOrder(tree->left);
      }
      if (hasRight(tree)) {
        cout << "\nGoing right.. ";
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

void BinTree::hitEnter()
{
  cout << "\n\nPress Enter to continue.\n";
  cin.ignore();
}

/*
Insertion and search both use pre-order
TREE SIZE  -- GROW TIME -- FIND TIME
       10       7918 ns           --
     1000     744759 ns      1572 ns
    10000    2985979 ns       408 ns
    50000   65528153 ns       311 ns
   125000  189714903 ns       294 ns
   250000  729750297 ns       631 ns
*/
