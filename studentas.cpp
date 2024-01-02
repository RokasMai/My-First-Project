#include "studentas.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <chrono>

void wtf(std::list<Studentas>& s, int num) {
    std::string name = "out" ;
    name.append(std::to_string(num));
    std::cout << name << std::endl;
    std::ofstream f(name);

    for (const Studentas& stud : s) {
        f << stud.vardas << " " << stud.pavarde << " " << skaiciuotiGalutiniBala(stud, "Vid") << std::endl;
    }

    f.close();
}

void dalinimoBudas1(std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& balleriai, std::string skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](Studentas& s){
        return skaiciuotiGalutiniBala(s, skBudas) >= 5;
    });

    vargsai.assign(studentai.begin(), pirmasKietas);
    balleriai.assign(pirmasKietas, studentai.end());

    wtf(vargsai, 1);
    wtf(balleriai, 2);
}

void dalinimoBudas2(std::list<Studentas>& studentai, std::list<Studentas>& balleriai, std::string skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](Studentas& s){
        return skaiciuotiGalutiniBala(s, skBudas) >= 5;
    });

    balleriai.assign(pirmasKietas, studentai.end());
    studentai.resize(studentai.size() - balleriai.size());


    wtf(studentai, 3);
    wtf(balleriai, 4);
}

double skaiciuotiGalutiniBala(const Studentas& studentas, const std::string& tipas) {
    if (tipas == "Vid") {
        if (studentas.tarpiniai_rezultatai.empty()) {
            return 0.0; // or handle the case when there are no intermediate results
        }

        double tarpiniuVidurkis = std::accumulate(studentas.tarpiniai_rezultatai.begin(), studentas.tarpiniai_rezultatai.end(), 0.0)
                                 / static_cast<double>(studentas.tarpiniai_rezultatai.size());
        return tarpiniuVidurkis;
    } else if (tipas == "Med") {
        std::list<int> visiPazymiai = studentas.tarpiniai_rezultatai;
        visiPazymiai.push_back(studentas.egzamino_rezultatas);
        visiPazymiai.sort();

        int dydis = visiPazymiai.size();
        auto it = visiPazymiai.begin();

        std::advance(it, dydis / 2);

        if (dydis % 2 == 0) {
            int vidurioIndeksas = dydis / 2;
            return (*std::prev(it) + *it) / 2.0;
        } else {
            return *it;
        }
    } else {
        std::cout << "Netinkamas tipo, naudojamas vidurkis." << std::endl;
        return skaiciuotiGalutiniBala(studentas, "Vid"); // fallback to average if the type is invalid
    }
}

void ivestiDuomenisRanka(std::list<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    for (int i = 0; i < studentuSkaicius; ++i) {
        Studentas naujasStudentas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> naujasStudentas.vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> naujasStudentas.pavarde;

        std::cout << "Iveskite " << i + 1 << "-ojo studento tarpinius rezultatus (baigti su -1): ";
        int tarpinis;
        while (true) {
            std::cin >> tarpinis;
            if (tarpinis == -1) {
                break;
            }
            naujasStudentas.tarpiniai_rezultatai.push_back(tarpinis);
        }

        std::cout << "Iveskite " << i + 1 << "-ojo studento egzamino rezultata: ";
        std::cin >> naujasStudentas.egzamino_rezultatas;

        studentai.push_back(naujasStudentas);
    }
}

void skaitytiDuomenisIsFailo(std::list<Studentas>& studentai, const std::string& failoPavadinimas) {
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

void generuotiDuomenis(std::list<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    for (int i = 0; i < studentuSkaicius; ++i) {
        Studentas naujasStudentas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> naujasStudentas.vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> naujasStudentas.pavarde;

        for (int j = 0; j < 5; ++j) {
            int pazymys = rand() % 10 + 1;
            naujasStudentas.tarpiniai_rezultatai.push_back(pazymys);
        }

        naujasStudentas.egzamino_rezultatas = rand() % 10 + 1;

        studentai.push_back(naujasStudentas);
    }
}
void generuotiFailus() {
    const std::list<int> irasuSkaiciai = {1000, 10000, 100000, 1000000, 10000000};
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
void padalintiStudentusIFailus(const std::list<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai) {
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
