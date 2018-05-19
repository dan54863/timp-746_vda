#include <stdlib.h>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
void functionCML(int s, double **a, int *min, double &min_sum) {//s - размер матрицы, a - матрица, min - контур мин длины, min_sum - длина контура
																//для поиска всех путей будем использовать перестановки из комбинаторики
	min_sum = -1; //мин сумма пока не известна, но она больше нуля и -1 достичь не может
	int *c = new int[s - 1];//массив с перестановкой с длиной на 1 меньше размера матрицы, т.к. первая вершина у нас уже найдена это 1(0-индекс) вершина
	for (int i = 0; i < s - 1; i++)//начальная перестановка это 1, 2,..., s
		c[i] = i + 1;
	bool is_next = true;//логическая переменная означающая будем продолжать поиск перестановок или нет
						//в цикле с постусловием будем делать 2 действия:
						//1) проверка перестановки на мимальность
						//2) генерация новой перестановки
	do {
		//1 действие
		double sum_cur = a[0][c[0]];//присваиваем длине текущего контура вес ребра между 1 вершиной и 1 вершине в перестановки 
		bool is_pass = true;//логическая переменная означающая можно ли пройти по данному контуру
		if (sum_cur != 0) {//проверка можно ли пройти из 1 вершины в 1 вершину в перестановки 
			for (int i = 0; i < s - 1; i++) {
				int weight = a[c[i]][i + 1 >= s - 1 ? 0 : c[i + 1]];//записываем вес ребра между i вершины в перестановки и i+1(или в 1 если это последня вершина перестановки) вершину в перестановки 
				if (weight == 0) {//проверка что все ребра равен 0 (ребра нет)
					is_pass = false;//указываем что пройти по данному контуру нельзя
					break;
				}
				sum_cur += weight;//прибавляем к длине текущего контура вес ребра между вершинами
			}
		}
		else {
			is_pass = false;//указываем что пройти по данному контуру нельзя
		}
		if (is_pass) {//проверяем можно ли пройти по данному контуру
			if (sum_cur < min_sum || min_sum == -1) {
				min_sum = sum_cur;//присваивание минимальной длине значение текущей длины
								  //присваивание минимальному контуру длины значение текущего контура длины
				min[0] = 0;
				for (int i = 1; i < s; i++) {
					min[i] = c[i - 1];
				}
			}
		}
		//2 действие
		int j = s - 3;
		//двигаемся по массиву справа налево пока не дойдем до начала или пока текущий элемент будет меньше предыдущего
		while (j != -1 && c[j] >= c[j + 1])
			j--;
		if (j == -1) {
			//больше перестановок нет
			is_next = false;
		}
		else {
			//снова двигаемся по массиву справа налево пока не дойдем до первого числа, которое больше чем отмеченное на предыдущем шаге.
			int k = s - 2;
			while (c[j] >= c[k])
				k--;
			//меняем местами два полученных элемента
			int b = c[j];
			c[j] = c[k];
			c[k] = b;
			//сортируем оставшуюся часть последовательности
			int l = j + 1, r = s - 2;
			while (l < r) {
				int b = c[l];
				c[l] = c[r];
				c[r] = b;
				l++;
				r--;
			}
			is_next = true;
		}
	} while (is_next);
}

int main()
{
	system("chcp 1251");
	system("cls");
	system("color B0");
	int size = 7;
	int mway[7];
	int posversh[7];
	double sumcml;
	double **ar;
	ar = new double*[size];
	int prver = 1;
	for (int i = 0; i < size; i++)
		ar[i] = new double[size];
	ofstream fout("otvet.txt");
	ifstream in("table.txt");
	if (in.is_open())
	{
		int count = 0;
		int temp;
		while (!in.eof())
		{
			in >> temp;
			count++;
		}
		in.seekg(0, ios::beg);
		in.clear();
		int count_space = 0;
		char symbol;
		while (!in.eof())
		{
			in.get(symbol);
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;
		}
		in.seekg(0, ios::beg);
		in.clear();
		int n = count / (count_space + 1);
		int m = count_space + 1;
		for (int i = 0; i < n; i++) ar[i] = new double[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> ar[i][j];
		in.close();
	}
	else
	{
		//Если открытие файла прошло не успешно
		cout << "Файл не найден.";
	}
	functionCML(size, ar, mway, sumcml);
	printf("Найденный контур минимальной длины: \n");
	for (int i = 0; i < size; i++)//Выводим контур
	{
		printf("%d", mway[i]);
		printf(" ");
		fout << mway[i] << " ";
	}
	fout << "\n";
	printf("\nДлина контура: %.0f\n", sumcml);//Выводим длину контура
	fout.close();
	system("pause");
	getchar(); getchar();
	return 0;
}