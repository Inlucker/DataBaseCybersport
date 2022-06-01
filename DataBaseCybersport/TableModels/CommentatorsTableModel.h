#ifndef COMMENTATORSTABLEMODEL_H
#define COMMENTATORSTABLEMODEL_H

#include <QAbstractTableModel>
#include "EssensitiesDTO/CommentatorDTO.h"

class CommentatorsTableModel : public QAbstractTableModel
{
public:
    explicit CommentatorsTableModel(QObject *parent = nullptr);
    explicit CommentatorsTableModel(shared_ptr<vector<CommentatorDTO>> comms);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<CommentatorDTO> > commenatros;
};

#endif // COMMENTATORSTABLEMODEL_H
