#include "currentsourcedialog.h"
#include "ui_currentsourcedialog.h"
#include <unit_transformer.h>
Currentsourcedialog::Currentsourcedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Currentsourcedialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    QObject::connect(ui->Mode,SIGNAL(activated(int)),this,SLOT(selectMode(int)));

    curline = new QLineEdit(this);
    curtext = new QLabel(this);

    offline = new QLineEdit(this);
    ampline = new QLineEdit(this);
    freline = new QLineEdit(this);
    phaline = new QLineEdit(this);
    offtext = new QLabel(this);
    amptext = new QLabel(this);
    fretext = new QLabel(this);
    phatext = new QLabel(this);

    Ionline = new QLineEdit(this);
    Ioffline = new QLineEdit(this);
    Tperline = new QLineEdit(this);
    Tonline = new QLineEdit(this);
    Iontext = new QLabel(this);
    Iofftext = new QLabel(this);
    Tpertext = new QLabel(this);
    Tontext = new QLabel(this);

    curline->setGeometry(250,80,130,25);
    curtext->setGeometry(100,80,100,25);
    curtext->setText("DC value: ");

    offline->setGeometry(250,80,130,25);
    ampline->setGeometry(250,110,130,25);
    freline->setGeometry(250,140,130,25);
    phaline->setGeometry(250,170,130,25);
    offtext->setGeometry(100,80,100,25);
    amptext->setGeometry(100,110,100,25);
    fretext->setGeometry(100,140,100,25);
    phatext->setGeometry(100,170,100,25);

    offtext->setText("DC offset(A): ");
    amptext->setText("Amplitude(A): ");
    fretext->setText("Frequency(Hz): ");
    phatext->setText("Phase(deg): ");

    Ionline->setGeometry(250,80,130,25);
    Ioffline->setGeometry(250,110,130,25);
    Tperline->setGeometry(250,140,130,25);
    Tonline->setGeometry(250,170,130,25);
    Iontext->setGeometry(100,80,100,25);
    Iofftext->setGeometry(100,110,100,25);
    Tpertext->setGeometry(100,140,100,25);
    Tontext->setGeometry(100,170,100,25);

    Iontext->setText("Ion(A) :");
    Iofftext->setText("Ioff(A): ");
    Tpertext->setText("Time period(s): ");
    Tontext->setText("Ton(s): ");


    showDC();
    hideSine();
    hideSquare();

    currentMode = DC;
}

Currentsourcedialog::~Currentsourcedialog()
{
    delete ui;
    deleteDC();
    deleteSine();
    deleteSquare();
}
/*
void Currentsourcedialog::getInput(double &coa,double &o,double &f,double &p,int &m)
{
    switch(currentMode)
    {
        case DC:
            coa = curline->text().toDouble();
            o = 0;
            f = 0;
            p = 0;
            m = DC;
            break;
        case Sine:
            coa = ampline->text().toDouble();
            qDebug() << "voa = " << amptext->text().toDouble();
            o = offline->text().toDouble();
            f = freline->text().toDouble();
            p = phaline->text().toDouble();
            m = Sine;
            break;
        case Square:
            coa = Ionline->text().toDouble();
            o = Ioffline->text().toDouble();
            f = Tperline->text().toDouble();
            p = Tonline->text().toDouble();
            m = 2;
            break;
    }
}*/

void Currentsourcedialog::getInput(currentSourcedata &a,double &frequency,int &mode)
{
    switch(currentMode)
    {
    case DC:
        a.dcData.current = unit_transformer::transform(curline->text());
        mode = DC;
        break;
    case Sine:
        a.sineData.amplitude = unit_transformer::transform(ampline->text());
        a.sineData.offset = unit_transformer::transform(offline->text());
        frequency = unit_transformer::transform(freline->text());
        a.sineData.phase = unit_transformer::transform(phaline->text());
        mode = Sine;
        break;
    case Square:
        a.squareData.Ion = unit_transformer::transform(Ionline->text());
        a.squareData.Ioff = unit_transformer::transform(Ioffline->text());
        a.squareData.Tperiod = unit_transformer::transform(Tperline->text());
        a.squareData.Ton = unit_transformer::transform(Tonline->text());
        mode = Square;
        frequency = 1./a.squareData.Tperiod;
        break;
    }
}

void Currentsourcedialog::buttonOK()
{
    currentMode = ui->Mode->currentIndex();
    switch(currentMode)
    {
        case DC:
            current = curline->text();
            break;
        case Sine:
            offset = offtext->text();
            amplitude = amptext->text();
            frequency = fretext->text();
            phase = phatext->text();
            break;
        case Square:
            Ion = Iontext->text();
            Ioff = Iofftext->text();
            Tperiod = Tpertext->text();
            Ton = Tontext->text();
            break;
    }

    this->hide();
}

void Currentsourcedialog::buttonCancel()
{
    switch(currentMode)
    {
        case DC:
            curline->setText(current);
            break;
        case Sine:
            offline->setText(offset);
            ampline->setText(amplitude);
            freline->setText(frequency);
            phaline->setText(phase);
            break;
        case Square:
            Ionline->setText(Ion);
            Ioffline->setText(Ioff);
            Tperline->setText(Tperiod);
            Tonline->setText(Ton);
            break;
    }

    this->hide();
}

void Currentsourcedialog::selectMode(int m)
{

    switch(m)
    {
        case DC:
            hideSine();
            hideSquare();
            showDC();
            break;
        case Sine:
            hideDC();
            hideSquare();
            showSine();
            break;
        case Square:
            hideDC();
            hideSine();
            showSquare();
            break;
    }
}

void Currentsourcedialog::showDC()
{
    curline->show();
    curtext->show();
}

void Currentsourcedialog::showSine()
{
    offline->show();
    ampline->show();
    freline->show();
    phaline->show();
    offtext->show();
    amptext->show();
    fretext->show();
    phatext->show();
}

void Currentsourcedialog::showSquare()
{
    Ionline->show();
    Ioffline->show();
    Tperline->show();
    Tonline->show();
    Iontext->show();
    Iofftext->show();
    Tpertext->show();
    Tontext->show();
}

void Currentsourcedialog::hideDC()
{
    curline->hide();
    curtext->hide();
}

void Currentsourcedialog::hideSine()
{
    offline->hide();
    ampline->hide();
    freline->hide();
    phaline->hide();
    offtext->hide();
    amptext->hide();
    fretext->hide();
    phatext->hide();
}

void Currentsourcedialog::hideSquare()
{
    Ionline->hide();
    Ioffline->hide();
    Tperline->hide();
    Tonline->hide();
    Iontext->hide();
    Iofftext->hide();
    Tpertext->hide();
    Tontext->hide();
}


void Currentsourcedialog::deleteDC()
{
    delete curline;
    delete curtext;
}

void Currentsourcedialog::deleteSine()
{
    delete offline;
    delete ampline;
    delete freline;
    delete phaline;
    delete offtext;
    delete amptext;
    delete fretext;
    delete phatext;
}

void Currentsourcedialog::deleteSquare()
{
    delete Ionline;
    delete Ioffline;
    delete Tperline;
    delete Tonline;
    delete Iontext;
    delete Iofftext;
    delete Tpertext;
    delete Tontext;

}
