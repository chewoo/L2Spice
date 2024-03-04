#include "diado_dialog.h"
#include "ui_diado_dialog.h"

Diado_dialog::Diado_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diado_dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    ui->warning->hide();

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

}

Diado_dialog::~Diado_dialog()
{
    delete ui;
}
/*
QString Diado_dialog::getInput()
{
    return text;
}

void Diado_dialog::buttonOK()
{
    text = ui->value->text();
    this->hide();
}

void Diado_dialog::buttonCancel()
{
    ui->value->setText(text);
    this->hide();
}
*/

QString Diado_dialog::getInput()
{
    if(text != "")
        return text;
    else
        return "0";
}

void Diado_dialog::buttonOK()
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

void Diado_dialog::buttonCancel()
{
    ui->value->setText(text);
    ui->warning->hide();
    this->hide();
}
