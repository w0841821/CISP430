// SnQ.cpp
// Erroll Abrahamian, CISP 430
// 03-17-2019

#include <iostream>
#include <chrono>
using namespace std;

const int oneK = 1000;
const int tenK = 10000;
const int fifK = 50000;
const int otfK = 125000;
const int tftK = 250000;

struct plate
{
  int data;
  plate *below;
};

struct person
{
  int data;
  person *front, *behind;
};

class Stack
{
  // friend class Queue;
private:
  int stackSize = 0;
  plate *topPlate, *bottomPlate;

public:
  friend class Queue;
  // constructor
  Stack()
  {
    topPlate = nullptr;
    bottomPlate = nullptr;
  }
  // function prototypes
  template <typename T, int N>
  static int size(T (&arr1)[N])
  {
     return N;
  }
  void sayHi();
  void main();
  void stackPlates(int);
  void push(int);
  void popAll();
  void pop();
  void printStack();
  void printSize();
  static void hitEnter();
};

class Queue
{
private:
  int queueSize = 0;
  person *frontPerson, *backPerson;

public:
  // constructor
  Queue()
  {
    frontPerson = nullptr;
    backPerson = nullptr;
  }
  // function prototypes
  void main();
  void formALine(int);
  void goStand(int);
  void leaveTheLine();
  void leave();
  void printLine();
  void printSize();
  // friend void Stack::hitEnter();
};

int main()
{
  Stack hw4Stack;
  Queue hw4Queue;
  srand(time(0));

  hw4Stack.sayHi();

  hw4Stack.main();
  hw4Queue.main();

  return 0;
}

void Stack::sayHi()
{
  system("clear");
  cout << "Hello! Are you ready to stack some plates?\n";
  cout << "...and maybe break some?\n\n";
}

void Stack::main()
{
  // an array of the different sizes of plates to be stacked
  int numPlates[] = {oneK, tenK, fifK, otfK, tftK};

  // using the template function to determine how many stacks
  int numStacks = size(numPlates);

  int totalPlates = 0;

  for (int i = 0; i < numStacks; i++)
  {
    stackPlates(numPlates[i]);
    popAll();
    totalPlates += numPlates[i];
  }

  cout << "Wow, you stacked and broke " << totalPlates << " plates!\n";
  cout << "...That was probably expensive.\n\n";
}

void Stack::stackPlates(int size)
{
  int randNum;

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++)
  {
    randNum = (rand() % 1000);
    push(randNum);
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  if (size <= 1000)
    printStack();

  printSize();

  cout << "Time to stack: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";

  hitEnter();
}

void Stack::push(int value)
{
  plate *temp = new plate;
  temp->data = value;
  temp->below = nullptr;

  if (bottomPlate == nullptr)
  {
    topPlate = temp;
    bottomPlate = temp;
    temp = nullptr;
  }
  else
  {
    temp->below = topPlate;
    topPlate = temp;
    temp = nullptr;
  }
  // cout << "Stacking " << topPlate->data << "... ";
  stackSize++;
}

void Stack::popAll()
{
  int stackCount = stackSize;

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < stackCount; i++)
    pop();

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  printSize();

  cout << "Time to break: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";

  hitEnter();
}

void Stack::pop()
{
  // cout << "Breaking " << topPlate->data << "... ";

  plate *temp;
  temp = topPlate;
  topPlate = temp->below;
  temp = nullptr;
  stackSize--;
}

void Stack::printStack()
{
  plate *temp;
  temp = topPlate;
  while (temp != nullptr)
  {
    cout << temp->data << "\t";
    temp = temp->below;
  }
  cout << "\n";
}

void Stack::printSize()
{
  if (stackSize == 0)
    cout << "There are no plates :(\n";
  else
    cout << "There are " << stackSize << " \"plates\" in the stack.\n";
}

void Stack::hitEnter()
{
  cout << "Press Enter to continue.\n";
  cin.ignore();
}

void Queue::main()
{
  int numPeople[] = {oneK, tenK, fifK, otfK, tftK};
  int numLines = Stack::size(numPeople);
  int totalPeople = 0;

  for (int i = 0; i < numLines; i++)
  {
    formALine(numPeople[i]);
    leaveTheLine();
    totalPeople += numPeople[i];
  }

  cout << "Phew, you processed " << totalPeople << " people!\n";
  cout << "You must be pretty tired.\n\n";
}

void Queue::formALine(int size)
{
  int randNum;

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++)
  {
    randNum = (rand() % 1000);
    goStand(randNum);
  }

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  if (size <= 1000)
    printLine();

  printSize();

  cout << "Time to get in line: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";

  Stack::hitEnter();
}

void Queue::goStand(int value)
{
  person *temp = new person;
  temp->data = value;
  temp->front = nullptr;
  temp->behind = nullptr;

  if (frontPerson == nullptr)
  {
    frontPerson = temp;
    backPerson = frontPerson;
    temp = nullptr;
  }
  else
  {
    backPerson->behind = temp;
    temp->front = backPerson;
    backPerson = temp;
    temp = nullptr;
  }

  queueSize++;
}

void Queue::leaveTheLine()
{
  int queueLength = queueSize;

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < queueLength; i++)
    leave();

  auto stop = chrono::high_resolution_clock::now();
  auto timing = stop - start;

  printSize();

  cout << "Time to leave the line: " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";

  Stack::hitEnter();
}

void Queue::leave()
{
  person *temp;
  temp = frontPerson;
  frontPerson = temp->behind;
  temp = nullptr;
  queueSize--;
}

void Queue::printLine()
{
  person *temp;
  temp = frontPerson;
  while (temp != nullptr)
  {
    cout << temp->data << "\t";
    temp = temp->behind;
  }
  cout << "\n";
}

void Queue::printSize()
{
  if (queueSize == 0)
    cout << "There is no one in line :(\n";
  else
    cout << "There are " << queueSize << " \"people\" in the queue.\n";
}

/*
 STACK  -- "build" time  --    pop time
  1000  --    149705 ns  --    18380 ns
 10000  --   1619811 ns  --   150341 ns
 50000  --   1382848 ns  --  1008283 ns
125000  --   3610013 ns  --  2345555 ns
250000  --  33832911 ns  --  1606488 ns

 QUEUE
  1000  --    243896 ns  --    20375 ns
 10000  --   1639568 ns  --    53793 ns
 50000  --   1427173 ns  --   860317 ns
125000  --  20004577 ns  --  2113405 ns
250000  --  10394999 ns  --  5242772 ns
*/
