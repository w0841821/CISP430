#include <iostream>
#include <chrono>
using namespace std;


class ListTest
{
private:
  int* dynArray = nullptr;
  int oldSize, newSize;

public:
  void newArray();
  void incArray(int);
  void delArray();
  void populate();
  void find();
  void add();
  void size();
  void print();
	void incPopDel(int);
};


int main()
{
  ListTest hw2;

  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
	const int oneM = 1000000;
	const int tenM = 10000000;

  srand(time(0));

	hw2.newArray();

  hw2.incPopDel(oneK);
	hw2.incPopDel(tenK);
	hw2.incPopDel(hunK);
	hw2.incPopDel(oneM);

  hw2.add();
  hw2.size();
  hw2.print();

	hw2.delArray();
}

void ListTest::newArray()
{
  dynArray = new int[10];
}

void ListTest::incPopDel(int size)
{
  incArray(size);
  populate();
  find();
}

void ListTest::incArray(int newSize)
{
  // newSize *= 2;

  int* tmpArr = nullptr;
  tmpArr = new int[newSize];

  for (int i = 0; i < oldSize; i++)
    tmpArr[i] = dynArray[i];

  delete [] dynArray;

  dynArray = tmpArr;

  tmpArr = nullptr;

	cout << "Array size is " << newSize << ".\n";
}

void ListTest::delArray()
{
  delete [] dynArray;
}

void ListTest::populate()
{
  for (int i = oldSize; i < newSize; i++)
    dynArray[i] = (rand() % 1000);
  oldSize = newSize;
}

void ListTest::find()
{
  int x = (rand() % 1000);
  int i;
  bool found = false;

  cout << "Searching for: " << x << endl;

  auto start = chrono::high_resolution_clock::now();

  for (i = 0; i < newSize; i++)
  {
    if (x == dynArray[i])
    {
      found = true;
      break;
    }
  }

  auto stop = chrono::high_resolution_clock::now();

  if (found)
    cout << "Random number " << x << " was found at element " << i << ".\n";
  if (!found)
    cout << "Random number " << x << " was not found.\n";

  auto timing = stop - start;

  cout << "The search took " << chrono::duration_cast<chrono::microseconds>(timing).count() << " microseconds\n\n";
}

void ListTest::add()
{

}

void ListTest::size()
{

}

void ListTest::print()
{

}
