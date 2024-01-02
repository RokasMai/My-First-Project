#include "studentas.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <chrono>

void wtf(std::vector<Studentas>& s, int num) {
    std::string name = "out" ;
    name.append(std::to_string(num));
    std::cout << name << std::endl;
    std::ofstream f(name);

    for (const Studentas& stud : s) {
        f << stud.vardas << " " << stud.pavarde << " " << skaiciuotiGalutiniBala(stud, "Vid") << std::endl;
    }

    f.close();
}

void dalinimoBudas1(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& balleriai, std::string skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](Studentas& s){
        return skaiciuotiGalutiniBala(s, skBudas) >= 5;
    });

    vargsai.assign(studentai.begin(), pirmasKietas);
    balleriai.assign(pirmasKietas, studentai.end());

    wtf(vargsai, 1);
    wtf(balleriai, 2);
}

void dalinimoBudas2(std::vector<Studentas>& studentai, std::vector<Studentas>& balleriai, std::string skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](Studentas& s){
        return skaiciuotiGalutiniBala(s, skBudas) >= 5;
    });

    balleriai.assign(pirmasKietas, studentai.end());
    studentai.resize(studentai.size() - balleriai.size());
    studentai.shrink_to_fit();

    wtf(studentai, 3);
    wtf(balleriai, 4);
}

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
void generuotiFailus() {
    const std::vector<int> irasuSkaiciai = {1000, 10000, 100000, 1000000, 10000000};
    const std::string sabloninisVardas = "Vardas";
    const std::string sabloninePavarde = "Pavarde";

    for (int irasuSkaicius : irasuSkaiciai) {
        auto start = std::chrono::high_resolution_clock::now();

        std::string failoPavadinimas = "failas_" + std::to_string(irasuSkaicius) + ".txt";
        std::ofstream failas(failoPavadinimas);

        if (!failas) {
            std::cout << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
            return;
        }

        for (int i = 1; i <= irasuSkaicius; ++i) {
            failas << sabloninisVardas << i << " " << sabloninePavarde << i;

            for (int j = 0; j < 5; ++j) {
                int pazymys = rand() % 10 + 1;
                failas << " " << pazymys;
            }

            int egzaminoBalas = rand() % 10 + 1;
            failas << " " << egzaminoBalas << std::endl;
        }

        failas.close();
        auto end = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << "Sukurtas failas: " << failoPavadinimas  << ", uztruko " << diff << "ms" << std::endl;
    }
}
void padalintiStudentusIFailus(const std::vector<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai) {
    std::ofstream vargsiukaiFailas(failasVargsiukai);
    std::ofstream lyderiaiFailas(failasLyderiai);

    if (!vargsiukaiFailas || !lyderiaiFailas) {
        std::cout << "Nepavyko sukurti failu." << std::endl;
        return;
    }

    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiGalutiniBala(studentas, "Vid");
        if (galutinis < 5.0) {
            vargsiukaiFailas << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        } else {
            lyderiaiFailas << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }
    }

    vargsiukaiFailas.close();
    lyderiaiFailas.close();
}
