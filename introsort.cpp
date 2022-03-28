#include<iostream>
#include<random>
#include<ctime>
#include<cmath>

using namespace std;

#define M_LN2 0.69314718055994530942

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
void InsertionSort(Type array[], int size,int choice) { //sortowanie przez wstawianie
    int tmp; // zmienne pomocnicze
    int j;
    for (int i = 1; i < size; i++) {
        tmp = array[i]; //tymczasowe zapisanie
        if (choice == 1 || choice == 2 || choice == 4) { //sortowanie rosnące
            for (j = i; j > 0; j--) {
                if (tmp < array[j - 1]) { //jesli tymczasowa jest mniejsza to zamienia miejscami
                    array[j] = array[j - 1];
                } else {
                    break;
                }
            }
            array[j] = tmp;
        }
        if (choice == 3) { // sortowanie malejące
            for (j = i; j > 0; --j) {
                if (tmp > array[j - 1]) { //jesli tymczasowa jest większa to zamienia miejscami
                    array[j] = array[j - 1];
                } else {
                    break;
                }
            }
            array[j] = tmp;
        }
    }
}
template <typename Type>
void heapify(Type array[], int size, int i , int choice)
{
    int largest = i;
    int left = 2 * i + 1; // lewy = 2*i + 1
    int right = 2 * i + 2; // prawy = 2*i + 2
    Type tmp = 0;
    if (choice == 1 || choice == 2 || choice ==4) { // posortowanie rosnąco
        if (left < size && array[left] > array[largest]) { // zamienia największą liczbę na wartość lewą, jeśli jest spełniony warunek
            largest = left;
        }
        if (right < size && array[right] > array[largest]) { // zamienia największą liczbę na wartość prawą, jeśli jest spełniony warunek
            largest = right;
        }
    }
    if (choice == 3) { // posortowanie malejąco
        if (left < size && array[left] < array[largest]) { // zamienia (tutaj najniższą) liczbę na wartość lewą, jeśli jest spełniony warunek
            largest = left;
        }
        if (right < size && array[right] < array[largest]) { // zamienia (tutaj najniższą) liczbę na wartość prawą, jeśli jest spełniony warunek
            largest = right;
        }
    }
    if (largest != i) { // jeśli największa/najniższa nie jest równa i zamienia miejscami
        tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;
        heapify(array, size, largest, choice); // rekurencyjnie wywołanie funkcji
    }
}

template <typename Type>
void heap_sort(Type array[], int size, int choice) // funkcja heapsort
{
    Type tmp = 0;
    for (int i = size / 2 - 1; i >= 0; i--) { // zamiana miejsc w tablicy
        heapify(array, size, i, choice);
    }
    for (int i = size - 1; i >= 0; i--) { //zamienia miejscami kolejne wartości
        tmp = array[0];
        array[0] = array[i];
        array[i] = tmp;
        heapify(array, i, 0, choice);
    }
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

template <typename Type>
void Mixed_sort(Type array[], int size, int depthLimit, int choice) //funkcja sortująca
{
    int pivot = 0;
    if(depthLimit <=0 ) { //jeśli  maksymalna dozwolona głębokość wywołań rekurencyjnych jest mniejsza bądź równa 0
        heap_sort(array,size,choice); // to wywołuje sortowanie przez kopcowanie
        return;
    }
    pivot = division(array,0,size-1,choice); // dzielimy tablice na dwie czesci; pivot oznacza punkt podzialu
    if(pivot > 9) { // dzieli tablice na podtablice o rozmiarze 9
        Mixed_sort(array,pivot,depthLimit-1,choice);
    }
    if(size - 1 - pivot > 9) {
        Mixed_sort(array+pivot+1,size -1 -pivot,depthLimit-1,choice);
    }

}

template <typename Type>
void IntroSort (Type array[], int size,int choice) // funkcja sortująca
{
    int depth_limit = floor(2 * log(size)/M_LN2); // maksymalna dozwolona głębokość wywołań rekurencyjnych
    Mixed_sort(array,size,depth_limit,choice); //wywołanie funkcji Mixed_sort
    InsertionSort(array,size,choice); //wywołanie funkcji InsertionSort - uporządkowuje zbiór do końca
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
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
            IntroSort(array, size, choice);
            uniform_int_distribution<> distr2(percentage, 100);
            for (int i = size - 1; i > (size * percentage / 100); i--)
            {
                array[i] = distr2(gen); //zastąpienie liczb, aby tylko część była posortowana
            }

            clock_t timeBegin = clock();
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
            IntroSort(array, size, 3);

            clock_t timeBegin = clock();
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
    return 0; //

}