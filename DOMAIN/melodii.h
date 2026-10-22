#pragma once
#include <string>

class Melodie {
private:
    int id;
    std::string titlu;
    std::string artist;
    int rank;

public:
    // Constructor
    Melodie(int id, const std::string& titlu, const std::string& artist, int rank);

    // gettere
    int getId() const;
    std::string getTitlu() const;
    std::string getArtist() const;
    int getRank() const;

    // settere
    void setTitlu(const std::string& titluNou);
    void setRank(int rankNou);
};