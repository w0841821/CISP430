// llist.cpp
// Erroll Abrahamian, CISP 430
// 03-10-2019

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
	bool inserted;

  // function prototypes
  void sayHi();
  void buildClear(int);
  void buildList(int);
	void buildRandom(int);
  void find();
  void printList();
  void printSize();
  void addNode(int);
  void insertNode(int, int);
  void clearList();
  void hitEnter();
};

int main()
{
  LinkList hw3;

  const int twen = 20;
  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  const int hlfM = 500000;

  srand(time(0));

  hw3.sayHi();

  hw3.buildClear(10);
  hw3.buildClear(twen);
  hw3.buildClear(oneK);
  hw3.buildClear(tenK);
  hw3.buildClear(hunK);
  hw3.buildClear(hlfM);
}

// program greeting
void LinkList::sayHi()
{
  cout << "Who's ready for some linked list fun?\nWe'll be building lists up to one million nodes, sequentially and randomly!\n";
}

void LinkList::buildClear(int size)
{
  nodeCount = 0;

  // build the list
  buildList(size);

  // find a random number
  find();

	// only print the elements for lists up to 1000 elements
  if (size <= 1000)
    printList();

  // clear head/tail pointers and node counter
	clearList();
  hitEnter();

  // build the random list
  buildRandom(size);
  find();

  if (size <= 1000)
    printList();

  clearList();
  hitEnter();
}

void LinkList::buildList(int size)
{
  int randNum;

  // start timing
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++)
  {
    randNum = (rand() % 1000);
    addNode(randNum);
    nodeCount++;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;
  // stop timing

  // print the size of the list
  printSize();

  cout << "Build time: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";
}

void LinkList::buildRandom(int size)
{
	int randNum, randPos;

  // start timing
  auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < size; i++)
  {
    // generate a random number
    randNum = (rand() % 1000);

    // loop until the random number is able to be inserted at a random position
    do {
      randPos = (rand() % size);
      insertNode(randNum, randPos);
    } while(!inserted);

    // increase node counter
    nodeCount++;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  // stop timing, and print size of the list
	printSize();

  cout << "Build time: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";
}

void LinkList::find()
{
  // the random number we'll attempt to find
  int findRand = (rand() % 1000);
  bool foundRand = false;
  int listEle = 0;

  node *temp;
  temp = head;

  auto start = chrono::high_resolution_clock::now();

  while (temp != nullptr)
  {
    if (temp->data == findRand)
    {
      foundRand = true;
      break;
    }
    temp = temp->next;
    listEle++;
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  cout << "Search time: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";

  if (foundRand)
    cout << "Random number " << findRand << " found at element " << listEle << ".\n";
  else
    cout << "Random number " << findRand << " was not found.\n";
}

void LinkList::printList()
{
  node *temp = new node;
	temp = head;
  while (temp != nullptr)
  {
    cout << temp->data << "\t";
    temp = temp->next;
  }
  cout << "\n\n";
}

void LinkList::printSize()
{
  cout << "\n\nNodes: " << nodeCount << "\n";
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

void LinkList::insertNode(int value, int pos)
{
  node *previous = new node;
  node *current = new node;
  node *temp = new node;

  // start at the beginning of the list
  current = head;
	inserted = false;
	temp->data = value;

  // if we're trying to enter a node at a position we haven't reached yet...
  if (pos > nodeCount)
  {
    cout << "Position " << pos << " doesn't exist yet! ";
    return;
  }

  // ...or if there is no head to the list yet...
  else if (pos == 0 && head == nullptr)
	{
		head = temp;
		tail = temp;
		temp = nullptr;
    inserted = true;
	}

  // ...or if there is a head and we need position 0...
  else if (pos == 0)
  {
    head = temp;
    head->next = current;
    head->data = value;
    temp = nullptr;
    inserted = true;
  }

  // ...or anywhere else in the list
	else
	{
		for (int i = 0; i < pos; i++)
  	{
    	previous = current;
		  current = current->next;
  	}
		temp->data = value;
  	previous->next = temp;
  	temp->next = current;
		temp = nullptr;
		inserted = true;
	}
}

void LinkList::clearList()
{
  head = nullptr;
  tail = nullptr;
  nodeCount = 0;
}

void LinkList::hitEnter()
{
  cout << "Press Enter to continue.";
  cin.ignore();
}

/*
          ns = nanosecond
1 million ns = 0.001 seconds (1 millisecond)

LIST SIZE     ||     BUILD TIME || ELEMENT
                                      SEARCH TIME
SEQUENTIAL 10 ||        3499 ns ||  ---    483 ns
RANDOM        ||       48992 ns ||  ---    574 ns

SEQ        20 ||        6985 ns ||  ---    521 ns
RAND          ||       95476 ns ||  ---    519 ns

SEQ      1000 ||      162042 ns ||  454   6805 ns
RAND          ||    51448926 ns ||  ---  14795 ns
                      51.449 ms

SEQ     10000 ||     1537753 ns ||  493   9422 ns
                       1.538 ms
RAND          ||   447925489 ns || 5672  63872 ns
                     447.925 ms

SEQ    100000 ||    15916640 ns || 1467  19247 ns
                      15.917 ms
RAND          || 53047208966 ns ||  490  10067 ns
                     53 seconds

SEQ    500000 ||    44506134 ns ||  860   3495 ns
                      44.506 ms
RAND          || I quit after fifteen minutes
*/
