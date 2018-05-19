#include <stdlib.h>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
void functionCML(int s, double **a, int *min, double &min_sum) {//s - ������ �������, a - �������, min - ������ ��� �����, min_sum - ����� �������
																//��� ������ ���� ����� ����� ������������ ������������ �� �������������
	min_sum = -1; //��� ����� ���� �� ��������, �� ��� ������ ���� � -1 ������� �� �����
	int *c = new int[s - 1];//������ � ������������� � ������ �� 1 ������ ������� �������, �.�. ������ ������� � ��� ��� ������� ��� 1(0-������) �������
	for (int i = 0; i < s - 1; i++)//��������� ������������ ��� 1, 2,..., s
		c[i] = i + 1;
	bool is_next = true;//���������� ���������� ���������� ����� ���������� ����� ������������ ��� ���
						//� ����� � ������������ ����� ������ 2 ��������:
						//1) �������� ������������ �� �����������
						//2) ��������� ����� ������������
	do {
		//1 ��������
		double sum_cur = a[0][c[0]];//����������� ����� �������� ������� ��� ����� ����� 1 �������� � 1 ������� � ������������ 
		bool is_pass = true;//���������� ���������� ���������� ����� �� ������ �� ������� �������
		if (sum_cur != 0) {//�������� ����� �� ������ �� 1 ������� � 1 ������� � ������������ 
			for (int i = 0; i < s - 1; i++) {
				int weight = a[c[i]][i + 1 >= s - 1 ? 0 : c[i + 1]];//���������� ��� ����� ����� i ������� � ������������ � i+1(��� � 1 ���� ��� �������� ������� ������������) ������� � ������������ 
				if (weight == 0) {//�������� ��� ��� ����� ����� 0 (����� ���)
					is_pass = false;//��������� ��� ������ �� ������� ������� ������
					break;
				}
				sum_cur += weight;//���������� � ����� �������� ������� ��� ����� ����� ���������
			}
		}
		else {
			is_pass = false;//��������� ��� ������ �� ������� ������� ������
		}
		if (is_pass) {//��������� ����� �� ������ �� ������� �������
			if (sum_cur < min_sum || min_sum == -1) {
				min_sum = sum_cur;//������������ ����������� ����� �������� ������� �����
								  //������������ ������������ ������� ����� �������� �������� ������� �����
				min[0] = 0;
				for (int i = 1; i < s; i++) {
					min[i] = c[i - 1];
				}
			}
		}
		//2 ��������
		int j = s - 3;
		//��������� �� ������� ������ ������ ���� �� ������ �� ������ ��� ���� ������� ������� ����� ������ �����������
		while (j != -1 && c[j] >= c[j + 1])
			j--;
		if (j == -1) {
			//������ ������������ ���
			is_next = false;
		}
		else {
			//����� ��������� �� ������� ������ ������ ���� �� ������ �� ������� �����, ������� ������ ��� ���������� �� ���������� ����.
			int k = s - 2;
			while (c[j] >= c[k])
				k--;
			//������ ������� ��� ���������� ��������
			int b = c[j];
			c[j] = c[k];
			c[k] = b;
			//��������� ���������� ����� ������������������
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
		//���� �������� ����� ������ �� �������
		cout << "���� �� ������.";
	}
	functionCML(size, ar, mway, sumcml);
	printf("��������� ������ ����������� �����: \n");
	for (int i = 0; i < size; i++)//������� ������
	{
		printf("%d", mway[i]);
		printf(" ");
		fout << mway[i] << " ";
	}
	fout << "\n";
	printf("\n����� �������: %.0f\n", sumcml);//������� ����� �������
	fout.close();
	system("pause");
	getchar(); getchar();
	return 0;
}