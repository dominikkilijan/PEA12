#pragma once
#include "AdjacencyMatrix.h"
#include <vector>

class Dynamic
{
	public:
		Dynamic(int, int**);
		int tsp(int, int);
		long long int read_QPC();
		long double TSPDynamic();

	private:
		//int* bestPath;
		//int bestSum = 2147483647; // najwieksza dostepna wartosc
		//int* currentPath;
		vector<int> currentPath;
		vector<int> bestPath;

		int** dp;
		int N;
		int N2;
		int** matrix;
		int visitedAll;
};

