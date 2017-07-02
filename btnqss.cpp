#include <btnqss.h>

void setBtnQss(QPushButton *btn,
                           QString normalColor, QString normalTextColor,
                           QString hoverColor, QString hoverTextColor,
                           QString pressedColor, QString pressedTextColor){
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}
