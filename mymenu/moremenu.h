#ifndef MOREMENU_H
#define MOREMENU_H

#include "basemenu.h"

class MoreMenu : public BaseMenu
{
    Q_OBJECT
public:
    MoreMenu(QWidget *parent = nullptr
              , int songId = -1, int favorite = 0);
};

#endif // MOREMENU_H
