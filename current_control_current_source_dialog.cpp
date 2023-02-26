#include "current_control_current_source_dialog.h"
#include "ui_current_control_current_source_dialog.h"
#include <unit_transformer.h>
Current_control_current_source_dialog::Current_control_current_source_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Current_control_current_source_dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));

}

Current_control_current_source_dialog::~Current_control_current_source_dialog()
{
    delete ui;
}

void Current_control_current_source_dialog::getInput(double &a,QString &b)
{
    if(ui->coefficient->text() == "")
        a = 1;
    else
        a = unit_transformer::transform(ui->coefline->text());
    if(ui->branchline->text() == "")
        b = "ERROR";
    else
        a = unit_transformer::transform(ui->coefline->text());
}

void Current_control_current_source_dialog::buttonOK()
{
    coefficient = ui->coefline->text();
    branchName = ui->branchline->text();
    this->hide();
}

void Current_control_current_source_dialog::buttonCancel()
{
    ui->coefficient->setText(coefficient);
    ui->branchline->setText(branchName);
    this->hide();
}
