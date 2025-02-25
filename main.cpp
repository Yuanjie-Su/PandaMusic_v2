#include "mainwindow.h"
#include "./database/database.h"
// #include "./network/musiclibrary.h"

#include <QApplication>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // MusicLibrary *musicLibrary = new MusicLibrary();
    // musicLibrary->searchSong("周杰伦");

    // 初始化数据库
    if (!DB->init("C:/Project/Qt/panda_music_v02/main.db3")) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                              QObject::tr("initialize database failed"));
        return 2;
    }

    MainWindow w;
    w.show();
    return app.exec();
}
