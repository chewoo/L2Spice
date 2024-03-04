#include "othercomponents.h"
#include "ui_othercomponents.h"

Othercomponents::Othercomponents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Othercomponents)
{
    ui->setupUi(this);
}

Othercomponents::~Othercomponents()
{
    delete ui;
}
