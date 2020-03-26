#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
void swap(T* tab, int first, int secend)
{
	int temporaryValue = tab[secend];
	tab[secend] = tab[first];
	tab[first] = temporaryValue;
}

template <typename T>
void display(T* tab, long int size) {
	for (int i = 0; i < size; i++)
	{
		cout << tab[i] << " ";
	}
}

template <typename T>
void losuj_tab(T* tab, int size, int length, double procent) {
	int index_los = size - (size * ((100 - procent) / 100));
	if (procent != 0) {
		for (int i = 0; i < index_los; i++) {
			tab[i] = i;
		}
	}
	if (procent != 100) {
		for (int i = index_los; i < size; i++) {
			if (index_los == 0) {
				tab[i] = rand() % length;
			}
			else
			{
				tab[i] = (rand() % (length - index_los + 2)) + tab[index_los - 1];
			}
		}
	}
}

template <typename T>
void reverse(T* tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		tab[i] = size - 1;
	}
}

/*sortowanie przez scalanie*/
template <typename T>
class MergeSort
{
private:
	T* temporaryTable; //tablica dodatkowa, na której bêd¹ siê doknywaæ operacje na oryginalnych elementach tablicy i ich wstawianie w dobre miejsce
	void merge(T* tab, int left, int mid, int right)
	{
		for (int i = left; i <= right; i++)
		{
			temporaryTable[i] = tab[i];
		}

		int firstElemTab1 = left;     //miejsce pierwszego elementu pierwszej tablicy
		int firstElemTab2 = mid + 1; //miejsce pierwszego elementu drugiej tablicy
		int firstElemTAB = left;      //miejsce na pierwszy element tablicy po scaleniu

		while (firstElemTab1 <= mid && firstElemTab2 <= right) //laczenie az sie nie skoncza elementy z dwoch tablic i wpisywanie do wynikowej
		{
			if (temporaryTable[firstElemTab1] < temporaryTable[firstElemTab2])
			{
				tab[firstElemTAB] = temporaryTable[firstElemTab1];
				firstElemTAB++;
				firstElemTab1++;
			}
			else  //wpisanie do tablicy wynikowej elementu mniejszego po porownaniu i przesuniecie tam granicy
			{
				tab[firstElemTAB] = temporaryTable[firstElemTab2];
				firstElemTAB++;
				firstElemTab2++;
			}
		}
		while (firstElemTab1 <= mid) //gdy skoncza nam sie elementy w drugiej tablicy i zostana nam elementy tylko pierwszej
		{
			tab[firstElemTAB] = temporaryTable[firstElemTab1];
			firstElemTAB++;
			firstElemTab1++;
		}
	}
	void mergeSort(T* tab, int left, int right) {
		if (left < right)
		{
			int mid = (left + right) / 2;   //dzielenie tablicy na pol
			mergeSort(tab, left, mid);      //rekurencyjne dzielenie az do tablicy jednoelementowej
			mergeSort(tab, mid + 1, right);
			merge(tab, left, mid, right);  //polaczenie 
		}
	}
public:
	void sort(T* tab_to_sort, long int size) {
		temporaryTable = new T[size];
		mergeSort(tab_to_sort, 0, size - 1);
		delete[]temporaryTable;
	}
};

/*sortowanie przez kopcowanie*/
template <typename T>
class HeapSort
{
private:
	void MaxHeap(T* tab, int HeapSize, int root)
	{
		int maxIndex = root;  //najwieksza wartosc sposrod korzenia i jego dwojki drzew (poczatkowo korzen)
		int leftTree = 2 * root + 1;  //index lewego drzewa od korzenia
		int rightTree = 2 * root + 2;  //index prawego drzewa od korzenia

		if (leftTree < HeapSize && tab[leftTree] > tab[maxIndex])  //ustalenie maksymalnej wartosci sposrod korzenia i dwojki drzew
			maxIndex = leftTree;
		if (rightTree < HeapSize && tab[rightTree] > tab[maxIndex])
			maxIndex = rightTree;
		if (maxIndex != root)
		{
			swap(tab, root, maxIndex);  //jesli maksymalna wartosc zmienila swoja wartosc to zamiana
			MaxHeap(tab, HeapSize, maxIndex);  //rekrencyjne wywolanie funkcji
		}
	}
public:
	void sort(T* tab_to_sort, long int size)
	{
		for (int i = size / 2 - 1; i >= 0; i--) //ostatni korzen; az do najstarszego korzenia;poruszamy sie w gore kopca wiec zmniejszamy licznik
		{
			MaxHeap(tab_to_sort, size, i);      //poruszamy sie w gore po kopcu tworzac go maksymalnym (korzen wiekszy od jego drzew)
		}
		for (int i = size - 1; i > 0; i--) //poruszamy sie w gore po kopcu zamieniajac pierwszy element z ostatnim
		{
			swap(tab_to_sort, 0, i);
			size--;
			MaxHeap(tab_to_sort, size, 0); //po zamianie elementow, umiejscowieniu najwiekszego elementu, zmniejszeniu rozmiaru tworzymy znow maksymalny kopiec
		}
	}
};

