#ifndef MOREMENU_H
#define MOREMENU_H

#include "basemenu.h"
#include "utils/constants.h"

class MoreMenu : public BaseMenu
{
    Q_OBJECT
public:
    MoreMenu(QWidget *parent = nullptr
              , int songId = -1
             , int favorite = 0
             , PlaylistKind listKind = PlaylistKind::PlayQueue
             , const QString &categoryName = QString());
};

#endif // MOREMENU_H
