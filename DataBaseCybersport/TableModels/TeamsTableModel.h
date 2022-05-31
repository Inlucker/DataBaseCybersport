#ifndef TEAMSTABLEMODEL_H
#define TEAMSTABLEMODEL_H

#include <QAbstractTableModel>
#include "EssensitiesDTO/TeamDTO.h"

class TeamsTableModel : public QAbstractTableModel
{
public:
    explicit TeamsTableModel(QObject *parent = nullptr);
    //explicit TeamsTableModel(shared_ptr<vector<TeamDTO>> teams);
    //int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<TeamDTO> > teams;
};

#endif // TEAMSTABLEMODEL_H
