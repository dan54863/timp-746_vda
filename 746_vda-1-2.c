
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void shell_sort(int a[], int num, double *aos, double *aoc) 
{
  int tmp, i, j; 
  int s = num; 
  double x=0; 
  while (s>0) { 
    s /= 2; 
    for (i = 0; i<num - s; ++i) { 
      j = i; 
      while (j >= 0) { 
        x++; 
        if (a[j] > a[j + s]) { 
          tmp = a[j]; a[j] = a[j + s]; a[j + s] = tmp; 
          *aos=(*aos)+1; 
          j--; 
        } 
        else break; 
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
    shell_sort(head, amount, aos, aoc);
  }
  unsigned int t_end = clock();
  unsigned int t_total = t_end - t_start;

  cout << "\nResult:\n";
  cout << "Average amount of comparing = " << (*aoc) / 100 << ";\nAverage amount of swapping = " << (*aos) / 100
    << ";\nTime taken = " << t_total << " clock tick(s)." << "\n";
  system("pause");
}