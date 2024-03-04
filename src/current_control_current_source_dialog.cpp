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
    ui->warning->hide();

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

}

Current_control_current_source_dialog::~Current_control_current_source_dialog()
{
    delete ui;
}

void Current_control_current_source_dialog::getInput(double &a,QString &b)
{
    if(ui->coefline->text() == "")
        a = 1;
    else
        a = unit_transformer::transform(ui->coefline->text());
    if(ui->branchline->text() == "")
        b = "ERROR";
    else
        b = branchName;
    //   a = unit_transformer::transform(ui->coefline->text());
}

void Current_control_current_source_dialog::buttonOK()
{
    if(ui->coefline->text() != "" && ui->branchline->text() != "")
    {
        coefficient = ui->coefline->text();
        branchName = ui->branchline->text();
        ui->warning->hide();
        this->hide();
    }
    else
        ui->warning->show();
    if(ui->coefline->text() != "")
        coefficient = ui->coefline->text();
    if(ui->branchline->text() != "")
        branchName = ui->branchline->text();

}

void Current_control_current_source_dialog::buttonCancel()
{
    ui->coefline->setText(coefficient);
    ui->branchline->setText(branchName);
    ui->warning->hide();

    this->hide();
}
