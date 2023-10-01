#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;
};

double skaiciuotiGalutiniBala(const Studentas& studentas, const string& tipas) {
    if (tipas == "Vid") {
        double tarpiniuVidurkis = accumulate(studentas.tarpiniai_rezultatai.begin(), studentas.tarpiniai_rezultatai.end(), 0.0) / studentas.tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    } else if (tipas == "Med") {
        vector<int> visiPazymiai = studentas.tarpiniai_rezultatai;
        visiPazymiai.push_back(studentas.egzamino_rezultatas);
        sort(visiPazymiai.begin(), visiPazymiai.end());

        int dydis = visiPazymiai.size();
        if (dydis % 2 == 0) {
            int vidurioIndeksas = dydis / 2;
            return (visiPazymiai[vidurioIndeksas - 1] + visiPazymiai[vidurioIndeksas]) / 2.0;
        } else {
            return visiPazymiai[dydis / 2];
        }
    } else {
        cout << "Netinkamas tipo, naudojamas vidurkis." << endl;
        double tarpiniuVidurkis = accumulate(studentas.tarpiniai_rezultatai.begin(), studentas.tarpiniai_rezultatai.end(), 0.0) / studentas.tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    }
}

void ivestiDuomenisRanka(vector<Studentas>& studentai) {
    int studentuSkaicius;
    cout << "Iveskite studentu skaiciu: ";
    cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> studentai[i].vardas;

        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> studentai[i].pavarde;

        cout << "Iveskite " << i + 1 << "-ojo studento tarpinius rezultatus (baigti su -1): ";
        int tarpinis;
        while (true) {
            cin >> tarpinis;
            if (tarpinis == -1) {
                break;
            }
            studentai[i].tarpiniai_rezultatai.push_back(tarpinis);
        }

        cout << "Iveskite " << i + 1 << "-ojo studento egzamino rezultata: ";
        cin >> studentai[i].egzamino_rezultatas;
    }
}

void skaitytiDuomenisIsFailo(vector<Studentas>& studentai, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);

    if (!failas) {
        cout << "Nepavyko atidaryti failo." << endl;
        return;
    }

    Studentas studentas;
    string eilute;
    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        iss >> studentas.vardas >> studentas.pavarde;

        studentas.tarpiniai_rezultatai.clear();
        int pazymys;
        while (iss >> pazymys) {
            if (pazymys == -1) {
                break;
            }
            studentas.tarpiniai_rezultatai.push_back(pazymys);
        }

        iss >> studentas.egzamino_rezultatas;

        studentai.push_back(studentas);
    }

    failas.close();
}

void generuotiDuomenis(vector<Studentas>& studentai) {
    int studentuSkaicius;
    cout << "Iveskite studentu skaiciu: ";
    cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> studentai[i].vardas;

        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> studentai[i].pavarde;

        for (int j = 0; j < 5; ++j) {
            int pazymys = rand() % 10 + 1;
            studentai[i].tarpiniai_rezultatai.push_back(pazymys);
        }

        studentai[i].egzamino_rezultatas = rand() % 10 + 1;
    }
}

int main() {
    char pasirinkimas;
    cout << "Pasirinkite buda, kaip vesti duomenis (I - ivesti ranka, S - skaityti is failo, G - generuoti atsitiktinai): ";
    cin >> pasirinkimas;

    vector<Studentas> studentai;

    if (pasirinkimas == 'I') {
        ivestiDuomenisRanka(studentai);
    } else if (pasirinkimas == 'S') {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima (su pilnu keliasu, jei failas yra kitoje vietoje): ";
        cin >> failoPavadinimas;
        skaitytiDuomenisIsFailo(studentai, failoPavadinimas);
    } else if (pasirinkimas == 'G') {
        generuotiDuomenis(studentai);
    } else {
        cout << "Neteisingas pasirinkimas. Programa baigia darbą." << endl;
        return 1;
    }

    string skaiciavimoBudas;
    cout << "Pasirinkite skaiciavimo buda (Vid arba Med): ";
    cin >> skaiciavimoBudas;

    for (const auto& studentas : studentai) {
        cout << "Studentas: " << studentas.vardas << " " << studentas.pavarde << endl;
        cout << "Galutinis balas (" << skaiciavimoBudas << "): " << fixed << setprecision(2) << skaiciuotiGalutiniBala(studentas, skaiciavimoBudas) << endl;
        cout << endl;
    }

    return 0;
}
