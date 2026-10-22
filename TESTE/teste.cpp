//
// Created by PPK on 6/27/2026.
//

#include "Teste.h"
#include "../DOMAIN/melodii.h"
#include "../REPO/melodiiRepo.h"
#include "../SERVICE/melodiiService.h"
#include <cassert>
#include <fstream>
#include <iostream>

void Teste::testeDomain() {
    Melodie m(1, "Bohemian", "Queen", 10);
    assert(m.getId() == 1);
    assert(m.getTitlu() == "Bohemian");
    assert(m.getArtist() == "Queen");
    assert(m.getRank() == 10);

    m.setTitlu("Radio");
    m.setRank(9);
    assert(m.getTitlu() == "Radio");
    assert(m.getRank() == 9);
}

void Teste::testeRepo() {
    std::ofstream fout("test_melodii.txt");
    fout << "1,Melodie1,Artist1,5\n";
    fout << "2,Melodie2,Artist2,10\n";
    fout.close();

    MelodieRepo repo("test_melodii.txt");
    assert(repo.getAll().size() == 2);
    Melodie mModificata(1, "Modificat", "Artist1", 8);
    repo.modifica(mModificata);
    assert(repo.getAll()[0].getTitlu() == "Modificat");
    assert(repo.getAll()[0].getRank() == 8);

    try {
        repo.modifica(Melodie(99, "Inexistent", "Nimeni", 5));
        assert(false);
    } catch (...) { assert(true); }

    // Test stergere
    repo.sterge(2);
    assert(repo.getAll().size() == 1);

    // Test exceptie stergere
    try {
        repo.sterge(99);
        assert(false);
    } catch (...) { assert(true); }
}

void Teste::testeService() {
    std::ofstream fout("test_srv.txt");
    fout << "1,Melodie1,Art1,5\n";
    fout << "2,Melodie2,Art1,10\n";
    fout << "3,Melodie3,Art2,7\n";
    fout.close();

    MelodieRepo repo("test_srv.txt");
    MelodieService srv(repo);

    // Test Sortare
    auto sorted = srv.getAllSorted();
    assert(sorted[0].getId() == 2);
    assert(sorted[1].getId() == 3);
    assert(sorted[2].getId() == 1);

    // Test modificare si validari
    srv.modificaMelodie(1, "TitluNou", 8);
    assert(repo.getAll()[0].getRank() == 8);

    try { srv.modificaMelodie(1, "Titlu", 11); assert(false); } catch (...) { assert(true); } // rank invalid
    try { srv.modificaMelodie(1, "", 5); assert(false); } catch (...) { assert(true); } // titlu invalid

    // Test stergere
    srv.stergeMelodie(2);
    assert(repo.getAll().size() == 2);

    try {
        srv.stergeMelodie(3);
        assert(false);
    } catch (...) { assert(true); }

    // Test statistici
    assert(srv.getNumarMelodiiCuRank(8) == 1);

    auto frecvente = srv.getFrecventeRankuri();
    assert(frecvente[8] == 1);
    assert(frecvente[10] == 0);
}

void Teste::ruleazaToateTestele() {
    testeDomain();
    testeRepo();
    testeService();
    std::cout << "Toate testele au trecut cu succes!\n";
}