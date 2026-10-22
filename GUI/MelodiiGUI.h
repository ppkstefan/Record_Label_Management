#pragma once
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPainter>
#include "../SERVICE/melodiiService.h"
#include "MelodieTableModel.h"

class DesenWidget : public QWidget {
private:
    std::vector<int> frecvente;
public:
    DesenWidget() {
        setMinimumHeight(150);
    }
    
    void setFrecvente(const std::vector<int>& f) {
        frecvente = f;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter p(this);
        if (frecvente.empty()) return;

        int latimeBara = width() / 11;
        
        for (int i = 0; i <= 10; i++) {
            //30 pixeli pe pe melodie
            int inaltimeBara = frecvente[i] * 20;
            
            //x, y, latime , inaltime
            p.drawRect(i * latimeBara, height() - inaltimeBara, latimeBara, inaltimeBara);
            
            //textul
            p.drawText(i * latimeBara + (latimeBara/3), height() - 2, QString::number(i));
        }
    }
};

//FEREASTRA PRINCIPALA
class MelodieGUI : public QWidget {
private:
    MelodieService& srv;
    MelodieTableModel* model;
    
    // Elemente vizuale
    QTableView* tabel;
    QLineEdit* txtTitlu;
    QSlider* sliderRank;
    QPushButton* btnUpdate;
    QPushButton* btnDelete;
    
    // Elementul de desen
    DesenWidget* desenBare;
    
    int idMelodieSelectata = -1; // retinem pe ce am dat click

    void initGUI();
    void connectSignals();
    void incarcaDate();

public:
    MelodieGUI(MelodieService& srv);
};