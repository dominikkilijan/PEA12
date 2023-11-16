#include "Dynamic.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
Dynamic::Dynamic(int n, int** m)
{
	N = n;
	matrix = m;
}
//------------------------------------------------------------------------------------------------------------------------------------
long double Dynamic::TSPDynamic()
{
	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC(); // rozpoczecie pomiaru czasu

	// algorytm
	Sleep(1000);
	// koniec algorytmu

	// koniec pomiaru czasu
	elapsed = read_QPC() - start; 
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku
	cout << "Miejsce na wynik\n";

	// czyszczenie
	cout << "Zwalnianie pamieci\n";

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