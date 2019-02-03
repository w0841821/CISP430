#include <iostream>
#include <chrono>
using namespace std;

class ArrayFun{
private:
  const int oneK = 1000;
  const int tenK = 10000;
  const int hunK = 100000;
  int* dynArray = nullptr;
  int arraySize;
public:
  //void oneKArray();
  //void tenKArray();
  //void hunKArray();
  void newArray();
  void incArray(int*);
  void addElement();

};

int main() {
  ArrayFun hw1;

  /*

  for (int i = 0; i < 200000; i++)
            cout << "OMG ";


    auto timing = stop - start;
    // cout << chrono::milliseconds(timing).count() << " milliseconds\n"
    cout << "\n\n" << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " milli\n";
    return 0;

    */

  hw1.newArray();

  hw1.incArray(&oneK);
  hw1.incArray(&tenK);
  hw1.incArray(&hunK);
}

void ArrayFun::newArray()
{
  dynArray = new int[1];
}

void ArrayFun::incArray(int* newSize)
{
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < *newSize; i++)
    addElement();

  auto stop = chrono::high_resolution_clock::now();
}

void ArrayFun::addElement()
{
  int* tmpSize = nullptr;
  tmpSize = new int[dynArray + 1];

  for (int i = 0; i < (dynArray.size() + 1); i++)
    tmpSize[i] = dynArray[i];

  delete [] dynArray;

  dynArray = tmpSize;
  tmpSize = nullptr;
}
