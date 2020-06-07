#include "calculate_gini.hpp"

#include <iostream>
#include <algorithm>
#include <math.h>
#include "data_read.hpp"
#include "sort_col.hpp"

void gini(std::vector<std::vector<double>> &dataSetTable)
{
	int rows = dataSetTable.size(); // Tu bedziemy trzymac ilosc wierszy naszej tabeli
	int cols = dataSetTable[0].size(); // Tu bedziemy trzymali ilosc kolumn naszej tabeli
	
	double startingAvarage = 0; // Poczatkowa srednia wartosc, ktora umiescimy w korzeniu naszego drzewa

	for (int iterator = 0; iterator < rows; iterator++)
	{
		startingAvarage += dataSetTable[iterator][cols - 1]; // Bierzemy ostatnia wartosc z kazdego wiersza, to znaczy cala ostatnia kolumne.
	}
	startingAvarage /= rows; // Nasza srednia, bedzie liczona jako suma calej ostatniej kolumny podzielic na ilosc wierszy
	
	for (int iterator = 0; iterator < rows; iterator++)
	{
		dataSetTable[iterator].push_back(dataSetTable[iterator][cols - 1] - startingAvarage); // Tutaj dodajemy druga kolumne na resiudale.
	}

	cols++; // Liczba kolumn nam przyrosla o jeden, poniewaz dodalismy residuale

	std::set<double> decidingParameters;
	for (int i = 0; i < rows; i++)
	{
		decidingParameters.insert(dataSetTable[i][cols - 1]); // Dodajemy do naszego zbioru set elementy ostatniej kolumny
	}

	for (std::set<double>::iterator k = decidingParameters.begin(); k != decidingParameters.end(); k++) {
		//cout << *k << endl;
	}
	
	double giniLowestFromAll = 2; // Tu bedziemy trzymac najmniejszego giniego ze wszystkich kolumn
	
	for (int i = 0; i < cols; i++)
	{
		double tempGini;
		sortCol::sort(dataSetTable.begin(), dataSetTable.end(), colType::fixed_addicity);
		for (int i = 0; i < rows; i++)
		{
			std::cout << dataSetTable[i][cols - 1] << std::endl; // Dodajemy do naszego zbioru set elementy ostatniej kolumny
		}
		tempGini = calculateGini(dataSetTable, rows, cols, i, decidingParameters);		
	}
}

double calculateGini(std::vector<std::vector<double>> &dataSetTable , int rows, int columns, int whatColumn , std::set<double> currentDecidingParameters)
{
	double average; // W tym wektorze trzymamy nasze srednie
	double giniLowestfromColumn = 2; // Dwa zeby pierwsza wartosc dostala sie do srodka

	for (int i = 0; i < rows - 1; i++) // minus 1 bo  nie liczymy dla ostatniego. Pierwszy z drugim, drugi z trzecim, ... Przedostatni z ostatnim
	{
		double probabilityForLess = 0; // Tu bedziemy trzymali wartosc roznicy kwadratow prawdopodobienstw dla wartosci mniejszych od sredniej
		double probabilityForHigher = 0; // Tu bedziemy trzymali wartosc roznicy kwadratow prawdopodobienstw dla wartosci wikeszych od sredniej

		double numberOfGradesAllTogetherForLess = i + 1; // Tutaj bedziemy trzymali sumaryczna ilosc rekordow mniejszych od naszej sredniej 
		double numberOfGradesAllTogetherForHigher = rows - (i + 1); // Tutaj bedziemy trzymali sumaryczna ilosc rekordow wiekszych od naszej sredniej

		if (dataSetTable[i][whatColumn] != dataSetTable[i + 1][whatColumn]) // Liczymy srednia jesli wartosci sa rozne
			average = (dataSetTable[i][whatColumn] + dataSetTable[i + 1][whatColumn] / 2);
		else
			continue;
		
		std::vector<int> numberOfEachGradeForLess(currentDecidingParameters.size());
		std::vector<int> numberOfEachGradeForHigher(currentDecidingParameters.size());

		for (int j = 0; j < numberOfGradesAllTogetherForLess; j++) // po tej stronie tabeli znajduja sie wartosci mniejsze od naszej sredniej
		{

			int counter = 0;
			for (std::set<double>::iterator k = currentDecidingParameters.begin(); k != currentDecidingParameters.end(); k++) {

				if (dataSetTable[j][columns - 1] == *k)
				{
					numberOfEachGradeForLess[counter]++; // Na tej pozycji gdzie jestesmy w naszym secie zwiekszamy wartosc o jeden
					break;
				}
				counter++;
			}
			//Czyli zwiekszamy ilosc danych ocen w tabeli
		}

		for (int j = i + 1; j < rows; j++) // Po tej stronie tabeli znajduja sie wartosci wieksze od naszej sredniej
		{
			int counter = 0;
			for (std::set<double>::iterator k = currentDecidingParameters.begin(); k != currentDecidingParameters.end(); k++) {

				//cout << "DODAWANIE DO LICZNIKA TYCH DLA WIEKSZYCH" << endl << endl;
				if (dataSetTable[j][columns - 1] == *k)
				{
					
					numberOfEachGradeForHigher[counter]++; // Na tej pozycji gdzie jestesmy w naszym secie zwiekszamy wartosc o jeden
					//cout << "numberOfEachGradeForHigher[" << counter << "]" << "=" << numberOfEachGradeForHigher[counter]++;
					continue;
				}
				counter++;
			}
		}


		for (int j = 0; j < currentDecidingParameters.size(); j++)
		{
			probabilityForLess += pow(numberOfEachGradeForLess[j] / numberOfGradesAllTogetherForLess, 2.0); // Kwadrat prawdopodobienstwa wystapienia danej liczby
			//cout << "numberOfGradesAllTogetherForLess " << numberOfGradesAllTogetherForLess << endl;
			//cout << numberOfEachGradeForLess[j]  << "ile z kazdego typu dla mniejszego" << endl;

			probabilityForHigher += pow(numberOfEachGradeForHigher[j] / numberOfGradesAllTogetherForHigher, 2.0); // Kwadrat prawdopodobienstwa wystapienia danej liczby
			//cout << "numberOfGradesAllTogetherForHigher " << numberOfGradesAllTogetherForHigher << endl;
			//cout <<numberOfEachGradeForHigher[j]  << " ile z kazdego typu dla wiekszego" << endl;
		}


		probabilityForLess = 1 - probabilityForLess;
		probabilityForHigher = 1 - probabilityForHigher;

		//cout << "probabilityForHigher " << probabilityForHigher << endl;

		// Teraz musimy policzyc Gini impurity, z udzialu obydwu tych liczb
		double giniTemp = probabilityForLess * (numberOfGradesAllTogetherForLess / rows) + probabilityForHigher * (numberOfGradesAllTogetherForHigher / rows);


		
		if (giniTemp < giniLowestfromColumn)
			giniLowestfromColumn = giniTemp;
		std::cout << giniTemp <<" "<<i<< std::endl;
	}
	return giniLowestfromColumn;
}
