#pragma once
#include "../DOMAIN/melodii.h"
#include <vector>
#include <string>

class MelodieRepo {
private:
    std::string filename;
    std::vector<Melodie> melodii;


    void loadFromFile();
    void saveToFile();

public:
    // Constructorul incarca automat datele din fisier
    MelodieRepo(const std::string& filename);

    // Returneaza toate melodiile curente
    std::vector<Melodie> getAll();

    // Actualizeaza o melodie existenta (cautand dupa ID) si salveaza in fisier
    void modifica(const Melodie& m);

    // Sterge o melodie dupa ID si salveaza modificarea in fisier
    void sterge(int id);
};