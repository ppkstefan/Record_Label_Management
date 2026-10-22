#pragma once
#include <QAbstractTableModel>
#include "../DOMAIN/melodii.h"
#include <vector>
#include <algorithm>

class MelodieTableModel : public QAbstractTableModel {
private:
    std::vector<Melodie> melodii;

public:
    // Metodele suprascrise obligatorii
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Metoda pentru actualizarea datelor in tabel
    void setMelodii(const std::vector<Melodie>& noiMelodii);
};