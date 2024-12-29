#ifndef ADDTOMENU_H
#define ADDTOMENU_H

#include "basemenu.h"


class AddToMenu : public BaseMenu
{
    Q_OBJECT
public:
    AddToMenu(QWidget *parent = nullptr
              , int songId = -1);
};

#endif // ADDTOMENU_H
