#include "current_control_voltage_source_dialog.h"
#include "ui_current_control_voltage_source_dialog.h"
#include <unit_transformer.h>
Current_control_voltage_source_dialog::Current_control_voltage_source_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Current_control_voltage_source_dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));

}

Current_control_voltage_source_dialog::~Current_control_voltage_source_dialog()
{
    delete ui;
}

void Current_control_voltage_source_dialog::getInput(double &a,QString &b)
{
    a = unit_transformer::transform(ui->coefline->text());
    b = ui->branchline->text();

}

void Current_control_voltage_source_dialog::buttonOK()
{
    coefficient = ui->coefline->text();
    branchName = ui->branchline->text();
    this->hide();
}

void Current_control_voltage_source_dialog::buttonCancel()
{
    ui->coefficient->setText(coefficient);
    ui->branchline->setText(branchName);
    this->hide();
}
