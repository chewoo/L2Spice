#include "linenodeitemdialog.h"
#include "ui_linenodeitemdialog.h"

Linenodeitemdialog::Linenodeitemdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Linenodeitemdialog)
{
    ui->setupUi(this);

    voltage = "";
    this->hide();
}

Linenodeitemdialog::~Linenodeitemdialog()
{
    delete ui;
}

double Linenodeitemdialog::getInput()
{
    return voltage.toDouble();
}

void Linenodeitemdialog::on_OK_clicked()
{
    voltage = ui->volline->text();
    this->hide();
}


void Linenodeitemdialog::on_Cancel_clicked()
{
    ui->volline->setText(voltage);
    this->hide();
}

