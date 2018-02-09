#pragma once

#include<QSqlQueryModel>
#include "util/music_global.h"

class Mysqlquerymodel : public QSqlQueryModel
{
public:
    Mysqlquerymodel();
    //FIXME : keep this function to edit favorite status (on/off)
    Qt::ItemFlags flags(const QModelIndex &index) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant data(const QModelIndex &item, int role) const;

    void refresh();
};
