#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>

using namespace std;

struct zmogus {
    string vardas;
    string pavarde;
    vector<int> nd;
    float rezultatas;  // Pridėtas rezultato kintamasis
};

bool palygintiPagalPavarde(const zmogus& zmogus1, const zmogus& zmogus2) {
    return zmogus1.pavarde < zmogus2.pavarde;
}

float skaiciuotiVidurki(vector<int>& pazymiai) {
    int suma = accumulate(pazymiai.begin(), pazymiai.end(), 0);
    return static_cast<float>(suma) / pazymiai.size();
}
float skaiciuotiMediana(vector<int>& pazymiai) {
    size_t dydis = pazymiai.size();
    sort(pazymiai.begin(), pazymiai.end());

    if (dydis % 2 == 0) {
        // Lyginis skaičius duomenų, medianą randame vidurinių elementų vidurkį
        int vidurys1 = pazymiai[dydis / 2 - 1];
        int vidurys2 = pazymiai[dydis / 2];
        return static_cast<float>(vidurys1 + vidurys2) / 2.0;
    } else {
        // Nelyginis skaičius duomenų, medianą randame tiesiog vidurinį elementą
        return pazymiai[dydis / 2];
    }
}

float skaiciuotiGalutini(vector<int>& nd, int egzaminas, bool naudotiVidurki) {
    if (naudotiVidurki) {
        nd.push_back(egzaminas);  // Pridedame egzamino balą prie namų darbų pažymių
        return skaiciuotiVidurki(nd);
    } else {
        nd.push_back(egzaminas);  // Pridedame egzamino balą prie namų darbų pažymių
        return skaiciuotiMediana(nd);
    }
}



int main() {
    zmogus laikinas;
    vector<zmogus> grupe;
    int zmoniu_sk;
    string skaiciavimoMetodas;

    cout << "Iveskite mokiniu skaiciu: " << endl;
    cin >> zmoniu_sk;

    cout << "Pasirinkite skaiciavimo metoda: (Vid) - vidurkis, (Med) - mediana" << endl;
    cin >> skaiciavimoMetodas;

    bool naudotiVidurki = (skaiciavimoMetodas == "Vid");

    for (int j = 0; j < zmoniu_sk; j++) {
        cout << "Iveskite varda ir pavarde " << endl;
        cin >> laikinas.vardas >> laikinas.pavarde;

        cout << "Kiek namu darbu pazymiu turi zmogus? " << endl;
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            int k;
            cout << "Iveskite " << i + 1 << " pazymi " << endl;
            cin >> k;
            laikinas.nd.push_back(k);
        }

        cout << "Iveskite egzamino bala " << endl;
        cin >> laikinas.rezultatas;

        laikinas.rezultatas = skaiciuotiGalutini(laikinas.nd, laikinas.rezultatas, naudotiVidurki);

        grupe.push_back(laikinas);
        laikinas.nd.clear();

        sort(grupe.begin(), grupe.end(), palygintiPagalPavarde);

    }

    for (auto& a : grupe) {
        cout << a.vardas << " " << a.pavarde << " " << setprecision(3) <<a.rezultatas << endl;
    }

    return 0;
}
