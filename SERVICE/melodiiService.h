#pragma once
#include "../REPO/melodiiRepo.h"
#include <string>
#include <vector>
#include <map>

class MelodieService {
private:
    MelodieRepo& repo;

public:
    // Constructor
    MelodieService(MelodieRepo& r) : repo{ r } {}

    // Returneaza lista de melodii sortata dupa rank
    std::vector<Melodie> getAllSorted();

    // Actualizeaza titlul si rank-ul unei melodii
    void modificaMelodie(int id, const std::string& titluNou, int rankNou);

    // Sterge o melodie, dupa regula
    void stergeMelodie(int id);

    // Returneaza numarul de melodii care au un anumit rank
    int getNumarMelodiiCuRank(int rank);

    // Returneaza un vector cu 11 elemente, care numara frecventele
    std::vector<int> getFrecventeRankuri();
};