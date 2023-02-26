#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->workspace->setMouseTracking(true);

    QObject::connect(ui->wireButton,SIGNAL(clicked()),this,SLOT(pushWire()));
    QObject::connect(ui->resistorButton,SIGNAL(clicked()),this,SLOT(pushResistor()));
    QObject::connect(ui->capacitorButton,SIGNAL(clicked()),this,SLOT(pushCapacitor()));
    QObject::connect(ui->inductorButton,SIGNAL(clicked()),this,SLOT(pushInductor()));
    QObject::connect(ui->voltagesourceButton,SIGNAL(clicked()),this,SLOT(pushVoltageSource()));
    QObject::connect(ui->componentsButton,SIGNAL(clicked()),this,SLOT(pushComponents()));
    QObject::connect(ui->moveButton,SIGNAL(clicked()),this,SLOT(pushMove()));
    QObject::connect(ui->delButton,SIGNAL(clicked()),this,SLOT(pushDelete()));
    QObject::connect(ui->groundButton,SIGNAL(clicked()),this,SLOT(pushGround()));
    QObject::connect(ui->runButton,SIGNAL(clicked()),this,SLOT(pushRun()));
    QObject::connect(ui->runButton,SIGNAL(clicked()),this,SLOT(pushRun()));
    QObject::connect(ui->diodeButton,SIGNAL(clicked()),this,SLOT(pushDiode()));


    menuImage.push_back(new QPixmap("image/Boss.png"));
    menuImage.push_back(new QPixmap("image/resistor.png"));
    menuImage.push_back(new QPixmap("image/capacitor.png"));
    menuImage.push_back(new QPixmap("image/inductor.png"));
    menuImage.push_back(new QPixmap("image/voltage_supply.png"));
    menuImage.push_back(new QPixmap("image/ppqwe.png"));
    menuImage.push_back(new QPixmap("image/ground.png"));
    menuImage.push_back(new QPixmap("image/player.png"));
    menuImage.push_back(new QPixmap("image/popo.png"));
    menuImage.push_back(new QPixmap("image/tt.png"));
    menuImage.push_back(new QPixmap("image/diode.png"));

    for(int i=0;i<11;i++)
        menuButtonIcon.push_back(new QIcon(*menuImage[i]));

    ui->wireButton->setIcon(*menuButtonIcon[0]);
    ui->resistorButton->setIcon(*menuButtonIcon[1]);
    ui->capacitorButton->setIcon(*menuButtonIcon[2]);
    ui->inductorButton->setIcon(*menuButtonIcon[3]);
    ui->voltagesourceButton->setIcon(*menuButtonIcon[4]);
    ui->componentsButton->setIcon(*menuButtonIcon[5]);
    ui->groundButton->setIcon(*menuButtonIcon[6]);
    ui->moveButton->setIcon(*menuButtonIcon[7]);
    ui->delButton->setIcon(*menuButtonIcon[8]);
    ui->runButton->setIcon(*menuButtonIcon[9]);
    ui->diodeButton->setIcon(*menuButtonIcon[10]);

    othercomponentsdialog = new Othercomponentsdialog();
    othercomponentsdialog->setModal(true);

}

void MainWindow::pushWire()
{
    ui->workspace->pushWire();
}

void MainWindow::pushResistor()
{
    ui->workspace->pushResistor();
}

void MainWindow::pushCapacitor()
{
    ui->workspace->pushCapacitor();
}

void MainWindow::pushInductor()
{
    ui->workspace->pushInductor();
}

void MainWindow::pushVoltageSource()
{
    ui->workspace->pushVoltageSource();
}

void MainWindow::pushComponents()
{
    othercomponentsdialog->exec();
    switch(othercomponentsdialog->getMode())
    {
        case 0:
            ui->workspace->pushCurrentSource();
            break;
        case 1:
            ui->workspace->pushCurrentControlCurrentSource();
            break;
        case 2:
            ui->workspace->pushCurrentControlVoltageSource();
            break;
        case 3:
            ui->workspace->pushVoltageControlCurrentSource();
            break;
        case 4:
            ui->workspace->pushVoltageControlVoltageSource();
            break;
    }
}

void MainWindow::pushCurrentSource()
{
    ui->workspace->pushCurrentSource();
}
void MainWindow::pushMove()
{
    ui->workspace->pushMove();
}
void MainWindow::pushDelete()
{
    ui->workspace->pushDelete();
}
void MainWindow::pushDiode()
{
    ui->workspace->pushDiode();
}
void MainWindow::pushGround()
{
    ui->workspace->pushGround();
}
void MainWindow::pushRun()
{
    ui->workspace->pushRun();
}
MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0;i<menuImage.size();i++)
    {
        delete menuButtonIcon[i];
        delete menuImage[i];
    }
    menuButtonIcon.clear();
    menuImage.clear();
    delete othercomponentsdialog;
}

void MainWindow::on_action_peter_dragon_dick_triggered()
{
    qDebug() << "Peterrrrrrrrrrrrrrrrrrrrrrr!!!!!!";
}



