#include <iostream>
#include <chrono>
using namespace std;

class ArrayFun{
private:
  int* dynArray = nullptr;
  int arraySize;
public:
  void newArray();
  void incArray(int);
  void addElement();

};

int main() {
  ArrayFun hw1;

  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;

  hw1.newArray();

  hw1.incArray(oneK);
//  hw1.incArray(tenK);
 // hw1.incArray(hunK);
}

void ArrayFun::newArray()
{
  dynArray = new int[1];
	arraySize = 0;
}

void ArrayFun::incArray(int newSize)
{
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < newSize; i++)
    addElement();

  auto stop = chrono::high_resolution_clock::now();
}

void ArrayFun::addElement()
{
  int* tmpSize = nullptr;
	arraySize += 1;
  tmpSize = new int[arraySize + 1];
	cout << "Size: " << arraySize << "\n";

  for (int i = 0; i < (arraySize + 1); i++)
    tmpSize[i] = dynArray[i];

  delete [] dynArray;

  dynArray = tmpSize;
  tmpSize = nullptr;
}
