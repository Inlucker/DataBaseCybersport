#ifndef STUDIOSTABLEMODEL_H
#define STUDIOSTABLEMODEL_H

#include <QAbstractTableModel>
#include "EssensitiesDTO/StudioDTO.h"

class StudiosTableModel : public QAbstractTableModel
{
public:
    explicit StudiosTableModel(QObject *parent = nullptr);
    explicit StudiosTableModel(shared_ptr<vector<StudioDTO>> studs);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int rows_number = 0;
    shared_ptr<vector<StudioDTO> > studios;
};

#endif // STUDIOSTABLEMODEL_H
