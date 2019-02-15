#include <iostream>
#include <chrono>
using namespace std;

<<<<<<< HEAD

=======
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5
class ListTest
{
private:
  int* dynArray = nullptr;
  int oldSize, newSize;
<<<<<<< HEAD

public:
  void newArray();
  void incArray(int);
=======
public:
  void newArray();
  void incArray();
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5
  void delArray();
  void populate();
  void find();
  void add();
  void size();
  void print();
<<<<<<< HEAD
	void incPopDel(int);
};

=======
};

template <class T>
T NewIncPopDel (T size)
{
  ListTest.newArray();
  ListTest.incArray(size);
  ListTest.populate();
  ListTest.delArray();
}
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5

int main()
{
  ListTest hw2;

  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
	const int oneM = 1000000;
	const int tenM = 10000000;

  srand(time(0));

<<<<<<< HEAD
	hw2.newArray();

  hw2.incPopDel(oneK);
	hw2.incPopDel(tenK);
	hw2.incPopDel(hunK);
	hw2.incPopDel(oneM);

  hw2.add();
  hw2.size();
  hw2.print();

	hw2.delArray();
=======
  //hw2.newArray();
  NewIncPopDel<int oneK>;
  hw2.populate();
  hw2.find();
  hw2.add();
  hw2.size();
  hw2.print();
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5
}

void ListTest::newArray()
{
<<<<<<< HEAD
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
=======
  oldSize = 10;
  newSize = oldSize;
  dynArray = new int[10];
}

void ListTest::incArray()
{
  newSize *= 2;
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5

  int* tmpArr = nullptr;
  tmpArr = new int[newSize];

  for (int i = 0; i < oldSize; i++)
    tmpArr[i] = dynArray[i];

  delete [] dynArray;

  dynArray = tmpArr;

  tmpArr = nullptr;
<<<<<<< HEAD

	cout << "Array size is " << newSize << ".\n";
=======
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5
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

<<<<<<< HEAD
  cout << "The search took " << chrono::duration_cast<chrono::microseconds>(timing).count() << " microseconds\n\n";
=======
  cout << "\nThe search took " << chrono::duration_cast<chrono::microseconds>(timing).count() << " microseconds\n";
>>>>>>> 3944eb3f2c21019df43dffaedbe017382b0e6bd5
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
