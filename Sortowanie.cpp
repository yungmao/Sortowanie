//Daniel Jab³oñski 241165
//Sortowanie

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <conio.h>

using namespace std;

//Deklaracja funkcji i zmiennych globalnych
size_t wybierzRozmiar();
template <class item>
void wyswietlTablice(vector <item> tab);
template <class item>
void QuickSort(vector <item>  &tab, int left, int right);
template <class item>
void Mergesort(vector <item>  &tab, int pocz, int kon);
template <class item>
void IntroSort(vector <item>  &data, int count);
template <class item>
void SortujMalejaco(vector <item> & tab, int left, int right);
template <class item>
void SprawdzTablice(vector <item> & tab);
chrono::duration<double> minTime(chrono::duration<double> time[], size_t size);
chrono::duration<double> maxTime(chrono::duration<double> time[], size_t size);
chrono::duration<double> sumTime(chrono::duration<double> time[], size_t size);

int main()
{
	srand(time(NULL));
	const size_t ilosc = 100;
	vector <vector <int>> tablica1(ilosc);
	vector <vector <int>> tablica2(ilosc);
	vector <vector <int>> tablica3(ilosc);
	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds[ilosc];

	size_t rozmiar = wybierzRozmiar();

	char wybor;
	for (;;)
	{
		//Losowanie elementow
		for (size_t i = 0; i < ilosc; i++)
		{
			tablica1[i].clear();
			for (size_t j = 0; j < rozmiar; j++)
			{
				tablica1[i].push_back(rand() % 1000);
				tablica2[i] = tablica1[i];
				tablica3[i] = tablica1[i];
			}
		}

	tryb:
		system("cls");
		cout << "PANEL SORTOWANIA" << endl;
		cout << "Wybierz tryb eksperymentu: " << endl;
		cout << "1. Wszystkie elementy tablicy losowe " << endl;
		cout << "2. N poczatkowych elementow tablicy posortowane " << endl;
		cout << "3. Wszystkie elementy tablicy posortowane w odwrotnej kolejnosci " << endl;
		cout << "\n4. Zakoncz program " << endl;
		wybor = _getch();
		system("cls"); //Czyszczenie okna konsoli
		switch (wybor)
		{
		case '1':
			break;
		case '2':
			double N;
			cout << "1. 25%" << endl;
			cout << "2. 50%" << endl;
			cout << "3. 75%" << endl;
			cout << "4. 95%" << endl;
			cout << "5. 99%" << endl;
			cout << "6. 99,7%" << endl;
		N:
			wybor = _getch();
			if (wybor == '1') N = 25;
			else if (wybor == '2') N = 50;
			else if (wybor == '3') N = 75;
			else if (wybor == '4') N = 95;
			else if (wybor == '5') N = 99;
			else if (wybor == '6') N = 99.7;
			else
			{
				goto N;
			}
			for (size_t i = 0; i < ilosc; i++)
			{
				QuickSort(tablica1[i], 0, (rozmiar - 1)*N / 100);
				QuickSort(tablica2[i], 0, (rozmiar - 1)*N / 100);
				QuickSort(tablica3[i], 0, (rozmiar - 1)*N / 100);
			}

			break;
		case '3':
			for (size_t i = 0; i < ilosc; i++)
			{
				SortujMalejaco(tablica1[i], 0, rozmiar - 1);
				SortujMalejaco(tablica2[i], 0, rozmiar - 1);
				SortujMalejaco(tablica3[i], 0, rozmiar - 1);
			}
			break;
		case '4':
			exit(0);
		default:
			system("cls");
			goto tryb;
		}
		system("cls");
		cout << "Chcesz wyswietlic tablice przed sortowaniem? Y/N" << endl;
		wybor = _getch();
		if (wybor == 'Y' || wybor == 'y')
		{
			wyswietlTablice(tablica1[0]);
			cout << "Enter, aby kontynuowac" << endl;
			cin.get();
		}
		system("cls");

		cout << "Mergesort: " << endl;
		for (size_t i = 0; i < ilosc; i++)
		{
			start = chrono::system_clock::now();
			Mergesort(tablica1[i], 0, rozmiar - 1);
			end = chrono::system_clock::now();
			elapsed_seconds[i] = end - start;
		}
		cout << "Calkowity czas sortowania: " << sumTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Sredni czas: " << (minTime(elapsed_seconds, ilosc).count() + maxTime(elapsed_seconds, ilosc).count()) / 2 * 1000 << " ms" << endl;
		cout << "Najszybsze sortowanie: " << minTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Najwolniejsze sortowanie: " << maxTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		SprawdzTablice(tablica1[0]);

		cout << endl << "Quicksort: " << endl;
		for (size_t i = 0; i < ilosc; i++)
		{
			start = chrono::system_clock::now();
			QuickSort(tablica2[i], 0, rozmiar - 1);
			end = chrono::system_clock::now();
			elapsed_seconds[i] = end - start;

		}
		cout << "Calkowity czas sortowania: " << sumTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Sredni czas: " << (minTime(elapsed_seconds, ilosc).count() + maxTime(elapsed_seconds, ilosc).count()) / 2 * 1000 << " ms" << endl;
		cout << "Najszybsze sortowanie: " << minTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Najwolniejsze sortowanie: " << maxTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		SprawdzTablice(tablica2[0]);

		cout << endl << "Introsort: " << endl;
		for (size_t i = 0; i < ilosc; i++)
		{
			start = chrono::system_clock::now();
			IntroSort(tablica3[i], rozmiar);
			end = chrono::system_clock::now();
			elapsed_seconds[i] = end - start;
		}
		cout << "Calkowity czas sortowania: " << sumTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Sredni czas: " << (minTime(elapsed_seconds, ilosc).count() + maxTime(elapsed_seconds, ilosc).count()) / 2 * 1000 << " ms" << endl;
		cout << "Najszybsze sortowanie: " << minTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;
		cout << "Najwolniejsze sortowanie: " << maxTime(elapsed_seconds, ilosc).count() * 1000 << " ms" << endl;

		SprawdzTablice(tablica3[0]);
		cout << "Enter, aby kontynuowac" << endl;
		cin.get();
	}
}

