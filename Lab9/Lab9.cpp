#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student{
    string imie;
    string nazwisko;
    string plec;
    string ocena;
    string email;
};

void zad1() {
    ifstream file;
    file.open("test1.txt");
    string line, linia;
    vector<string> wynik;
    while (!file.eof()) {
        getline(file, line);
        wynik.push_back(line);
    }
    file.close();
    for (int i = 0; i < wynik.size(); i++) {
        linia = wynik.at(i);
        for (int j = 0; j < linia.size(); j++) {
            if (linia[j] == '/' && linia[j + 1] == '/')
                break;
            cout << linia[j];
        }
        cout << endl;
    }
}

void zad2() {
    int liczba = 0;
    int suma = 0;
    string pom;
    while (suma < 21) {
        try {
            cout << "Podaj liczbe: " << endl;
            cin >> pom;
            liczba = stoi(pom);
            suma = suma + liczba;
            if (suma > 21)
                throw 1;
        }
        catch (invalid_argument const& ex) {
            cout << "zly typ danych" << endl << "Sprobuj jeszcze raz: " << endl;
        }
        catch (int w1) {
            cout << "za duza liczba!" << endl;
            cout << "Sprobuj jeszcze raz: " << endl;
            suma = suma - liczba;
        }
        catch (...) {
            cout << "zle dane" << endl;
        }
    }
    if (suma == 21)
        cout << "Oczko!" << endl;
}
void pokaz(vector<Student> studenci) {
    for (int i = 0; i < studenci.size(); i++) {
        cout << studenci[i].imie << " ";
        cout << studenci[i].nazwisko << " ";
        cout << studenci[i].plec << " ";
        cout << studenci[i].ocena << " ";
        cout << studenci[i].email << endl;
    }
}

bool validate(string imie, string nazwisko, string plec, string ocena, string email) {
    bool error = false;
    for (int i = 0; i < imie.size(); i++) {
        if (!isalpha(imie[i]) || !isupper(imie[i]))
            error = true;
    }
    for (int i = 0; i < nazwisko.size(); i++) {
        if (!isalpha(nazwisko[i]) || !isupper(nazwisko[i]))
            error = true;
    }
    for (int i = 0; i < email.size(); i++) {
        if (email[i] == '@') {
            error = false;
            break;
        }
        error = true;
    }
    if (!(plec[0] == 'K' || plec[0] == 'M'))
        error = true;
    if (!isdigit(ocena[0]))
        error = true;
    return error;
}

void zapis(Student student, string plik) {
    ofstream file2;
    file2.open(plik, fstream::app);

    file2 << student.imie << ";";
    file2 << student.nazwisko << ";";
    file2 << student.plec << ";";
    file2 << student.ocena << ";";
    file2 << student.email << "\n";
}
bool pom(Student s1, Student s2) {
    return (s1.ocena < s2.ocena);
}

vector<Student> sort(vector<Student> studenci) {
    sort(studenci.begin(), studenci.end(), pom);
    for (int i = 0; i < studenci.size(); i++) {
        cout << studenci[i].imie << " ";
        cout << studenci[i].nazwisko << " ";
        cout << studenci[i].plec << " ";
        cout << studenci[i].ocena << " ";
        cout << studenci[i].email << " ";
        cout << endl;
    }
    return studenci;
}
void zad3() {
    try {
        string plik, imie, nazwisko, plec, ocena, email, pierwsza;
        ifstream file;
        vector<string> linia;
        Student student;
        vector<Student> studenci;
        string nazwiskoDoSzukania;
        int y;
        bool error = false;
        file.open("dane.csv");
        getline(file, pierwsza);
        while (!file.eof()) {
            linia.push_back(plik);
            getline(file, imie, ';');
            getline(file, nazwisko, ';');
            getline(file, plec, ';');
            getline(file, ocena, ';');
            getline(file, email, '\n');
            
            error = validate(imie, nazwisko, plec, ocena, email);
            student.imie = imie;
            student.nazwisko = nazwisko;
            student.plec = plec;
            student.ocena = ocena;
            student.email = email;

            if (email == "")
                error = true;
            if (!error)
                studenci.push_back(student);
        }
        int x = 0;
        cout << "1. Wyswietlanie" << endl;
        cout << "2. Dodawanie" << endl;
        cout << "3. Szukanie" << endl;
        cout << "4. Dielenie" << endl;
        cout << "5. Mniej niz liczba" << endl;
        cout << "6. Posortowanie wzgledem oceny rosnaco" << endl;
        cin >> x;
        switch (x) {
            case 1:
                cout << "wyswietlanie studentow: " << endl;
                pokaz(studenci);
                break;
            case 2:
                error = false;
                cout << "zapisywanie osoby do ksiazki: " << endl;
                cout << "Podaj imie: " << endl;
                cin >> imie;
                cout << "Podaj nazwisko: " << endl;
                cin >> nazwisko;
                cout << "Podaj plec: " << endl;
                cin >> plec;
                cout << "Podaj ocene: " << endl;
                cin >> ocena;
                cout << "Podaj email: " << endl;
                cin >> email;
                
                error = validate(imie, nazwisko, plec, ocena, email);
                student.imie = imie;
                student.nazwisko = nazwisko;
                student.plec = plec;
                student.ocena = ocena;
                student.email = email;
                if (error)
                    cout << "podano zle dane";
                if (!error)
                    studenci.push_back(student);
                zapis(student,"dane.csv");
                break;
            case 3:
                cout << "Podaj nazwisko do szukania: " << endl;
                cin >> nazwiskoDoSzukania;
                for (int i = 0; i < studenci.size();i++) {
                    if (studenci[i].nazwisko == nazwiskoDoSzukania) {
                        cout << studenci[i].imie;
                        cout << studenci[i].nazwisko;
                        cout << studenci[i].plec;
                        cout << studenci[i].ocena;
                        cout << studenci[i].email;
                    }
                }
                break;
            case 4:
                for (int i = 0; i < studenci.size(); i++) {
                    if (studenci[i].plec == "K")
                        zapis(studenci[i], "k.csv");
                    else
                        zapis(studenci[i], "m.csv");
                }
                break;
            case 5:
                cout << "Podaj liczbe do wyswietlenia" << endl;
                cin >> y;
                if (y <= studenci.size()) {
                    for (int i = 0; i < y; i++) {
                        cout << studenci[i].imie << " ";
                        cout << studenci[i].nazwisko << " ";
                        cout << studenci[i].plec << " ";
                        cout << studenci[i].ocena << " ";
                        cout << studenci[i].email << endl;
                    }
                }
                else
                    cout << "Podano duza liczbe studentow";
                break;
            case 6:
                sort(studenci);
                break;
        }
    }
    catch (exception& ex) {
        cout << "Blad! " << endl;
        cout << ex.what();
    }
}

int main() {
    //zad1();
    //zad2();
    zad3();
    return 0;
}
