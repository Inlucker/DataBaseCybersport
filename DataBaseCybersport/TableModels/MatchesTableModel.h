#ifndef MATCHESTABLEMODEL_H
#define MATCHESTABLEMODEL_H

#include <QAbstractTableModel>
#include "EssensitiesDTO/MatchDTO.h"

class MatchesTableModel : public QAbstractTableModel
{
public:
    explicit MatchesTableModel(QObject *parent = nullptr);
    explicit MatchesTableModel(shared_ptr<vector<MatchDTO>> matches);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<MatchDTO> > matches;
};

#endif // MATCHESTABLEMODEL_H
