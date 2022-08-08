#include "funkcje.h"

const string nazwa_pliku = "wyrazenie.txt"; // ustalanie sciezki do pliku przechowującego wyrazenie
Argument *stos = nullptr; // inicjowanie stosu


void modyfikujWyrazenie() {
    system("cls");
    string wyrazenie = pobierzZawartosc(nazwa_pliku.c_str());
    if (wyrazenie == "") {
        cout << "Wprowadz wyrazenie: " << endl;
        edytujZawartosc(nazwa_pliku);
    }
    else {
        char a;
        do {
            cout << "Czy chcesz edytowac wyrazenie: '" << wyrazenie << "' (Y/N) ";
            cin >> a;
        }
        while (!(a == 'Y' || a == 'N' || a == 'n' || a == 'y'));

        if (a == 'N' || a == 'n');
        else {
            cout << "Edytuj wyrazenie: "<< wyrazenie << endl << setw(18) << "| ";
            edytujZawartosc(nazwa_pliku);
        }
    }
    obliczWyrazenie();
    wrocDoMenu();
}

void obliczWyrazenie() {
    cout << "Obliczam..." << endl;
    string wyrazenie = pobierzZawartosc(nazwa_pliku);
    string liczba = "";
    int n = wyrazenie.length();
    char T[n];
    double x, wynik = 0.0;
    for (int i = 0; i < n; i++) {
        T[i] = wyrazenie[i];
    }

    for (int i = 0; i < n; i++) {
        if ((T[i] >= 48 && T[i] <= 57) || T[i] == 46 || T[i] == 44) {
            if ((i > 0 && T[i-1] == 32  ) || i == 0)
                liczba = liczba + '0';
            liczba = liczba + T[i];
        }
        else if (T[i] == 32) {
            if (!(i > 0 && T[i-1] == 32)) {
                x = zamienStringNaDouble(liczba);
                odlozNaStos(x);
            }
            liczba = "";
        }
        //if wyrazenie[i] jest zmienna
        //if wyrazenie[i] jest operatorem
    }
    wypiszStos(stos);
    cout << wyrazenie << " = " << wynik << endl;
    wyczyscStos(stos);
    char a;
    do {
        cout << "Jesli chcesz wrocic do menu wcisnij 'T' i  ENTER" << endl;
        cin.ignore();
        cin >> a;
    } while (a != 'T');

}

void modyfikujZmienne() {
    cout << "Opcja nr 2." << endl;

}

double zamienStringNaDouble(string napis) {
    int n = napis.length();
    char T[n];
    int counter = 0, commaIndex = n, exponent = 0;
    double x = 0.0;
    for (int i = 0; i < n; i++)
        T[i] = napis[i];
    for (int i = 0; i < n; i++) {
        if (T[i] == 46 || T[i] == 44) {
            counter++;
            commaIndex = i;
        }
        if (counter >= 2)
            break;
    }
    if (counter == 0) {
        for (int i = n-1; i >= 0; i--) {
            x += (double(T[i] - 48))*pow(10, exponent);
            exponent++;
        }
        exponent = 0;
    }
    else if (counter == 1) {
        for (int i = commaIndex-1; i >= 0; i--) {
            x += (double(T[i] - 48))*pow(10, exponent);
            exponent++;
        }
        exponent = 0;
        for (int i = commaIndex+1; i < n; i++) {
            exponent--;
            x += (double(T[i] - 48))*pow(10, exponent);
        }
    }
    else {
      cout << "Blad!: Bledny zapis liczby -> za duzo kropek lub/i przecinkow!" << endl
           << "counter = " << counter << endl;
      x = 0.0;
      //modyfikujWyrazenie(); // nie wiem, czy program nie zapętli się jakoś dziwnie
    }
    return x;
}
void odlozNaStos(double x) {
    dodajElement(stos, x);
}
