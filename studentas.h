#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#pragma once

#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;
};

double skaiciuotiGalutiniBala(const Studentas& studentas, const std::string& tipas);
void ivestiDuomenisRanka(std::vector<Studentas>& studentai);
void skaitytiDuomenisIsFailo(std::vector<Studentas>& studentai, const std::string& failoPavadinimas);
void generuotiDuomenis(std::vector<Studentas>& studentai);
void generuotiFailus();
void padalintiStudentusIFailus(const std::vector<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai);

#endif
