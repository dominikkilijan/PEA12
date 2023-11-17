#include "Dynamic.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
Dynamic::Dynamic(int n, int** m)
{
	N = n;
	matrix = m;
	visitedAll = (1 << N) - 1;
	//vector<int> currentPath;
	currentPath.reserve(N);

	//vector<int> bestPath;
	bestPath.reserve(N);
	N2 = (1 << N);
	dp = new int* [N2];
	for (int i = 0; i < N2; i++)
	{
		dp[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			dp[i][j] = -1;
		}
	}
	
}
//------------------------------------------------------------------------------------------------------------------------------------
int Dynamic::tsp(int mask, int pos)
{
	int currentSum;

	if (mask == visitedAll) // jesli odwiedzono wszystkie wierzcholki
		return matrix[pos][0];

	if (dp[mask][pos] != -1) // ten przypadek juz byl liczony
		return dp[mask][pos];

	int bestSum = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		if ((mask & (1 << i)) == 0) // sprawdzenie czy wierzochlek byl juz odwiedzony
		{
			//currentPath.emplace_back(i);
			currentSum = matrix[pos][i] + tsp(mask|(1<<i), i); // odleglosc z obecnego punktu do nastepnego + kolejne odcinki
			bestSum = min(bestSum, currentSum);
		}
	}
	/*if (bestSum > currentSum)
	{
		bestSum = currentSum;
		bestPath.clear();
		for (int i = 0; i < currentPath.size(); i++)
		{
			bestPath.emplace_back(currentPath[i]);
		}
		currentPath.clear();
	}*/

	return dp[mask][pos] = bestSum;
}
//------------------------------------------------------------------------------------------------------------------------------------
long double Dynamic::TSPDynamic()
{
	
	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// rozpoczecie pomiaru czasu
	start = read_QPC(); 

	// algorytm
	cout << tsp(1, 0) << "\n";
	// koniec algorytmu

	// koniec pomiaru czasu
	elapsed = read_QPC() - start; 
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku
	/*cout << "Miejsce na wynik\n";
	for (int i = 0; i < bestPath.size(); i++)
	{
		cout << bestPath[i] << " ";
	}
	cout << endl;*/

	cout << "dp:\n";
	for (int i = 0; i < N2; i++)
	{
		dp[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}

	// czyszczenie
	cout << "Zwalnianie pamieci\n";
	for (int i = 0; i < N2; i++)
	{
		delete[] dp[i];
	}
	delete[] dp;
	dp = nullptr;

	return timeElapsed;
}
//------------------------------------------------------------------------------------------------------------------------------------
// metoda do precyzyjnego pomiaru czasu
long long int Dynamic::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//------------------------------------------------------------------------------------------------------------------------------------