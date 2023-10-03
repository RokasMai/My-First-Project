#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

int main() {
    char pasirinkimas;
    std::cout << "Pasirinkite buda, kaip vesti duomenis (I - ivesti ranka, S - skaityti is failo, G - generuoti atsitiktinai): ";
    std::cin >> pasirinkimas;

    std::vector<Studentas> studentai;

    if (pasirinkimas == 'I') {
        ivestiDuomenisRanka(studentai);
    } else if (pasirinkimas == 'S') {
        std::string failoPavadinimas;
        std::cout << "Iveskite failo pavadinima (su pilnu keliasu, jei failas yra kitoje vietoje): ";
        std::cin >> failoPavadinimas;
        skaitytiDuomenisIsFailo(studentai, failoPavadinimas);
    } else if (pasirinkimas == 'G') {
        generuotiDuomenis(studentai);
    } else {
        std::cout << "Neteisingas pasirinkimas. Programa baigia darbą." << std::endl;
        return 1;
    }

    std::string skaiciavimoBudas;
    std::cout << "Pasirinkite skaiciavimo buda (Vid arba Med): ";
    std::cin >> skaiciavimoBudas;

    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas < b.vardas;
    });

    for (const auto& studentas : studentai) {
        std::cout << "Studentas: " << studentas.vardas << " " << studentas.pavarde << std::endl;
        std::cout << "Galutinis balas (" << skaiciavimoBudas << "): "
                  << std::fixed << std::setprecision(2) << skaiciuotiGalutiniBala(studentas, skaiciavimoBudas) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
