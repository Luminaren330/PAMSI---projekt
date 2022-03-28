#include<iostream>
#include<random>
#include<ctime>

using namespace std;

template<typename Type>
int check(Type array[], int size,int choice) // funkcja sprawdzająca czy dobrze posrtowano tablicę
{
    for (int i =0; i<size-2;i++) {
        if (choice == 1 || choice == 2 || choice == 4) { // sprawdza czy posrtowano rosnąco
            if (array[i + 1] >= array[i]) {
                continue;
            } else {
                return 0; // zwraca zero jak źle tablica jest posrtowana
            }
        }
        if (choice ==3) {
            if (array[i + 1] <= array[i]) { // sprawdza czy posrtowano malejąco
                continue;
            } else {
                return 0;
            }
        }

    }
    return 1; // zwraca jeden jak dobrze tablica jest posortowana
}

template <typename Type>
void merge(Type array[], int start, int middle, int last, int choice) { // funkcja sortująca
    Type *tmp_array = new Type[(last - start + 1)]; // utworzenie tablicy pomocniczej o odpowiednim rozmiarze
    int i = start;
    int j = middle +1; // zmienne pomocnicze
    int k = 0;
    if (choice == 1|| choice ==2 || choice == 4) { // posortowanie rosnąco
        while (i <= middle && j <= last) {
            if (array[j] < array[i]) { // zapisanie do tablicy pomocniczej wartości mniejszej
                tmp_array[k] = array[j];
                j++;
            } else {
                tmp_array[k] = array[i]; // zapisanie do tablicy pomocniczej wartości mniejszej
                i++;
            }
            k++;
        }
    }
    if (choice == 3) { // posortowanie malejąco
        while (i <= middle && j <= last) {
            if (array[j] > array[i]) { // zapisanie do tablicy pomocniczej wartości większej
                tmp_array[k] = array[j];
                j++;
            } else {
                tmp_array[k] = array[i]; // zapisanie do tablicy pomocniczej wartości większej
                i++;
            }
            k++;
        }
    }

    if (i <= middle) {
        while (i <= middle) {
            tmp_array[k] = array[i]; //przypisanie do następnych indeksów tablicy pomocniczej wartości większych (lub mniejszych), porównywalnych wcześniej
            i++;
            k++;
        }
    } else {
        while (j <= last) {
            tmp_array[k] = array[j]; //przypisanie do następnych indeksów tablicy pomocniczej wartości większych (lub mniejszych), porównywalnych wcześniej
            j++;
            k++;
        }
    }

    for (i = 0; i <= last - start; i++) { // zamiana miejsc w tablicy głównej
        array[start + i] = tmp_array[i];
    }

    delete [] tmp_array;  // usunięcie tablicy, aby nie było wycieku
}
template <typename Type>
void merge_sort(Type array[], int start, int last, int choice) // funckja dzieląca tablicę na części
{
    int middle = 0;

    if (start != last)
    {
        middle = (start + last) / 2; // dzielenie tablicy na części
        merge_sort(array, start, middle, choice); //dzielenie tablicy na części dopóki początek indeksu tablicy nie jest równy końcowy, pierwsza część
        merge_sort(array, middle + 1, last, choice); // druga część
        merge(array, start, middle, last, choice); //wywołanie funkcji sortującej. Na początku sortuje części podzielone, a następnie całość tablicy
    }
}

int main()
{
    int size=0;
    int choice=0;
    int percentage = 25; // procent, ile liczb jest już posortowanych
    random_device rd;
    mt19937 gen(rd()); // generator losowych liczb
    uniform_int_distribution<> distr(0, 100); // przedział
    cout << "Podaj rozmiar tablicy:  ";
    cin >> size;
    cout << "Wybierz opcje:" << endl << "1. Posortuj rosnaco losowe liczby" << endl
         << "2.Posortuj, gdzie dana czesc liczb jest posortowana " << endl
         << "3.Posortuj malejaco losowe liczby:  " << endl
         << "4.Posrtuj rosnaco, liczby posortowane malejaco: ";
    cin >> choice;
    auto *array = new double[size]; // utworzenie dynamicznej tablicy o określonym rozmiarze
    float time = 0;
    if (choice == 1 || choice == 3) {
        for (int j = 0; j < 100; j++) { // sortowanie 100 tablic
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }

            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas sortowania

            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time / CLOCKS_PER_SEC) << "s"; //pokazuje czas działania sortowania
    }
    else if (choice == 2) {
        for(int j =0; j<100;j++) {
            uniform_int_distribution<> distr1(0, percentage);
            for (int i = 0; i <size; i++) // wczytywanie liczb od 0 do ustawionego procentu (aby tylko dana część była posortowana)
            {
                array[i] = distr1(gen);
            }
            merge_sort(array, 0, size - 1, choice);
            uniform_int_distribution<> distr2(percentage, 100);
            for (int i = size - 1; i > (size * percentage / 100); i--)
            {
                array[i] = distr2(gen); //zastąpienie liczb, aby tylko część była posortowana
            }

            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas sortowania

            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas działania sortowania
    }
    else if (choice == 4) {
        for(int j =0; j<100;j++) {
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }
            merge_sort(array, 0, size - 1, 3);

            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas sortowania

            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas działania sortowania
    } else {
        cout << "Nie ma takiej opcji:" << endl;
    }

    delete[] array; // usunięcie tablicy, aby nie było wycieku
    return 0;

}