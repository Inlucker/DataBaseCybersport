#include "PlayersTableModel.h"

PlayersTableModel::PlayersTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 4;
    players = make_shared<vector<PlayerBL>>();
}

PlayersTableModel::PlayersTableModel(shared_ptr<vector<PlayerBL> > plrs)
{
    rows_number = plrs->size();
    players = plrs;
}

int PlayersTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int PlayersTableModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant PlayersTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
            case 0:
            {
                return QString("%1").arg((*players)[row].getTeamId());
            }
            case 1:
            {
                return QString("%1").arg((*players)[row].getCountryId());
            }
            case 2:
            {
                return QString::fromStdString((*players)[row].getNickname());
            }
            case 3:
            {
                return QString::fromStdString((*players)[row].getFirstName());
            }
            case 4:
            {
                return QString::fromStdString((*players)[row].getSecondName());
            }
            case 5:
            {
                return QString("%1").arg((*players)[row].getBirthYear());
            }
            case 6:
            {
                return QString::fromStdString((*players)[row].getMainRole());
            }
            case 7:
            {
                return QString("%1").arg((*players)[row].getRating());
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
