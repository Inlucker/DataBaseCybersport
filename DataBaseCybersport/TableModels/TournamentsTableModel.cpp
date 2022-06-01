#include "TournamentsTableModel.h"

TournamentsTableModel::TournamentsTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    tournaments = make_shared<vector<TournamentDTO>>();
}

TournamentsTableModel::TournamentsTableModel(shared_ptr<vector<TournamentDTO> > tournaments) : tournaments(tournaments)
{
    rows_number = tournaments->size();
}

int TournamentsTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int TournamentsTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant TournamentsTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:
            return QString("%1").arg((*tournaments)[row].getId());
        case 1:
            return QString::fromStdString((*tournaments)[row].getCountry());
        case 2:
            return QString::fromStdString((*tournaments)[row].getOrganizer());
        case 3:
            return QString::fromStdString((*tournaments)[row].getName());
        case 4:
            return QString("%1").arg((*tournaments)[row].getPrizePool());
        default:
            return QString("Row%1, Column%2")
                        .arg(index.row() + 1)
                        .arg(index.column() +1);
        }
    }

    return QVariant();
}

QVariant TournamentsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Organizer");
        case 3:
            return QString("Tournament name");
        case 4:
            return QString("Prize pool");
        }
    }
    /*else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }*/
    return QVariant();
}
