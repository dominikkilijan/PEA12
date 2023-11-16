#pragma once
#include "AdjacencyMatrix.h"

class Dynamic
{
	public:
		Dynamic(int, int**);
		long long int read_QPC();
		long double TSPDynamic();

	private:
		int* bestPath;
		int bestSum = 2147483647; // najwieksza dostepna wartosc
		int* currentPath;

		int N;
		int** matrix;
};

