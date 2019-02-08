#include <iostream>
#include <chrono>
using namespace std;

class ArrayFun{
private:
  int* dynArray = nullptr;
  int arraySize;
public:
  // function prototypes
  void sayHi();
  void newArray();
  void incArray(int);
  void addElement();
	void delArray();
};

int main() {
  ArrayFun hw1;

  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
	const int oneM = 1000000;
	const int tenM = 10000000;

  hw1.sayHi();

  for (int i = 0; i < 3; i++)
	{
		hw1.newArray();
		// increment array to one thousand
		hw1.incArray(oneK);
		hw1.delArray();
	}

  for (int i = 0; i < 3; i++)
	{
		hw1.newArray();
  	// increment array to ten thousand
		hw1.incArray(tenK);
		hw1.delArray();
	}

	for (int i = 0; i < 3; i++)
	{
		hw1.newArray();
  	// increment array to one hundred thousand
		hw1.incArray(hunK);
		hw1.delArray();
	}

	for (int i = 0; i < 3; i++)
	{
		hw1.newArray();
  	// increment array to one million
		hw1.incArray(oneM);
		hw1.delArray();
	}

	for (int i = 0; i < 3; i++)
	{
		hw1.newArray();
		// increment array to ten million
		hw1.incArray(tenM);
		hw1.delArray();
	}
}

void ArrayFun::sayHi()
{
  cout << "Hello! Today we are performing some Array Tests.\n";
  cout << "We'll be timing how long it takes to increment an array from 1 to 1000,\n";
  cout << "1 to 10,000, 1 to 100,000, 1 to 1 million, and 1 to 10 million.\n";
  cout << "Also, how long it takes, on average, to increment each element.\n\n";
  cout << "Press Enter to continue.";
  cin.get();
}

void ArrayFun::newArray()
{
  dynArray = new int[1];
	arraySize = 0;
}

void ArrayFun::incArray(int newSize)
{
  // start the timer
	auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < newSize; i++)
		addElement();

	auto stop = chrono::high_resolution_clock::now();

  // stop the timer above, then calculate the difference
  auto timing = stop - start;

  // output array size to see where we're at
  cout << "\nFinal arraySize: " << arraySize << "\n";

  // print time in microseconds since the smaller arrays are very quick...
	cout << "\n" << chrono::duration_cast<chrono::microseconds>(timing).count() << " microseconds\n";

  // ...but also print in milliseconds since some take longer...
	cout << chrono::duration_cast<chrono::milliseconds>(timing).count() << " milliseconds\n\n";

  // ...and for fun, print the average time it takes to increase each element of the array
  cout << "Average time per element: " << (chrono::duration_cast<chrono::microseconds>(timing).count() / arraySize) << " microseconds.\n";
	cout << "----------\n";
}

void ArrayFun::addElement()
{
  // increase element counter
  arraySize += 1;
	int* tmpSize = nullptr;
  tmpSize = new int[arraySize];

  delArray();

  dynArray = tmpSize;
  tmpSize = nullptr;
}

void ArrayFun::delArray()
{
  // not really necessary to put in a function, but provides symmetry with newArray
	delete [] dynArray;
}

/*
     μs = microsecond
1000 μs = 1 millisecond

Array size --   run1 --   run2 --   run3 --   run avg -- element avg
      1000    117 μs     74 μs     74 μs     88.33 μs    0.08833 μs
     10000    848 μs    764 μs    763 μs    791.67 μs    0.07917 μs
    100000    145 ms     26 ms     28 ms    199.00 ms    0.00199 ms
   1000000   2302 ms    112 ms    120 ms    844.67 ms    0.00084 ms
  10000000  31537 ms  11298 ms  11149 ms  17994.67 ms    0.00180 ms
*/
