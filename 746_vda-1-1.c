#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void comb_sort(int a[], int asize, double *aos, double *aoc)
{
  int tmp, i;
  int gap = asize;
  double x = 0;
  while (gap>1) {
      gap /= 1.2473309;
      if (gap<1) gap = 1;
      for (i = 0; i + gap<asize; ++i) {
          x++;
          if (a[i]>a[i + gap]) {
              tmp = a[i]; a[i] = a[i + gap]; a[i + gap] = tmp;
              *aos=(*aos)+1;
          }
      }
  }
  *aoc = (*aoc) + x;
}

int main(){
  int amount, i, j;
  int array[501], *head = array;
  double mholder1 = 0, mholder2 = 0;
  double *aoc = &mholder1, *aos = &mholder2;

  cout << "Amount of elements = ";
  cin >> amount;
  cout.setf(ios::fixed);
  cout.precision(0);

  srand(time(NULL));
  unsigned int t_start = clock();
  for (j = 0; j < 100; j++) {
    for (i = 0; i < amount; i++) {
      array[i] = 1 + rand() % ((10 + 1) - 1);
    }
    comb_sort(head, amount, aos, aoc);
  }
  unsigned int t_end = clock();
  unsigned int t_total = t_end - t_start;

  cout << "\nResult:\n";
  cout << "Average amount of comparing = " << (*aoc) / 100 << ";\nAverage amount of swapping = " << (*aos) / 100
    << ";\nTime taken = " << t_total << " clock tick(s)." << "\n";
  system("pause");
}