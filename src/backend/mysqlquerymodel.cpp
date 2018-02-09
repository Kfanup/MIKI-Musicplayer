#include "mysqlquerymodel.h"

using namespace MMusic;
Mysqlquerymodel::Mysqlquerymodel()
{

}

Qt::ItemFlags Mysqlquerymodel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    //if set, the index of favorite property will be 2
    if (index.column() == 2)
        flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant Mysqlquerymodel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    // change length of song from integer (or long) to string
    if (role == Qt::DisplayRole && item.column() == 1)
        return QVariant(MMusic::length2String(value.toInt()));
    if (role == Qt::TextAlignmentRole && item.column() == 1)
        value = (Qt::AlignVCenter + Qt::AlignCenter);
    return value;
}

void Mysqlquerymodel::refresh()
{
    setQuery("SELECT title, length FROM mymusic");
    sort(1,Qt::AscendingOrder);
    setHeaderData(0, Qt::Horizontal, tr("歌名"));
    setHeaderData(1, Qt::Horizontal, tr("长度"));
}
