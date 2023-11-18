#include "Dynamic.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <bitset>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
Dynamic::Dynamic(int n, int** m)
{
	N = n;
	matrix = m;
	visitedAll = (1 << N) - 1;
	//vector<int> currentPath;
	//currentPath.reserve(N);

	//vector<int> bestPath;
	//bestPath.reserve(N);
	N2 = (1 << N);
	dp = new int* [N2];
	path = new int* [N2];
	for (int i = 0; i < N2; i++)
	{
		dp[i] = new int[N];
		path[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			dp[i][j] = -1;
			path[i][j] = -1;
		}
	}
	
}
//------------------------------------------------------------------------------------------------------------------------------------
int Dynamic::tsp(int mask, int pos)
{
	int currentSum = 0;


	//printdp();

	if (mask == visitedAll) // jesli odwiedzono wszystkie wierzcholki
		return matrix[pos][0];

	if (dp[mask][pos] != -1) // sprawdzenie czy przypadek juz byl liczony
		return dp[mask][pos] = currentSum;

	int bestSum = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		if ((mask & (1 << i)) == 0) // sprawdzenie czy wierzochlek byl juz odwiedzony
		{
			currentPath.emplace_back(i);
			//currentPath[pos] = i;
			currentSum = matrix[pos][i] + tsp(mask|(1<<i), i); // odleglosc z obecnego punktu do nastepnego + kolejne odcinki
			//bestSum = min(bestSum, currentSum);
			path[pos][i] = currentSum;
			printpath();
			cout << "pos = " << pos << "," << "i = " << i << endl;
			cout << "mask = ";
			bitset<4> y(mask);
			cout << y << endl;
			if (bestSum > currentSum)
			{
				bestSum = currentSum;
				lastBestNode = i;
				cout << "lastBestNode = " << lastBestNode << endl<< endl;
			}
			
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
	cout << "Miejsce na wynik\n";
	for (int i = 0; i < currentPath.size(); i++)
	{
		cout << currentPath[i] << " ";
	}
	cout << endl;

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
void Dynamic::printdp()
{

for (int i = 0; i < N2; i++)
{
		for (int j = 0; j < N; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}	
//------------------------------------------------------------------------------------------------------------------------------------
void Dynamic::printpath()
{

	for (int i = 0; i < N2; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------------------------------------------------
