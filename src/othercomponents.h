#ifndef OTHERCOMPONENTS_H
#define OTHERCOMPONENTS_H

#include <QDialog>

namespace Ui {
class Othercomponents;
}

class Othercomponents : public QDialog
{
    Q_OBJECT

public:
    explicit Othercomponents(QWidget *parent = nullptr);
    ~Othercomponents();

private:
    Ui::Othercomponents *ui;
};

#endif // OTHERCOMPONENTS_H
