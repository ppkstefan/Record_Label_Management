#include "melodiiRepo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::getline;
using std::string;

MelodieRepo::MelodieRepo(const std::string& filename) : filename{ filename } {
    loadFromFile();
}

void MelodieRepo::loadFromFile() {
    melodii.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;


        std::stringstream ss(line);
        string idStr, titlu, artist, rankStr;

        getline(ss, idStr, ',');
        getline(ss, titlu, ',');
        getline(ss, artist, ',');
        getline(ss, rankStr, ',');


        if (!idStr.empty() && !rankStr.empty()) {
            melodii.push_back(Melodie(std::stoi(idStr), titlu, artist, std::stoi(rankStr)));
        }
    }
    fin.close();
}

void MelodieRepo::saveToFile() {
    std::ofstream fout(filename);
    for (const auto& m : melodii) {
        fout << m.getId() << ","
             << m.getTitlu() << ","
             << m.getArtist() << ","
             << m.getRank() << "\n";
    }
    fout.close();
}

std::vector<Melodie> MelodieRepo::getAll() {
    return melodii;
}

void MelodieRepo::modifica(const Melodie& m) {
    bool gasit = false;
    for (auto& mel : melodii) {
        if (mel.getId() == m.getId()) {
            mel = m;
            gasit = true;
            break;
        }
    }

    if (!gasit) {
        throw std::runtime_error("Melodia nu exista in baza de date!");
    }

    saveToFile();
}

void MelodieRepo::sterge(int id) {

    auto it = std::remove_if(melodii.begin(), melodii.end(), [id](const Melodie& m) {
        return m.getId() == id;
    });

    if (it == melodii.end()) {
        throw std::runtime_error("Melodia pe care incercati sa o stergeti nu exista!");
    }

    // Stergem efectiv elementul din vector
    melodii.erase(it, melodii.end());

    saveToFile();
}