size_t wybierzRozmiar()
{
	size_t rozmiar;
	char wybor;
	cout << "PANEL SORTOWANIA" << endl;
	cout << "Wybierz rozmiar tablic: " << endl;
	cout << "1. 10 000 " << endl;
	cout << "2. 50 000 " << endl;
	cout << "3. 100 000 " << endl;
	cout << "4. 500 000 " << endl;
	cout << "5. 1 000 000 " << endl;
	wybor = _getch();
	system("cls");
	switch (wybor)
	{
	case '1':
		rozmiar = 10000;
		break;
	case '2':
		rozmiar = 50000;
		break;
	case '3':
		rozmiar = 100000;
		break;
	case '4':
		rozmiar = 500000;
		break;
	case '5':
		rozmiar = 1000000;
		break;
	default:
		rozmiar = wybierzRozmiar();
		break;
	}
	return rozmiar;
}
template <class item>
void wyswietlTablice(vector <item> tab)
{
	for (size_t i = 0; i < tab.size(); i++)
	{
		cout << tab[i] << endl;
	}
}
template <class item>
void QuickSort(vector <item> & tab, int left, int right)
{
	int i = left;
	int j = right;
	int x = tab[(left + right) / 2];
	do
	{
		while (tab[i] < x)
			i++;

		while (tab[j] > x)
			j--;

		if (i <= j)
		{
			swap(tab[i], tab[j]);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) QuickSort(tab, left, j);

	if (right > i) QuickSort(tab, i, right);
}
template <class item>
void merge(vector <item> & tab, int pocz, int sr, int kon)
{
	vector <int> t(kon + 1);
	int i, j, q;
	for (i = pocz; i <= kon; i++) t[i] = tab[i];  // Skopiowanie danych do tablicy pomocniczej
	i = pocz; j = sr + 1; q = pocz;                 // Ustawienie wskaŸników tablic
	while (i <= sr && j <= kon) {         // Przenoszenie danych z sortowaniem ze zbiorów pomocniczych do tablicy g³ównej
		if (t[i] < t[j])
			tab[q++] = t[i++];
		else
			tab[q++] = t[j++];
	}
	while (i <= sr) tab[q++] = t[i++]; // Przeniesienie nie skopiowanych danych ze zbioru pierwszego w przypadku, gdy drugi zbiór siê skoñczy³
}
template <class item>
void Mergesort(vector <item> & tab, int pocz, int kon)
{
	int sr;
	if (pocz < kon) {
		sr = (pocz + kon) / 2;
		Mergesort(tab, pocz, sr);    // Dzielenie lewej czêœci
		Mergesort(tab, sr + 1, kon);   // Dzielenie prawej czêœci
		merge(tab, pocz, sr, kon);   // £¹czenie czêœci lewej i prawej
	}
}
template <class item>
int Partition(vector <item> & data, int left, int right)
{
	int pivot = data[right];
	int temp;
	int i = left;

	for (int j = left; j < right; ++j)
	{
		if (data[j] <= pivot)
		{
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
			i++;
		}
	}

	data[right] = data[i];
	data[i] = pivot;

	return i;
}
template <class item>
void QuickSortRecursive(vector <item> & data, int left, int right)
{
	if (left < right)
	{
		int q = Partition(data, left, right);
		QuickSortRecursive(data, left, q - 1);
		QuickSortRecursive(data, q + 1, right);
	}
}
template <class item>
void MaxHeapify(vector <item> & data, int heapSize, int index)
{
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) * 2;
	int largest = 0;

	if (left < heapSize && data[left] > data[index])
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[right] > data[largest])
		largest = right;

	if (largest != index)
	{
		int temp = data[index];
		data[index] = data[largest];
		data[largest] = temp;

		MaxHeapify(data, heapSize, largest);
	}
}
template <class item>
void HeapSort(vector <item> & data, int count)
{
	int heapSize = count;

	for (int p = (heapSize - 1) / 2; p >= 0; --p)
		MaxHeapify(data, heapSize, p);

	for (int i = count - 1; i > 0; --i)
	{
		int temp = data[i];
		data[i] = data[0];
		data[0] = temp;

		--heapSize;
		MaxHeapify(data, heapSize, 0);
	}
}
template <class item>
void InsertionSort(vector <item> & data, int count)
{
	int i, j, tmp;

	for (i = 1; i < count; i++)
	{
		j = i;
		tmp = data[i];
		while (j > 0 && tmp < data[j - 1])
		{
			data[j] = data[j - 1];
			j--;
		}
		data[j] = tmp;
	}
}

