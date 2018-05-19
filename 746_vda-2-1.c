#include <stdlib.h>
#include <fstream>
#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
void functionD(double **array, int razmer, int *minway, int *vershina, int &indPrev)
{
	int temp;
	int minx, metka; // здесь минимальный индекс вершины и минимальный путь
	int end = 5;
	system("chcp 1251");
	system("cls");
	for (int i = 0; i<razmer; i++)
	{
		minway[i] = 10000;
		vershina[i] = 1;
	}
	minway[0] = 0;
	do
	{
		minx = 10000;
		metka = 10000;
		for (int i = 0; i<razmer; i++)
		{
			if ((vershina[i] == 1) && (minway[i]<metka)) // сравниваем индекьсы
			{
				metka = minway[i];
				minx = i;
			}
		}
		if (minx != 10000)
		{
			for (int i = 0; i<razmer; i++)
			{
				if (array[minx][i] > 0)
				{
					temp = metka + array[minx][i];
					if (temp < minway[i])
					{
						minway[i] = temp;
					}
				}
			}
			vershina[minx] = 0;
		}
	} while (minx < 10000);// пока весь не заполнит
	vershina[0] = end + 1;
	int weight = minway[end];
	while (end > 0)
	{
		for (int i = 0; i<razmer; i++)
			if (array[end][i] != 0)
			{
				int temp = weight - array[end][i];
				if (temp == minway[i])
				{
					weight = temp;
					end = i;
					vershina[indPrev] = i + 1;
					indPrev++;
				}
			}
	}
}


int main()
{
	system("color B0");
	int size = 7;
	int mway[7];
	int posversh[7];
	double **ar;
	ar = new double*[size];
	int prver = 1;
	for (int i = 0; i < size; i++)
		ar[i] = new double[size];
	ofstream fout("result.txt");
	ifstream in("matrix.txt");
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

	functionD(ar, 7, mway, posversh, prver);
	printf("Найденное кратчайшее расстояние до вершин: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d", mway[i]);
		printf(" ");
		fout << mway[i] << " ";
	}
	fout << "\n";
	int w = 0;
	printf("\nКратчайший путь\n");
	for (int i = prver - 1; i >= 0; i--)
	{
		printf("%d", posversh[i]);
		printf(" ");
		w = w + posversh[i];
		fout << posversh[i] << " ";
	}
	printf("\nКратчайший путь: ");
	printf("%d", w);
	fout << endl << w;
	printf("\n");
	fout.close();
	system("pause");
	getchar(); getchar();
	return 0;
}