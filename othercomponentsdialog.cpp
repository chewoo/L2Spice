#include "othercomponentsdialog.h"
#include "ui_othercomponentsdialog.h"

Othercomponentsdialog::Othercomponentsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Othercomponentsdialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    QObject::connect(ui->currentsource,SIGNAL(clicked()),this,SLOT(buttonCurrentSource()));
    QObject::connect(ui->currentcontrolcurrentsource,SIGNAL(clicked()),this,SLOT(buttonCurrentControlCurrentSource()));
    QObject::connect(ui->currentcontrolvoltagesource,SIGNAL(clicked()),this,SLOT(buttonCurrentControlVoltageSource()));
    QObject::connect(ui->voltagecontrolcurrentsource,SIGNAL(clicked()),this,SLOT(buttonVoltageControlCurrentSource()));
    QObject::connect(ui->voltagecontrolvoltagesource,SIGNAL(clicked()),this,SLOT(buttonVoltageControlVoltageSource()));

    image = new QImage();
    image->load("image/ppqwe.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));

    menuImage.push_back(new QPixmap("image/control_current_supply.png"));
    menuImage.push_back(new QPixmap("image/control_voltage_supply.png"));

    menuButtonIcon.push_back(new QIcon(*menuImage[0]));
    menuButtonIcon.push_back(new QIcon(*menuImage[1]));

    ui->currentcontrolcurrentsource->setIcon(*menuButtonIcon[0]);
    ui->currentcontrolvoltagesource->setIcon(*menuButtonIcon[1]);
    ui->voltagecontrolcurrentsource->setIcon(*menuButtonIcon[0]);
    ui->voltagecontrolvoltagesource->setIcon(*menuButtonIcon[1]);

}

Othercomponentsdialog::~Othercomponentsdialog()
{
    delete ui;
    delete image;
    qDeleteAll(menuImage);
    qDeleteAll(menuButtonIcon);
}

int Othercomponentsdialog::getMode()
{
    if(flagOK)
        return currentmode;
    else
        return -1;
}

void Othercomponentsdialog::buttonOK()
{
    flagOK = true;
    this->hide();
}

void Othercomponentsdialog::buttonCancel()
{
    flagOK = false;
    image->load("image/ppqwe.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
    this->hide();
}

void Othercomponentsdialog::buttonCurrentSource()
{
    currentmode = currentSource;
    image->load("image/current_supply.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
}

void Othercomponentsdialog::buttonCurrentControlCurrentSource()
{
    currentmode = CurrentcontrolCurrentSource;
    image->load("image/control_current_supply.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
}

void Othercomponentsdialog::buttonCurrentControlVoltageSource()
{
    currentmode = CurrentcontrolVoltageSource;
    image->load("image/control_voltage_supply.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
}

void Othercomponentsdialog::buttonVoltageControlCurrentSource()
{
    currentmode = VoltagecontrolCurrentSource;
    image->load("image/control_current_supply.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
}

void Othercomponentsdialog::buttonVoltageControlVoltageSource()
{
    currentmode = VoltagecontrolVoltageSource;
    image->load("image/control_voltage_supply.png");
    ui->image->setPixmap(QPixmap::fromImage(*image));
}