template <class item>
void IntroSort(vector <item> & data, int count)
{
	int partitionSize = Partition(data, 0, count - 1);

	if (partitionSize < 16)
	{
		InsertionSort(data, count);
	}
	else if (partitionSize > (2 * log(count)))
	{
		HeapSort(data, count);
	}
	else
	{
		QuickSortRecursive(data, 0, count - 1);
	}
}
template <class item>
void SortujMalejaco(vector <item> & tab, int left, int right)
{
	int i = left;
	int j = right;
	int x = tab[(left + right) / 2];
	do
	{
		while (tab[i] > x)
			i++;

		while (tab[j] < x)
			j--;

		if (i <= j)
		{
			swap(tab[i], tab[j]);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) SortujMalejaco(tab, left, j);

	if (right > i) SortujMalejaco(tab, i, right);
}
template <class item>
void SprawdzTablice(vector <item> & tab)
{
	bool ok;
	for (size_t i = 0; i < tab.size() - 2; i++)
	{
		if (tab[i] <= tab[i + 1])
		{
			ok = true;
		}
		else
		{
			ok = false;
		}
	}
	if (ok == true)
	{
		cout << "Dobrze posortowano" << endl;
	}
	else
	{
		cout << "Zle posortowano" << endl;
	}
}
chrono::duration<double> minTime(chrono::duration<double> time[], size_t size)
{
	chrono::duration<double> sumTime = time[0];
	for (size_t i = 0; i < size - 1; i++)
	{
		if (time[i + 1] < time[i]) sumTime = time[i + 1];
	}
	return sumTime;
}
chrono::duration<double> maxTime(chrono::duration<double> time[], size_t size)
{
	chrono::duration<double> sumTime = time[0];
	for (size_t i = 0; i < size - 1; i++)
	{
		if (time[i + 1] > time[i]) sumTime = time[i + 1];
	}
	return sumTime;
}
chrono::duration<double> sumTime(chrono::duration<double> time[], size_t size)
{
	chrono::duration<double> sumTime = (chrono::duration<double>)0;
	for (size_t i = 0; i < size; i++)
	{
		sumTime += time[i];
	}
	return sumTime;
}