#ifndef TOURNAMENTSTABLEMODEL_H
#define TOURNAMENTSTABLEMODEL_H

#include <QAbstractTableModel>
#include "EssensitiesDTO/TournamentDTO.h"

class TournamentsTableModel : public QAbstractTableModel
{
public:
    explicit TournamentsTableModel(QObject *parent = nullptr);
    explicit TournamentsTableModel(shared_ptr<vector<TournamentDTO>> tournaments);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<TournamentDTO> > tournaments;
};

#endif // TOURNAMENTSTABLEMODEL_H
