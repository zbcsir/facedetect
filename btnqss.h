#ifndef BTNQSS_H
#define BTNQSS_H

#include <QPushButton>
#include <QString>

void setBtnQss(QPushButton *btn,
               QString normalColor, QString normalTextColor,
               QString hoverColor, QString hoverTextColor,
               QString pressedColor, QString pressedTextColor);

#endif // BTNQSS_H

