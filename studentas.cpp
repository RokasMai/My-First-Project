#include "studentas.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>

double skaiciuotiGalutiniBala(const Studentas& studentas, const std::string& tipas) {
    if (tipas == "Vid") {
        double tarpiniuVidurkis = std::accumulate(studentas.tarpiniai_rezultatai.begin(), studentas.tarpiniai_rezultatai.end(), 0.0) / studentas.tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    } else if (tipas == "Med") {
        std::vector<int> visiPazymiai = studentas.tarpiniai_rezultatai;
        visiPazymiai.push_back(studentas.egzamino_rezultatas);
        std::sort(visiPazymiai.begin(), visiPazymiai.end());

        int dydis = visiPazymiai.size();
        if (dydis % 2 == 0) {
            int vidurioIndeksas = dydis / 2;
            return (visiPazymiai[vidurioIndeksas - 1] + visiPazymiai[vidurioIndeksas]) / 2.0;
        } else {
            return visiPazymiai[dydis / 2];
        }
    } else {
        std::cout << "Netinkamas tipo, naudojamas vidurkis." << std::endl;
        double tarpiniuVidurkis = std::accumulate(studentas.tarpiniai_rezultatai.begin(), studentas.tarpiniai_rezultatai.end(), 0.0) / studentas.tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    }
}

void ivestiDuomenisRanka(std::vector<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> studentai[i].vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> studentai[i].pavarde;

        std::cout << "Iveskite " << i + 1 << "-ojo studento tarpinius rezultatus (baigti su -1): ";
        int tarpinis;
        while (true) {
            std::cin >> tarpinis;
            if (tarpinis == -1) {
                break;
            }
            studentai[i].tarpiniai_rezultatai.push_back(tarpinis);
        }

        std::cout << "Iveskite " << i + 1 << "-ojo studento egzamino rezultata: ";
        std::cin >> studentai[i].egzamino_rezultatas;
    }
}

void skaitytiDuomenisIsFailo(std::vector<Studentas>& studentai, const std::string& failoPavadinimas) {
    std::ifstream failas(failoPavadinimas);

    if (!failas) {
        std::cout << "Nepavyko atidaryti failo." << std::endl;
        return;
    }

    Studentas studentas;
    std::string eilute;
    while (std::getline(failas, eilute)) {
        std::istringstream iss(eilute);
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

void generuotiDuomenis(std::vector<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> studentai[i].vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> studentai[i].pavarde;

        for (int j = 0; j < 5; ++j) {
            int pazymys = rand() % 10 + 1;
            studentai[i].tarpiniai_rezultatai.push_back(pazymys);
        }

        studentai[i].egzamino_rezultatas = rand() % 10 + 1;
    }
}
