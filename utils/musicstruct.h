#ifndef MUSICSTRUCT_H
#define MUSICSTRUCT_H
#include <QString>

struct mst {
    QString name;
    QString singerName;
    QString albumName;
    QString time;
    QString hashStr;
    QString id;
    QString url;
    QString img;
    QString lrcStr;

    bool operator == (const mst a) const {
        return name == a.name && singerName == a.singerName &&
               hashStr == a.hashStr && albumName == a.albumName &&
               time == a.time && url == a.url && img == a.img &&
               lrcStr == a.lrcStr;
    }
};
#endif // MUSICSTRUCT_H
