// llist.cpp
// Erroll Abrahamian, CISP 430
// 03-03-2019

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

  // function prototypes
  void printList();
  void createNode(int);
};

int main()
{
  LinkList hw3;

  /*
  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  const int oneM = 1000000;
  */

  srand(time(0));

  int randNum = (rand() % 1000);

  hw3.createNode(randNum);
  hw3.printList();
}

void LinkList::printList()
{
  node *temp = new node;
  temp = head;
  while (temp != nullptr)
  {
    cout << temp -> data << "   ";
    temp = temp -> next;
  }
}

void LinkList::createNode(int value)
{
  node *temp = new node;
  temp -> data = value;
  temp -> next = nullptr;
  if (head == nullptr)
  {
    head = temp;
    tail = temp;
    temp = nullptr;
  }
  else
  {
    tail -> next = temp;
    tail = temp;
  }
}
