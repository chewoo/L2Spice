#include "voltage_control_current_source_dialog.h"
#include "ui_voltage_control_current_source_dialog.h"
#include <unit_transformer.h>
Voltage_control_current_source_dialog::Voltage_control_current_source_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voltage_control_current_source_dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
}

Voltage_control_current_source_dialog::~Voltage_control_current_source_dialog()
{
    delete ui;
}

void Voltage_control_current_source_dialog::getInput(double &a,QString &b,QString &c)
{
    a = unit_transformer::transform(ui->coefline->text());
    b = ui->node1line->text();
    c = ui->node2line->text();
}

void Voltage_control_current_source_dialog::buttonOK()
{
    coefficient = ui->coefline->text();
    node1name = ui->node1line->text();
    node2name = ui->node2line->text();
    this->hide();
}

void Voltage_control_current_source_dialog::buttonCancel()
{
    ui->coefline->setText(coefficient);
    ui->node1line->setText(node1name);
    ui->node2line->setText(node2name);
    this->hide();
}
