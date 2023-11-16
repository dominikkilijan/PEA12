#include "FileHandler.h"
//include "Bruteforce.h"
#include <iostream>

using namespace std;

int choice;
int run = 1;

int main()
{
    FileHandler fHandler;

    // menu wyswietlane ciagle
    while (run)
    {
        cout << "MENU:\n";;
        cout << "1. Wygeneruj losowe dane\n";
        cout << "2. Wyswietl dane\n";
        cout << "3. Uruchom algorytm\n";
        cout << "4. Zakoncz\n";

        cin >> choice;
        system("CLS"); // czyszczenie ekranu
        switch (choice)
        {
        case 1:
        {
            cout << "Ile wierzcholkow?\n";
            int N;
            cin >> N;
            cout << "Podaj nazwe pliku wraz z rozszerzeniem:\n";
            string filename;
            filename = "test.txt";
            cin >> filename;

            fHandler.generate(N, filename);
        }
        break;
        case 2:
        {
            cout << "Podaj nazwe pliku do wyswietlenia:\n";
            string filename;
            cin >> filename;

            fHandler.print(filename);
        }
        break;
        case 3:
        {
            cout << "Podaj nazwe pliku do wczytania:\n";
            string filename;
            cin >> filename;

            fHandler.openFile(filename);
        }
        break;
        case 4:
            cout << "Koniec programu\n";
            run = 0;
            break;

        default:
            cout << "Nieprawidlowy numer!\n";
            break;
        }
    }
}