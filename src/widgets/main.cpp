#include "mplayer.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);

    MusicDatabase database;
    database.initDatabase();
    MusicMeta musicmeta;
    musicmeta.init();

    MPlayer w;
    w.show();

    return a.exec();
}
