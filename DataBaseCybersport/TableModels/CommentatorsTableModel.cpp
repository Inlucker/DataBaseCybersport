#include "CommentatorsTableModel.h"

CommentatorsTableModel::CommentatorsTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    rows_number = 0;
    commenatros = make_shared<vector<CommentatorDTO>>();
}

CommentatorsTableModel::CommentatorsTableModel(shared_ptr<vector<CommentatorDTO> > comms)
{
    commenatros = comms;
    rows_number = commenatros->size();
}

int CommentatorsTableModel::rowCount(const QModelIndex &parent) const
{
    return rows_number;
}

int CommentatorsTableModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant CommentatorsTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:
            return QString("%1").arg((*commenatros)[row].getId());
        case 1:
            return QString::fromStdString((*commenatros)[row].getStudio());
        case 2:
            return QString::fromStdString((*commenatros)[row].getCountry());
        case 3:
            return QString::fromStdString((*commenatros)[row].getNickname());
        case 4:
            return QString::fromStdString((*commenatros)[row].getFirstName());
        case 5:
            return QString::fromStdString((*commenatros)[row].getSecondName());
        case 6:
            return QString("%1").arg((*commenatros)[row].getBirthYear());
        case 7:
            return QString("%1").arg((*commenatros)[row].getPopularity());
        default:
            return QString("Row%1, Column%2")
                        .arg(index.row() + 1)
                        .arg(index.column() +1);
        }
    }

    return QVariant();
}

QVariant CommentatorsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Studio");
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
            return QString("Popularity");
        }
    }
    /*else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section);
    }*/
    return QVariant();
}
