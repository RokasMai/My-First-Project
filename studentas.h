#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#pragma once

#include <string>
#include <list>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::list<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;
};

void dalinimoBudas1(std::list<Studentas>&, std::list<Studentas>&, std::list<Studentas>&, std::string);
void dalinimoBudas2(std::list<Studentas>&, std::list<Studentas>&, std::string);
double skaiciuotiGalutiniBala(const Studentas& studentas, const std::string& tipas);
void ivestiDuomenisRanka(std::list<Studentas>& studentai);
void skaitytiDuomenisIsFailo(std::list<Studentas>& studentai, const std::string& failoPavadinimas);
void generuotiDuomenis(std::list<Studentas>& studentai);
void generuotiFailus();
void padalintiStudentusIFailus(const std::list<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai);

#endif
