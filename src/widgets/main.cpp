#include "mplayer.h"
#include <QApplication>
#include <QStyleFactory>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);

    QSharedMemory shared("SHGND-MIN-080209");
    if (shared.attach())
    {
        return 0;
    }
    shared.create(1);

    MusicDatabase database;
    database.initDatabase();
    MusicMeta musicmeta;
    musicmeta.init();

    MPlayer w;
    w.show();

    return a.exec();
}
