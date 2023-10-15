#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits> // Pridėtas includes

int main() {
    char pasirinkimas;
    std::vector<Studentas> studentai;

    std::cout << "Pasirinkite buda, kaip vesti duomenis (I - ivesti ranka, S - skaityti is failo, G - generuoti atsitiktinai, F - generuoti failus): ";
    std::cin >> pasirinkimas;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Išvalo buferį

    if (pasirinkimas == 'I') {
        ivestiDuomenisRanka(studentai);
    } else if (pasirinkimas == 'S') {
        std::string failoPavadinimas;
        std::cout << "Iveskite failo pavadinima (su pilnu keliasu, jei failas yra kitoje vietoje): ";
        std::cin >> failoPavadinimas;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Išvalo buferį

        skaitytiDuomenisIsFailo(studentai, failoPavadinimas);

        padalintiStudentusIFailus(studentai, "failas_Vargsiukai.txt", "failas_Lyderiai.txt");
    } else if (pasirinkimas == 'G') {
        generuotiDuomenis(studentai);
    } else if (pasirinkimas == 'F') {
        generuotiFailus();
        return 0;
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

    std::cout << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << std::setw(20) << skaiciavimoBudas << std::endl;
    std::cout << std::setfill('-') << std::setw(60) << "" << std::setfill(' ') << std::endl;

    for (const auto& studentas : studentai) {
        std::cout << std::left << std::setw(20) << studentas.vardas << std::setw(20) << studentas.pavarde
                  << std::fixed << std::setprecision(2) << skaiciuotiGalutiniBala(studentas, skaiciavimoBudas) << std::endl;
    }

    return 0;
}
