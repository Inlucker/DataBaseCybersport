#include "MatchesTableModel.h"

MatchesTableModel::MatchesTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    matches = make_shared<vector<MatchDTO>>();
}

MatchesTableModel::MatchesTableModel(shared_ptr<vector<MatchDTO> > matches) : matches(matches)
{
    rows_number = matches->size();
}

int MatchesTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int MatchesTableModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant MatchesTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:
            return QString("%1").arg((*matches)[row].getId());
        case 1:
            return QString::fromStdString((*matches)[row].getTeam1());
        case 2:
            return QString::fromStdString((*matches)[row].getTeam2());
        case 3:
            return QString::fromStdString((*matches)[row].getWinner());
        case 4:
            return QString::fromStdString((*matches)[row].getStudio());
        case 5:
            return QString::fromStdString((*matches)[row].getCommentator());
        case 6:
            return QString::fromStdString((*matches)[row].getTournament());
        case 7:
            return QString::fromStdString((*matches)[row].getDate());
        default:
            return QString("Row%1, Column%2")
                        .arg(index.row() + 1)
                        .arg(index.column() +1);
        }
    }

    return QVariant();
}

QVariant MatchesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Team1");
        case 2:
            return QString("Team2");
        case 3:
            return QString("Winner");
        case 4:
            return QString("Studio");
        case 5:
            return QString("Commentator");
        case 6:
            return QString("Tournament");
        case 7:
            return QString("Date");
        }
    }
    /*else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }*/
    return QVariant();
}
