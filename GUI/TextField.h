#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>

class TextField : public QLineEdit
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = nullptr);

private:
    static const QString styleSheet;
};

#endif // TEXTFIELD_H
