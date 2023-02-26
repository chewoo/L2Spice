#include "diado_dialog.h"
#include "ui_diado_dialog.h"

Diado_dialog::Diado_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diado_dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));

}

Diado_dialog::~Diado_dialog()
{
    delete ui;
}

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
