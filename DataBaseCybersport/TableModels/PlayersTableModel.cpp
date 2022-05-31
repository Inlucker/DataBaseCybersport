#include "PlayersTableModel.h"

PlayersTableModel::PlayersTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    players = make_shared<vector<PlayerDTO>>();
}

PlayersTableModel::PlayersTableModel(shared_ptr<vector<PlayerDTO> > plrs)
{
    players = plrs;
    rows_number = players->size();
}

int PlayersTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int PlayersTableModel::columnCount(const QModelIndex &parent) const
{
    return 9;
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
                return QString("%1").arg((*players)[row].getId());
            }
            case 1:
            {
                return QString::fromStdString((*players)[row].getTeam());
            }
            case 2:
            {
                //return QString("%1").arg((*players)[row].getCountryId());
                return QString::fromStdString((*players)[row].getCountry());
            }
            case 3:
            {
                return QString::fromStdString((*players)[row].getNickname());
            }
            case 4:
            {
                return QString::fromStdString((*players)[row].getFirstName());
            }
            case 5:
            {
                return QString::fromStdString((*players)[row].getSecondName());
            }
            case 6:
            {
                return QString("%1").arg((*players)[row].getBirthYear());
            }
            case 7:
            {
                return QString::fromStdString((*players)[row].getMainRole());
            }
            case 8:
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

QVariant PlayersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Team");
        case 2:
            return QString("Country");
        case 3:
            return QString("Nickname");
        case 4:
            return QString("First name");
        case 5:
            return QString("Second name");
        case 6:
            return QString("Birth year");
        case 7:
            return QString("Main role");
        case 8:
            return QString("Rating");
        }
    }
    /*else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }*/
    return QVariant();
}
