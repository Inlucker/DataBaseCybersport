#ifndef PLAYERSTABLEMODEL_H
#define PLAYERSTABLEMODEL_H

#include <QAbstractTableModel>
#include "Essensities/PlayerBL.h"

class PlayersTableModel : public QAbstractTableModel
{
public:
    explicit PlayersTableModel(QObject *parent = nullptr);
    explicit PlayersTableModel(shared_ptr<vector<PlayerBL>> plrs);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<PlayerBL> > players;
};

#endif // PLAYERSTABLEMODEL_H
