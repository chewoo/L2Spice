#include "capacitordialog.h"
#include "ui_capacitordialog.h"

Capacitordialog::Capacitordialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Capacitordialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    ui->warning->hide();

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

Capacitordialog::~Capacitordialog()
{
    delete ui;
}

QString Capacitordialog::getInput()
{
    if(text != "")
        return text;
    else
        return "0";
}

void Capacitordialog::buttonOK()
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

void Capacitordialog::buttonCancel()
{
    ui->value->setText(text);
    ui->warning->hide();
    this->hide();
}
