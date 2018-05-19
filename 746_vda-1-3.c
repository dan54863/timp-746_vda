#include "stdafx.h" 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

void hoar_sort(int *a, int lborder, int rborder, double *aos, double *aoc){ 
  int tmp; 
  double s = 0; 
  int i = lborder, j = rborder, x = a[(lborder + rborder) / 2]; 
  do { 
    while (a[i]<x)i++; 
    while (a[j]>x)j--; 
    if (i <= j) { 
        s++; 
        if (a[i] > a[j]) { tmp = a[i]; a[i] = a[j]; a[j] = tmp; (*aos)++; } 
        i++; 
        j--; 
    } 
  } while (i <= j); 
  *aoc = (*aoc) + s; 
  if (i<rborder) hoar_sort(a, i, rborder, aos, aoc); 
  if (j>lborder) hoar_sort(a, lborder, j, aos, aoc); 
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
    hoar_sort(head, 0, amount - 1, aos, aoc);
  }
  unsigned int t_end = clock();
  unsigned int t_total = t_end - t_start;

  cout << "\nResult:\n";
  cout << "Average amount of comparing = " << (*aoc) / 100 << ";\nAverage amount of swapping = " << (*aos) / 100
    << ";\nTime taken = " << t_total << " clock tick(s)." << "\n";
  system("pause");
}