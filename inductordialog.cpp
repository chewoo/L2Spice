#include "inductordialog.h"
#include "ui_inductordialog.h"

Inductordialog::Inductordialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inductordialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));

}

Inductordialog::~Inductordialog()
{
    delete ui;
}

QString Inductordialog::getInput()
{
    return text;
}

void Inductordialog::buttonOK()
{
    text = ui->value->text();
    this->hide();
}

void Inductordialog::buttonCancel()
{
    ui->value->setText(text);
    this->hide();
}
