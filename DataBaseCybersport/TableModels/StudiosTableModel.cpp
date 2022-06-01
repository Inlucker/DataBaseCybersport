#include "StudiosTableModel.h"

StudiosTableModel::StudiosTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    studios = make_shared<vector<StudioDTO>>();
}

StudiosTableModel::StudiosTableModel(shared_ptr<vector<StudioDTO> > studs)
{
    studios = studs;
    rows_number = studios->size();
}

int StudiosTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int StudiosTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant StudiosTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:
            return QString("%1").arg((*studios)[row].getId());
        case 1:
            return QString::fromStdString((*studios)[row].getCountry());
        case 2:
            return QString::fromStdString((*studios)[row].getOwner());
        case 3:
            return QString::fromStdString((*studios)[row].getName());
        case 4:
            return QString("%1").arg((*studios)[row].getAvgPopularity());
        default:
            return QString("Row%1, Column%2")
                        .arg(index.row() + 1)
                        .arg(index.column() +1);
        }
    }

    return QVariant();
}

QVariant StudiosTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Country");
        case 2:
            return QString("Owner");
        case 3:
            return QString("Studio name");
        case 4:
            return QString("Average popularity");
        }
    }
    /*else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }*/
    return QVariant();
}
