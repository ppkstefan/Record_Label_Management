#include "MelodieTableModel.h"

int MelodieTableModel::rowCount(const QModelIndex& parent) const {
    return melodii.size();
}

int MelodieTableModel::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant MelodieTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        Melodie m = melodii[index.row()];
        
        switch (index.column()) {
            case 0: return QString::number(m.getId());
            case 1: return QString::fromStdString(m.getTitlu());
            case 2: return QString::fromStdString(m.getArtist());
            case 3: return QString::number(m.getRank());
            case 4: {
                // calcul frecventa rank
                int rankCurent = m.getRank();
                int count = std::count_if(melodii.begin(), melodii.end(), [rankCurent](const Melodie& mel) {
                    return mel.getRank() == rankCurent;
                });
                return QString::number(count);
            }
            default: break;
        }
    }
    return QVariant();
}

QVariant MelodieTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Titlu";
            case 2: return "Artist";
            case 3: return "Rank";
            case 4: return "Acelasi Rank";
            default: break;
        }
    }
    return QVariant();
}

void MelodieTableModel::setMelodii(const std::vector<Melodie>& noiMelodii) {
    beginResetModel();
    melodii = noiMelodii;
    endResetModel();
}