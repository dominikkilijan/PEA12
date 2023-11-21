#include "Dynamic.h"
#include "AdjacencyMatrix.h"
#include "Answer.h"
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
Answer Dynamic::tsp(int mask, int pos)
{
	Answer answer(N);
	vector<int> bestPath;

	//printdp();

	if (mask == visitedAll) // jesli odwiedzono wszystkie wierzcholki
	{
		answer.sum = matrix[pos][0];
		answer.pathAnswer.emplace_back(pos);
		return answer;
	}

	if (dp[mask][pos] != -1) // sprawdzenie czy przypadek juz byl liczony
		return answer;

	int bestSum = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		if ((mask & (1 << i)) == 0) // sprawdzenie czy wierzochlek byl juz odwiedzony
		{
			if (answer.sum != 0)
				answer.pathAnswer.clear();

			answer.sum = matrix[pos][i];
			answer.addAnswers(tsp(mask | (1 << i), i));
			if (mask != visitedAll)
				answer.pathAnswer.emplace_back(pos);

			if (bestSum > answer.sum)
			{
				bestSum = answer.sum;
				answer.sum = 0;
				bestPath.clear();
				bestPath = answer.pathAnswer;
				answer.pathAnswer.clear();
			}

		}
	}

	answer.pathAnswer = bestPath;
	answer.sum = bestSum;
	return answer;
}
//------------------------------------------------------------------------------------------------------------------------------------
long double Dynamic::TSPDynamic()
{
	Answer finalAnswer(N);

	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// rozpoczecie pomiaru czasu
	start = read_QPC();

	// algorytm
	finalAnswer = tsp(1, 0);
	// koniec algorytmu

	// koniec pomiaru czasu
	elapsed = read_QPC() - start;
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku
	cout << "Miejsce na wynik\n\n\n====================================================================================\n";
	cout << "finalAnswer.sum = " << finalAnswer.sum << "\nSciezka:\n";
	//cout << "0->";
	for (int i = finalAnswer.pathAnswer.size() - 1; i >= 0; i--)
	//for (int i = 0; i < finalAnswer.pathAnswer.size()/2; i++)
	{
		cout << finalAnswer.pathAnswer[i] << "->";
	}
	cout << "0" << endl;


	//printdp();
	/*for (int i = 0; i < currentPath.size(); i++)
	{
		cout << currentPath[i] << " ";
	}
	cout << endl;*/

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
