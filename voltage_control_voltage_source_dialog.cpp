#include "voltage_control_voltage_source_dialog.h"
#include "ui_voltage_control_voltage_source_dialog.h"
#include <unit_transformer.h>
Voltage_control_voltage_source_dialog::Voltage_control_voltage_source_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voltage_control_voltage_source_dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    ui->warning->hide();

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

}

Voltage_control_voltage_source_dialog::~Voltage_control_voltage_source_dialog()
{
    delete ui;
}
/*
void Voltage_control_voltage_source_dialog::getInput(double &a,QString &b,QString &c)
{
    a = unit_transformer::transform(ui->coefline->text());
    b = ui->node1line->text();
    c = ui->node2line->text();
}

void Voltage_control_voltage_source_dialog::buttonOK()
{
    coefficient = ui->coefline->text();
    node1name = ui->node1line->text();
    node2name = ui->node2line->text();
    this->hide();
}

void Voltage_control_voltage_source_dialog::buttonCancel()
{
    ui->coefline->setText(coefficient);
    ui->node1line->setText(node1name);
    ui->node2line->setText(node2name);
    this->hide();
}
*/

void Voltage_control_voltage_source_dialog::getInput(double &a,QString &b,QString &c)
{
    if(ui->coefline->text() == "")
        a = 1;
    else
        a = unit_transformer::transform(ui->coefline->text());
    if(ui->node1line->text() == "")
        b = "ERROR";
    else
        b = node1name;
    if(ui->node2line->text() == "")
        c = "ERROR";
    else
        c = node2name;
}

void Voltage_control_voltage_source_dialog::buttonOK()
{
    if(ui->coefline->text() != "" && ui->node1line->text() != "" && ui->node2line->text() != "")
    {
        coefficient = ui->coefline->text();
        node1name = ui->node1line->text();
        node2name = ui->node2line->text();
        ui->warning->hide();
        this->hide();
    }
    else
        ui->warning->show();
    if(ui->coefline->text() != "")
        coefficient = ui->coefline->text();
    if(ui->node1line->text() != "")
        node1name = ui->node1line->text();
    if(ui->node2line->text() != "")
        node2name = ui->node2line->text();
}

void Voltage_control_voltage_source_dialog::buttonCancel()
{
    ui->coefline->setText(coefficient);
    ui->node1line->setText(node1name);
    ui->node2line->setText(node2name);
    ui->warning->hide();
    this->hide();
}

