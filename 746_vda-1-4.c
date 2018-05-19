#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

double swap(int *pen, int *pineapple, double penpineappleapplepen) {
  int applepen = *pen;
  *pen = *pineapple;
  *pineapple = applepen;
  penpineappleapplepen++;
  return penpineappleapplepen;
}

void heap_sort(int *a, int asize, double *aos, double *aoc) {
  int i, j = 0, boole = 0;
  double x = 0;
  while (1){
    boole = 0;
    for (i = 0; i < asize; ++i){
      if (i * 2 + 2 + j < asize){
        if (a[i + j] > a[i * 2 + 1 + j] || a[i + j] > a[i * 2 + 2 + j]){
          x = x + 3;
          if ((a[i * 2 + 1 + j] < a[i * 2 + 2 + j])){
            *aos = swap(&a[i + j], &a[i * 2 + 1 + j], *aos);
            boole = 1;
          }
          else{
            x++;
            if ((a[i * 2 + 2 + j] < a[i * 2 + 1 + j])){
              *aos = swap(&a[i + j], &a[i * 2 + 2 + j], *aos);
              boole = 1;
            }
          }
        }
      }
      else if (i * 2 + 1 + j < asize){
        x++;
        if ((a[i + j] > a[i * 2 + 1 + j])){
          *aos = swap(&a[i + j], &a[i * 2 + 1 + j], *aos);
          boole = 1;
        }
      }
    }
    if (boole == 0) j++;
    if (j + 2 == asize) break;
  }
  *aoc = (*aoc) + x;;
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
    heap_sort(head, amount, aos, aoc);
  }
  unsigned int t_end = clock();
  unsigned int t_total = t_end - t_start;

  cout << "\nResult:\n";
  cout << "Average amount of comparing = " << (*aoc) / 100 << ";\nAverage amount of swapping = " << (*aos) / 100
    << ";\nTime taken = " << t_total << " clock tick(s)." << "\n";
  system("pause");
}