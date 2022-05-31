#include "TeamsTableModel.h"

TeamsTableModel::TeamsTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    teams = make_shared<vector<TeamDTO>>();
}

TeamsTableModel::TeamsTableModel(shared_ptr<vector<TeamDTO> > tms)
{
    teams = tms;
    rows_number = teams->size();
}

int TeamsTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int TeamsTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant TeamsTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
            case 0:
            {
                return QString("%1").arg((*teams)[row].getId());
            }
            case 1:
            {
                return QString::fromStdString((*teams)[row].getCountry());
            }
            case 2:
            {
                return QString::fromStdString((*teams)[row].getSponsor());
            }
            case 3:
            {
                return QString::fromStdString((*teams)[row].getCaptain());
            }
            case 4:
            {
                return QString::fromStdString((*teams)[row].getName());
            }
            case 5:
            {
                return QString("%1").arg((*teams)[row].getAvgRating());
            }
            default:
            {
                return QString("Row%1, Column%2")
                            .arg(index.row() + 1)
                            .arg(index.column() +1);
            }
        }
    }

    return QVariant();
}

QVariant TeamsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Spnsor");
        case 3:
            return QString("Captain");
        case 4:
            return QString("Team name");
        case 5:
            return QString("Average rating");
        }
    }
    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }
    return QVariant();
}
