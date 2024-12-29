#include "mainwindow.h"
#include "./database/database.h"

#include <QApplication>
#include <QMessageBox>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // initialize database
    if (!DB->init("C:/Project/Qt/panda_music_v02/main.db3")) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                              QObject::tr("initialize database failed"));
        return 2;
    }

    MainWindow w;
    w.show();
    return app.exec();
}
