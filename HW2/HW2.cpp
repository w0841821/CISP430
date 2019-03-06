// HW2.cpp
// Erroll Abrahamian, CISP 430
// 02-17-2019

#include <iostream>
#include <chrono>
using namespace std;

class ListTest
{
private:
  int* dynArray = nullptr;
  int oldSize, endSize;

public:
  // function prototypes
  void newArray();
  void incPop(int);
  void incArray(int);
  void populate();
  void find();
  void printSize();
  void printDump();
  void delArray();
};

int main()
{
  ListTest hw2;

  const int twen = 20;
  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  const int oneM = 1000000;

  srand(time(0));

  // loop three times to get some decent numbers
  for (int i = 0; i < 3; i++)
  {
    // start with our 10 element array
    hw2.newArray();

    // populate with random numbers
    hw2.populate();

    // print the size of the array
    hw2.printSize();

    // find a random number
    hw2.find();

    // print the values of the 10 elements
    hw2.printDump();

    // increase, populate, print size, find random number, and print elements
    // not printing elements above one thousand as it gets messy
    // see: if statement in incPop()
    hw2.incPop(twen);
    hw2.incPop(oneK);
    hw2.incPop(tenK);
    hw2.incPop(hunK);
    hw2.incPop(oneM);

    hw2.delArray();
  }
}

void ListTest::newArray()
{
  dynArray = new int[10];
  oldSize = 0;
  endSize = 10;
}

void ListTest::incPop(int size)
{
  incArray(size);
  populate();
  printSize();
  find();
  if (size <= 1000)
    printDump();
}

void ListTest::incArray(int size)
{
  // end size of the incremented array is equal to the passed variable
  endSize = size;

  int* tmpArr = nullptr;
  tmpArr = new int[size];

  // copy the elements up to the previous size (oldSize) of the array
  for (int i = 0; i < oldSize; i++)
    tmpArr[i] = dynArray[i];

  delArray();

  dynArray = tmpArr;

  tmpArr = nullptr;
}

void ListTest::populate()
{
  // start at oldSize, which is where the last array ended, so that we aren't overwriting previous elements
  for (int i = oldSize; i < endSize; i++)
    dynArray[i] = (rand() % 1000);

  // set oldSize to endSize
  // oldSize is used for copying elements to the temp array and for tracking in the previous loop
  oldSize = endSize;
}

void ListTest::find()
{
  // generate a random number to find
  int x = (rand() % 1000);
  int i;
  bool found = false;

  // start the timing for the search
  auto start = chrono::high_resolution_clock::now();

  for (i = 0; i < endSize; i++)
  {
    if (dynArray[i] == x)
    {
      found = true;
      break;
    }
  }

  auto stop = chrono::high_resolution_clock::now();
  // timing ends above

  if (found)
    cout << "Random number " << x << " was found at element " << i << ".\n";
  else
    cout << "Random number " << x << " was not found.\n";

  auto timing = stop - start;

  cout << "The search took " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n";
}

void ListTest::printSize()
{
  cout << "\nArray size is " << endSize << ".\n";
}

void ListTest::printDump()
{
  for (int i = 0; i < endSize; i++)
  {
    // print a line break if we're at the end...
    if (i == (endSize - 1))
      cout << dynArray[i] << "\n";

    // ...otherwise insert a comma
    else
      cout << dynArray[i] << ",";
  }
}

void ListTest::delArray()
{
  delete [] dynArray;
}

/*
           ns = nanosecond
           μs = microsecond
1 thousand ns = 1 μs
1 thousand μs = 0.001 seconds
 1 million μs = 1 second

element avg = total search time divided by number of elements searched

10- and 20-element arrays did not have their number found.

 Array size --  run 1 (element #       -- run 2 (element #       -- run 3 (element #
                          element avg)              element avg)              element avg)
         10    569 ns ( ---  56.90 ns)   125 ns ( ---  12.50 ns)    66 ns ( ---   6.60 ns)
         20    323 ns ( ---  16.15 ns)   164 ns ( ---   8.20 ns)    87 ns ( ---   4.35 ns)
       1000   1229 ns ( 117  10.50 ns)  1211 ns ( 267   4.54 ns)  1283 ns ( 532   2.41 ns)
      10000   5917 ns ( 700   8.45 ns)   352 ns (  67   5.25 ns)  7351 ns (2997   2.45 ns)
     100000   7957 ns ( 912   8.72 ns)   526 ns ( 132   3.98 ns)  2110 ns ( 873   2.42 ns)
    1000000   2327 ns ( 449   5.18 ns)  6529 ns (2663   2.45 ns)  1262 ns ( 553   2.28 ns)
*/
