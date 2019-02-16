#include <iostream>
#include <chrono>
using namespace std;

class ListTest
{
private:
  int* dynArray = nullptr;
  int oldSize, endSize;

public:
  void newArray();
  void incPopFind(int);
  void incArray(int);
  void populate();
  void find();
  void delArray();
};

int main()
{
  ListTest hw2;

  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  const int oneM = 1000000;

  srand(time(0));

  for (int i = 0; i < 3; i++)
  {
    hw2.newArray();

    hw2.incPopFind(oneK);
    hw2.incPopFind(tenK);
    hw2.incPopFind(hunK);
    hw2.incPopFind(oneM);

    hw2.delArray();
  }
}

void ListTest::newArray()
{
  dynArray = new int[10];
  oldSize = 10;
}

void ListTest::incPopFind(int size)
{
  incArray(size);
  populate();
  find();
}

void ListTest::incArray(int size)
{
  endSize = size;

  int* tmpArr = nullptr;
  tmpArr = new int[size];

  for (int i = 0; i < oldSize; i++)
    tmpArr[i] = dynArray[i];

  delArray();

  dynArray = tmpArr;

  tmpArr = nullptr;

  cout << "Array size is " << size << ".\n";
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
  int x = (rand() % 1000);
  int i;
  bool found = false;

  cout << "Searching for: " << x << endl;

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

  if (found)
    cout << "Random number " << x << " was found at element " << i << ".\n";
  else
    cout << "Random number " << x << " was not found.\n";

  auto timing = stop - start;

  cout << "The search took " << chrono::duration_cast<chrono::nanoseconds>(timing).count() << " nanoseconds.\n\n";
}

void ListTest::delArray()
{
  delete [] dynArray;
}

/*
           μs = microsecond
1 thousand μs = 0.001 seconds
 1 million μs = 1 second

element avg = total search time divided by number of elements searched

 Array size --  run 1 (element #       -- run 2 (element #       -- run 3 (element #
                          element avg)              element avg)              element avg)
       1000   7979 μs ( 911  8.759 μs)  1176 μs ( 779  1.509 μs)  1480 μs (1000  1.480 μs)
      10000   4545 μs ( 527  8.624 μs)  2057 μs (1349  1.525 μs)    47 μs (  13  3.615 μs)
     100000    598 μs ( 389  1.537 μs)   236 μs ( 142  1.662 μs)   309 μs ( 178  1.736 μs)
    1000000   3836 μs (2437  1.574 μs)   925 μs ( 582  1.589 μs)   699 μs ( 428  1.633 μs)
*/
