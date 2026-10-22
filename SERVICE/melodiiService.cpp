#include "melodiiService.h"
#include <stdexcept>
#include <algorithm>

std::vector<Melodie> MelodieService::getAllSorted() {
    std::vector<Melodie> toate = repo.getAll();
    std::sort(toate.begin(), toate.end(), [](const Melodie& m1, const Melodie& m2) {
        return m1.getRank() > m2.getRank();
    });
    
    return toate;
}

void MelodieService::modificaMelodie(int id, const std::string& titluNou, int rankNou) {
    if (rankNou < 0 || rankNou > 10) {
        throw std::runtime_error("Rank-ul trebuie sa fie un numar intre 0 si 10!");
    }
    if (titluNou.empty()) {
        throw std::runtime_error("Titlul melodiei nu poate fi vid!");
    }

    std::vector<Melodie> toate = repo.getAll();
    auto it = std::find_if(toate.begin(), toate.end(), [id](const Melodie& m) {
        return m.getId() == id;
    });

    if (it == toate.end()) {
        throw std::runtime_error("Melodia nu a fost gasita!");
    }

    Melodie melodieActualizata(id, titluNou, it->getArtist(), rankNou);
    repo.modifica(melodieActualizata);
}

void MelodieService::stergeMelodie(int id) {
    std::vector<Melodie> toate = repo.getAll();

    auto it = std::find_if(toate.begin(), toate.end(), [id](const Melodie& m) {
        return m.getId() == id;
    });

    if (it == toate.end()) {
        throw std::runtime_error("Melodia nu exista!");
    }
    
    std::string artistCurent = it->getArtist();

    int nrMelodiiArtist = std::count_if(toate.begin(), toate.end(), [&](const Melodie& m) {
        return m.getArtist() == artistCurent;
    });

   //daca e ultima melodie
    if (nrMelodiiArtist == 1) {
        throw std::runtime_error("Aceasta este ultima melodie a artistului! Nu poate fi stearsa.");
    }

    repo.sterge(id);
}

int MelodieService::getNumarMelodiiCuRank(int rank) {
    std::vector<Melodie> toate = repo.getAll();
    return std::count_if(toate.begin(), toate.end(), [rank](const Melodie& m) {
        return m.getRank() == rank;
    });
}

std::vector<int> MelodieService::getFrecventeRankuri() {
    std::vector<int> frecvente(11, 0);
    std::vector<Melodie> toate = repo.getAll();
    
    for (const auto& m : toate) {
        int r = m.getRank();
        if (r >= 0 && r <= 10) {
            frecvente[r]++;
        }
    }
    return frecvente;
}