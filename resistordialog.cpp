#include "resistordialog.h"
#include "ui_resistordialog.h"

Resistordialog::Resistordialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resistordialog)
{
    ui->setupUi(this);


    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    ui->warning->hide();

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

}

Resistordialog::~Resistordialog()
{
    delete ui;
}

QString Resistordialog::getInput()
{
    if(text != "")
        return text;
    else
        return "0";
}

void Resistordialog::buttonOK()
{
    if(ui->value->text() != "")
    {
        text = ui->value->text();
        ui->warning->hide();
        this->hide();
    }
    else
        ui->warning->show();
}

void Resistordialog::buttonCancel()
{
    ui->value->setText(text);
    ui->warning->hide();
    this->hide();
}
