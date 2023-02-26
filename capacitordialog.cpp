#include "capacitordialog.h"
#include "ui_capacitordialog.h"

Capacitordialog::Capacitordialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Capacitordialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
}

Capacitordialog::~Capacitordialog()
{
    delete ui;
}

QString Capacitordialog::getInput()
{
    if(text == "")
        return "0";
    return text;
}

void Capacitordialog::buttonOK()
{
    text = ui->value->text();
    this->hide();
}

void Capacitordialog::buttonCancel()
{
    ui->value->setText(text);
    this->hide();
}
