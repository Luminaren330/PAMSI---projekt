
#include<iostream>
#include<random>
#include<ctime>

using namespace std;

template<typename Type>
int check(Type array[], int size,int choice) // funkcja sprawdzająca czy dobrze posortowano tablicę
{
    for (int i =0; i<size-2;i++) {
        if (choice == 1 || choice == 2 || choice == 4) { // sprawdza czy posortowano rosnąco
            if (array[i + 1] >= array[i]) {
                continue;
            } else {
                return 0; // zwraca zero jak źle tablica jest posortowana
            }
        }
        if (choice ==3) {
            if (array[i + 1] <= array[i]) { // sprawdza czy posortowano malejąco
                continue;
            } else {
                return 0;
            }
        }

    }
    return 1; // zwraca jeden jak dobrze tablica jest posortowana
}

template<typename Type>
int division(Type array[], int first, int last, int choice) // funckja dzieląca tablicę na 2 części: na tablicę posiadającą mniejsze lub równe oraz na większe lub równe liczby od tmp1
{
    Type tmp1 = array[(first+last)/2]; // obieramy tmp1
    Type tmp2 = 0; // do zamiany miejsc
    while (true) // petla nieskonczona, kończy się przy return
    {
        if (choice == 1 || choice == 2 || choice ==4) {  //sortowanie rosnace
            while (array[last] > tmp1) // dopoki elementy sa wieksze od tmp1
                last--;
            while (array[first] < tmp1) // dopoki elementy sa mniejsze od tmp1
                first++;
        }
        if(choice == 3) { // sortowanie malejace
            while (array[last] < tmp1) // dopoki elementy sa mniejsze od tmp1
                last--;
            while (array[first] > tmp1) // dopoki elementy sa wieksze od tmp1
                first++;
        }
        if (first < last) // zamieniamy miejscami gdy first < last
        {
            tmp2 = array[first];
            array[first] = array[last];
            array[last] = tmp2;
            first++;
            last--;
        }
        else { // zwracamy last jako punkt podzialu tablicy gdy first >= last
            return last;
        }
    }
}

template<typename Type>
void quick_sort(Type array[], int first, int last, int choice) // sortowanie szybkie
{
    Type pivot = 0;
    if (first < last)
    {
        pivot = division(array, first, last, choice); // dzielimy tablice na dwie czesci; pivot oznacza punkt podzialu
        quick_sort(array, first, pivot, choice); // wywołanie funkcji dla pierwszej części tablicy
        quick_sort(array, pivot + 1, last, choice); // wywołanie funkcji dla drugiej części tablicy
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
            quick_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas działania sortowania

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
            quick_sort(array, 0, size - 1, choice);
            uniform_int_distribution<> distr2(percentage, 100);
            for (int i = size - 1; i > (size * percentage / 100); i--)
            {
            array[i] = distr2(gen); //zastąpienie liczb, aby tylko część była posortowana
            }

            clock_t timeBegin = clock();
            quick_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas działania sortowania

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
            quick_sort(array, 0, size - 1, 3);

            clock_t timeBegin = clock();
            quick_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin; // czas działania sortowania

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