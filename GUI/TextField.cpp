#include "TextField.h"

const QString TextField::styleSheet = "QLineEdit { border: 2px solid #C8D3D5; border-radius: 17px; padding: 6px; background-color: white; selection-background-color: darkgray; min-width: 57px; min-height: 30px; font-size: 14px; }";

TextField::TextField(QWidget *parent)
    : QLineEdit(parent)
{
    setStyleSheet(styleSheet);
}
