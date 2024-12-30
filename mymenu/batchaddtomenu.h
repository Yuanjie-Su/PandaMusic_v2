#ifndef BATCHADDTOMENU_H
#define BATCHADDTOMENU_H

#include "basemenu.h"
#include "utils/constants.h"

class BatchAddToMenu : public BaseMenu
{
public:
    BatchAddToMenu(QWidget *parent = nullptr
                   , QVector<int> songIdVector = {}
                   , const QString &sourceCategoryName = ""
                   , PlaylistKind listKind = PlaylistKind::PlayQueue);
};

#endif // BATCHADDTOMENU_H