/*sortowanie Shella*/
template <typename T>
class ShellSort
{
private:
	void shellSort(T* tab, long int size)
	{
		for (int gap = size / 2; gap > 0; gap /= 2)  //ustawienie poczatkowej odleglosci dwoch sasiednich elementow, z kazdym przejsciem dzielenie na 2 az do 1
		{
			for (int i = gap; i < size; i++) //poruszanie sie po tablicy
			{
				int temporary_tab = tab[i];
				int j;
				for (j = i; j >= gap && tab[j - gap] > temporary_tab; j -= gap)
				{
					tab[j] = tab[j - gap]; //zamiana jesli jest konieczna
				}
				tab[j] = temporary_tab;
			}
		}
	}
public:
	void sort(T* tab_to_sort, long int size)
	{
		shellSort(tab_to_sort, size);
	}
};

template <typename T>
class test
{
private:
	long int size[5] = { 10000, 50000, 100000, 500000, 1000000 };
	double procent[7] = { 0, 25, 50, 75, 95, 99, 99.7 };
	double liczba_tablic = 100;
	int length = 10000000;
	double suma = 0;
	double srednia = 0;

	ShellSort<T> s;
	HeapSort<T> h;
	MergeSort<T> m;

	clock_t start, stop;
	double czas = 0;
	double min_czas;
	double max_czas;
public:
	void TEST(int sortType)
	{
		fstream wyniki("Wyniki.txt", ios::app);

		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 7; i++)
			{
				min_czas = 9999;
				max_czas = 0;
				for (int k = 1; k <= liczba_tablic; k++)
				{
					T* tab;
					tab = new T[size[j]];
					losuj_tab(tab, size[j], length, procent[i]);

					switch (sortType) {
					case 1:
					{
						start = clock();
						m.sort(tab, size[j]);
						stop = clock();
					}
					break;
					case 2:
					{
						start = clock();
						h.sort(tab, size[j]);
						stop = clock();
					}
					break;
					case 3:
					{
						start = clock();
						s.sort(tab, size[j]);
						stop = clock();
					}
					break;
					default:
						break;
					}
					czas = (stop - start) / (double)CLOCKS_PER_SEC;
					suma += czas;
					if (min_czas > czas)
					{
						min_czas = czas;
					}
					if (max_czas < czas)
					{
						max_czas = czas;
					}
					if (k == liczba_tablic)
					{

						if (k == 1)
						{
							wyniki << "minimum: " << procent[i] << "  " << size[j] << "  " << czas << " sekund" << endl;
							wyniki << "maximum: " << procent[i] << "  " << size[j] << "  " << czas << " sekund" << endl;
						}
						else
						{
							wyniki << "minimum: " << procent[i] << "  " << size[j] << "  " << min_czas << " sekund" << endl;
							wyniki << "maximum: " << procent[i] << "  " << size[j] << "  " << max_czas << " sekund" << endl;
						}
					}
					delete[]tab;
				}
				srednia = suma / liczba_tablic;
				wyniki << "srednia: " << procent[i] << "  " << size[j] << "  " << srednia << " sekund" << endl;
				suma = 0;
			}

			min_czas = 9999;
			max_czas = 0;

			for (int k = 1; k <= liczba_tablic; k++) {

				T* tabReverse;
				tabReverse = new T[size[j]];
				losuj_tab(tabReverse, size[j], length, 100);
				reverse(tabReverse, size[j]);

				switch (sortType)
				{
				case 1:
				{
					start = clock();
					m.sort(tabReverse, size[j]);
					stop = clock();
				}
				break;
				case 2:
				{
					start = clock();
					h.sort(tabReverse, size[j]);
					stop = clock();
				}
				break;
				case 3:
				{
					start = clock();
					s.sort(tabReverse, size[j]);
					stop = clock();
				}
				break;
				default:
					break;
				}
				czas = (stop - start) / (double)CLOCKS_PER_SEC;
				suma += czas;
				if (min_czas > czas)
				{
					min_czas = czas;
				}
				if (max_czas < czas)
				{
					max_czas = czas;
				}
				if (k == liczba_tablic) {

					if (k == 1)
					{
						wyniki << "minimum: " << "odwrocone" << "  " << size[j] << "  " << czas << " sekund" << endl;
						wyniki << "maximum: " << "odwrocone" << "  " << size[j] << "  " << czas << " sekund" << endl;

					}
					else
					{
						wyniki << "minimum: " << "odwrocone" << "  " << size[j] << "  " << min_czas << " sekund" << endl;
						wyniki << "maximum: " << "odwrocone" << "  " << size[j] << "  " << max_czas << " sekund" << endl;
					}
				}
				delete[]tabReverse;
			}
			srednia = suma / liczba_tablic;
			wyniki << "srednia: " << "odwrocone" << "  " << size[j] << "  " << srednia << " sekund" << endl;
			suma = 0;
		}

	}
};

int main()
{
	srand(time(NULL)); //zapobiegniecie takiego samego losu za kazdym odpaleniem
	cout.setf(ios::fixed); //notacja zwykla, czyli nie wywali wyniku typu 1.175000e+003	

	remove("Wyniki.txt");
	fstream wyniki;
	wyniki.open("Wyniki.txt", ios::app);

	test<int> SORTOWANIE;
	wyniki << " MergeSort " << endl;
	SORTOWANIE.TEST(1);
	wyniki << " HeapSort " << endl;
	SORTOWANIE.TEST(2);
	wyniki << " ShellSort " << endl;;
	SORTOWANIE.TEST(3);

	wyniki.close();
}