// llist.cpp
// Erroll Abrahamian, CISP 430
// 03-10-2019

/*
Find(x)
– Locate the first instance of element x . Note: x is a value in the data structure, not an index number or address.

*/

#include <iostream>
#include <chrono>
using namespace std;

struct node
{
  int data;
  node *next;
};

class LinkList
{
private:
  node *head, *tail;

public:
  // constructor
  LinkList()
  {
    head = nullptr;
    tail = nullptr;
  }
  int nodeCount;

  // function prototypes
  void sayHi();
  void buildClear(int);
  void buildList(int);
  void printList();
  void addNode(int);
  void insertNode(int, int);
  void clearList();
};

int main()
{
  LinkList hw3;

  const int twen = 20;
  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  const int hlfM = 500000;
  const int oneM = 1000000;

  srand(time(0));

  hw3.sayHi();

  hw3.buildClear(10);
  hw3.buildClear(twen);
  hw3.buildClear(oneK);
  hw3.buildClear(tenK);
  hw3.buildClear(hunK);
  hw3.buildClear(hlfM);
  hw3.buildClear(oneM);
}

void LinkList::sayHi()
{
  cout << "Who's ready for some linked list fun?\n\n";
}

void LinkList::buildClear(int size)
{
  nodeCount = 0;
  buildList(size);
  insertNode(123, 0);
  nodeCount++;
  if (size <= 1000)
    printList();
  cout << "\nNodes: " << nodeCount << "\n";

  clearList();
}

void LinkList::buildList(int size)
{
  int randNum;

  for (int i = 0; i < size; i++)
  {
    randNum = (rand() % 1000);
    addNode(randNum);
    nodeCount++;
  }
}

void LinkList::printList()
{
  node *temp = new node;
  temp = head;
  while (temp != nullptr)
  {
    cout << temp -> data << "\t";
    temp = temp -> next;
  }
}

void LinkList::addNode(int value)
{
  node *temp = new node;
  temp->data = value;
  temp->next = nullptr;
  if (head == nullptr)
  {
    head = temp;
    tail = temp;
    temp = nullptr;
  }
  else
  {
    tail->next = temp;
    tail = temp;
  }
}

// Insert(x, y) – Add element x after element y in your data structure.
void LinkList::insertNode(int value, int pos)
{
  node *previous = new node;
  node *current = new node;
  node *temp = new node;

  // start at the beginning of the list
  current = head;

  for(int i = 1; i < pos; i++)
  {
    previous = current;
    current = current->next;
  }
  temp->data = value;
  previous->next = temp;
  temp->next = current;
}

void LinkList::clearList()
{
  head = nullptr;
  tail = nullptr;
  nodeCount = 0;
}
