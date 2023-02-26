#include "resistordialog.h"
#include "ui_resistordialog.h"

Resistordialog::Resistordialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resistordialog)
{
    ui->setupUi(this);


    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));

}

Resistordialog::~Resistordialog()
{
    delete ui;
}

QString Resistordialog::getInput()
{
    return text;
}

void Resistordialog::buttonOK()
{
    text = ui->value->text();
    this->hide();
}

void Resistordialog::buttonCancel()
{
    ui->value->setText(text);
    this->hide();
}
