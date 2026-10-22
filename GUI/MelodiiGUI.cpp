#include "MelodiiGUI.h"
#include <QMessageBox>
#include <QLabel>

MelodieGUI::MelodieGUI(MelodieService& srv) : srv{ srv } {
    initGUI();
    model = new MelodieTableModel();
    tabel->setModel(model);
    
    incarcaDate();
    connectSignals();
}

void MelodieGUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    //Partea de Sus:
    QHBoxLayout* topLayout = new QHBoxLayout();
    
    //Tabelul
    tabel = new QTableView();
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setSelectionMode(QAbstractItemView::SingleSelection);
    topLayout->addWidget(tabel);
    
    //Formularul de Editare si Butoane
    QVBoxLayout* formLayout = new QVBoxLayout();
    
    QFormLayout* detaliiLayout = new QFormLayout();
    txtTitlu = new QLineEdit();
    
    //slider ul
    sliderRank = new QSlider(Qt::Horizontal);
    sliderRank->setMinimum(0);
    sliderRank->setMaximum(10);
    sliderRank->setTickPosition(QSlider::TicksBelow);
    sliderRank->setTickInterval(1);
    
    detaliiLayout->addRow("Titlu:", txtTitlu);
    detaliiLayout->addRow("Rank (0-10):", sliderRank);
    formLayout->addLayout(detaliiLayout);
    
    //Butoanele
    btnUpdate = new QPushButton("Update Melodie");
    btnDelete = new QPushButton("Delete Melodie");
    formLayout->addWidget(btnUpdate);
    formLayout->addWidget(btnDelete);
    
    topLayout->addLayout(formLayout);

    //prima jumatate la fereastra mare
    mainLayout->addLayout(topLayout);
    
    //Zona de desenare a barelor de jos
    desenBare = new DesenWidget();
    mainLayout->addWidget(new QLabel("Frecventa rank-uri:")); // Un titlu mic
    mainLayout->addWidget(desenBare);
}

void MelodieGUI::incarcaDate() {
    //sorteaza melodiile dupa rank
    model->setMelodii(srv.getAllSorted());

    // trimite frecventele ptr redesenare
    desenBare->setFrecvente(srv.getFrecventeRankuri());
}

void MelodieGUI::connectSignals() {
    //Selectia
    QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (tabel->selectionModel()->selectedIndexes().isEmpty()) return;
        
        int row = tabel->selectionModel()->selectedIndexes().at(0).row();
        
        //id 0, titlu 1, rank 3
        int id = model->data(model->index(row, 0)).toInt();
        QString titlu = model->data(model->index(row, 1)).toString();
        int rank = model->data(model->index(row, 3)).toInt();
        
        idMelodieSelectata = id;
        txtTitlu->setText(titlu);
        sliderRank->setValue(rank); 
    });

    // Buton UPDATE
    QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
        if (idMelodieSelectata == -1) {
            QMessageBox::warning(this, "Eroare", "Selecteaza o melodie din tabel!");
            return;
        }
        try {
            std::string titluNou = txtTitlu->text().toStdString();
            int rankNou = sliderRank->value(); //
            
            srv.modificaMelodie(idMelodieSelectata, titluNou, rankNou);
            incarcaDate(); //refresh
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare Update", e.what());
        }
    });

    // Buton DELETE
    QObject::connect(btnDelete, &QPushButton::clicked, [this]() {
        if (idMelodieSelectata == -1) {
            QMessageBox::warning(this, "Eroare", "Selecteaza o melodie din tabel!");
            return;
        }
        try {
            srv.stergeMelodie(idMelodieSelectata);
            incarcaDate();

            idMelodieSelectata = -1;
            txtTitlu->clear();
            sliderRank->setValue(0);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Nu se poate sterge!", e.what());
        }
    });
}